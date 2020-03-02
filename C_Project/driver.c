// This program is run on Linux VM.

#include <stdio.h>
#include "partitionTable.h"
#include "processTable.h"
# include <stdlib.h>

// print out prompt and take inputs
void prompt(ProcessTable tableProcess, FrameTable table, int * id);
//add a process into memory
void add(ProcessTable tableProcess, FrameTable table, int *id);
//delete a process
void delete(ProcessTable tableProcess, FrameTable table, int *id);
//print out process and frame table
void print(ProcessTable tableProcess, FrameTable table, int *id);
// quit program
void quit();

// main method
int main(void){
    // create an frame and process table
    FrameTable table;
    ProcessTable tableProcess;
    // create an variable to keep track of process ID
    int processID =  0;
    int numberOfPartition, partitionSize;
    printf("Enter the number of partitions: ");
    scanf("%d", &numberOfPartition);
    printf("Enter the size of partitions: ");
    scanf("%d", &partitionSize);
    table = createFrameTable(numberOfPartition,partitionSize);
    tableProcess = createProcessTable(numberOfPartition);
    //prompt
    prompt(tableProcess, table, & processID);
    
    return 0;
}
// // print out prompt and take inputs
void prompt(ProcessTable tableProcess, FrameTable table, int *id){
    int choice;
    printf("Do you want to: \nAdd a process? Enter 1 \nDelete a process? Enter 2 \nPrint values? Enter 3 \nQuit? Enter 4)\n");
    scanf("%d", &choice);
    if(choice == 1) add(tableProcess, table, id);
    if (choice == 2) delete(tableProcess, table, id);
    if (choice == 3) print(tableProcess, table, id);
    if (choice == 4) quit();
}
// add a process
void add(ProcessTable tableProcess, FrameTable table, int *id){
    // increment process ID
    (*id) ++;
    int process_size;
    printf("Adding - Enter process size ");
    scanf("%d", & process_size);
    // add process to processTable and Frame table
    addProcess(tableProcess, table,process_size,*id);
    // print out prompt again
    prompt(tableProcess, table, id);
}
// delete a process
void delete(ProcessTable tableProcess, FrameTable table, int* id){
    int process_id;
    printf("Deleting - Enter processs id: ");
    // get process ID from console
    scanf("%d", & process_id);
    // delete process from frame and process Table
    deleteProcess(tableProcess, table,process_id);
    printf("\n");
    // print prompt again
    prompt(tableProcess, table, id);
}

// print out process and frame table
void print(ProcessTable tableProcess, FrameTable table, int * id){
    printf("Printing – \n");
    printf("---------------------------------------------------------------------------\n");
    printf("Process table:\n");
    printf("Process id              Frames\n");
    // print process Table
    printProcessTable(tableProcess);
    printf("---------------------------------------------------------------------------\n");
    printf("Partition table:\n");
    printf("Partition number    Process id      Frag        Availability\n");
    // print partitionTable
    printPartitionTable(table);
    printf("---------------------------------------------------------------------------");
    printf("\n");
    // print prompt again
    prompt(tableProcess, table, id);

}
// quit program
void quit(){
    exit(0);
}

