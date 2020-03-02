#include "partitionTable.h"
#include "processTable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// each partition holds procesID, left over fragment it holds and a character indicate its availability
struct partition{
    int process_id;
    int fragment;
    char availability;
};

// frame Table hold its capacity, maximum space each partition has, an array of partition
struct frameTable{
    int * frameList;
    int availCapacity;
    int maximumSpace;
    int numberOfPartition;
    Partition partitionTable;
};

// creaste Frame Table from inputs
FrameTable createFrameTable(int numberOfPart, int maximum){
    FrameTable  ptr = malloc(sizeof( struct frameTable));
    if(ptr != NULL){
        ptr->availCapacity = numberOfPart;
        ptr->maximumSpace = maximum;
        ptr -> numberOfPartition = numberOfPart;
        // an array to temporary store what frame a process is added into
        ptr->frameList = malloc(sizeof(int) * numberOfPart);
        // create an array of partition
        ptr->partitionTable = malloc(sizeof(struct partition) * numberOfPart);
        if (ptr-> partitionTable != NULL){
            int i = 0;
            for(;i<numberOfPart; i++){
                // process_id, fragment is initialized to 0, availibility to Y
                ptr ->partitionTable[i].process_id = 0;
                ptr ->partitionTable[i].fragment = 0;
                ptr ->partitionTable[i].availability ='Y';
            }
        }
    }
    
    return ptr;
}
// add process to frame and process table
void addProcess(ProcessTable proTable, FrameTable table, int process_size, int process_id){
    // find the number of frames is taken by process
    int x = process_size/table->maximumSpace;
    int rem = process_size % table->maximumSpace;
    int x_copy = x;
    // if process size  does not devides maximum size of each partition, the number of partition taken is x+1  
    if (rem>0) x_copy = x+1;
    
    // change value in each partition  taken
    if (table->availCapacity >= x_copy){

        int count =0;
        int i = 0;
        for (; i< table->numberOfPartition; i++){
        if(table ->partitionTable[i].availability == 'Y' && count <  x){
            table->partitionTable[i].fragment =0;
            table->partitionTable[i].availability ='N';
            table ->partitionTable[i].process_id = process_id;
            table->frameList[count] = i;
            count++;
            }
        if (table ->partitionTable[i].availability == 'Y' && count ==  x && rem != 0){
            table->partitionTable[i].fragment = table->maximumSpace - rem;
            table->partitionTable[i].availability ='N';
            table ->partitionTable[i].process_id = process_id;
            table->frameList[count] = i;
            break;
        } 
        }
        int j = 0;
        // add process to ProcessTable
        addProcess2ProcessTable(proTable, process_size, process_id,x_copy, table->frameList);
        table->availCapacity = table->availCapacity - x_copy;
    } else{
        printf("Not enough memmory\n");
    }

    } 
// delete process from process table and frame table 
void deleteProcess(ProcessTable proTable, FrameTable table,int process_id){
    // get the number of frame will be deleted
    int numberOfDeleteFrame = deleteProcessfromProcessTable(proTable, process_id);
    if ( numberOfDeleteFrame != 0){
        table-> availCapacity = table-> availCapacity + numberOfDeleteFrame;

        int i =0;
        // change value in each partition deletes
        for (; i< table-> maximumSpace; i++){
            if (table->partitionTable[i].process_id == process_id) {

                table->partitionTable[i].process_id = 0;
                table->partitionTable[i].availability ='Y';
                table->partitionTable[i].fragment = 0;
            }
        }
    }
}
// print partitionTable
void printPartitionTable(FrameTable table){
    int j = 0;
    for (; j< table->numberOfPartition; j++){
        if(table->partitionTable[j].availability =='N')
        printf("%-20d%-16d%-12d%-13c\n",j,table->partitionTable[j].process_id,table->partitionTable[j].fragment,table->partitionTable[j].availability);
        else printf("%d                   ?               ?           Y\n",j);                  
    }
}
