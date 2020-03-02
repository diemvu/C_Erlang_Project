#include "processTable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct processCell{
    // process ID in each process Cell
    int process_id;
    // how many frame a process ID takes up
    int frameCount;
    // size of process
    int processSize;
    // what frame the process takes
    int *frameList ;
};
struct processTable {
    // how many partition( cell) in process Table
    int numberOfCell;
    // array of processCell
    Cell ProcessCell; 
};

// create Processtable
ProcessTable createProcessTable(int numberOfPartition){
    ProcessTable ptr = malloc(sizeof(struct processTable));
    if(ptr!=NULL){
        ptr->numberOfCell = numberOfPartition;
        // process table have numberOf Partiton cell
        ptr->ProcessCell = malloc(sizeof(struct processCell) * numberOfPartition);
        if(ptr->ProcessCell != NULL){
            int i = 0;
            // initialize value for processCell component
            for (; i< numberOfPartition; i++){
                ptr->ProcessCell[i].process_id = 0;
                ptr->ProcessCell[i].processSize = 0;
                ptr->ProcessCell[i].frameCount = 0;
                ptr ->ProcessCell[i].frameList = malloc(sizeof(int) * numberOfPartition) ;
            } 
        }
    }
    return ptr;

}
//print out Proces Table
void printProcessTable(ProcessTable table){
    int i = 0;
    for(; i< table->numberOfCell; i++){
        // if a cell store frame list of a process ID, print it out
        if (table->ProcessCell[i].frameCount != 0){
            printf("%d                      ",table->ProcessCell[i].process_id);
            int j = 0;
            for (; j< table->ProcessCell[i].frameCount -1; j++){
                printf("%d,  ",table-> ProcessCell[i].frameList[j]);
            }
            printf("%d",table-> ProcessCell[i].frameList[j]);
            printf("\n");
        }
        
    }
}
// add a process to Processtable
void addProcess2ProcessTable(ProcessTable table, int process_size, int id, int frame_count, int * frame_list ){
    int m = 0;
    int i = 0;
    // if a process Cell is empty, store a process ID and its frame list into it
    for (; i< table->numberOfCell; i++){
        if (table->ProcessCell[i].frameCount == 0){
            table ->ProcessCell[i].frameList = malloc(sizeof(int) * frame_count);
            table->ProcessCell[i].process_id = id;
            table->ProcessCell[i].processSize = process_size;
            table->ProcessCell[i].frameCount = frame_count;
            int j = 0;
            for(;j<frame_count; j++){
                table->ProcessCell[i].frameList[j] = frame_list[j];
            }
            
            break;
        }
    }
}

// delete a process
int deleteProcessfromProcessTable(ProcessTable table, int id){
    if (id ==0) {
        printf("Process 0 does not exist\n");
        return 0;
    }
    // exist will have value of 0 if the process ID doesnt exist or equals to the total frame that process takes up
    int exist = 0;
    int i = 0;
    for (; i< table->numberOfCell; i++){
        // if procesID in a cell equals to the ID user want to delete
        if (table->ProcessCell[i].process_id == id){
            exist = table->ProcessCell[i].frameCount;
            table->ProcessCell[i].process_id = 0;
            table->ProcessCell[i].processSize = 0;
            table->ProcessCell[i].frameCount = 0;
            break;
        }
    }
    if (i == table->numberOfCell){
        printf("Process %d not found\n",id); 
        exist = 0;
    } 
    return exist;
}




