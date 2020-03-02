#ifndef PROCESSTABLE_H
#define PROCESSTABLE_H

// define a pointer of processTable
typedef struct processTable * ProcessTable;
// define a pointer of processCell
typedef struct processCell * Cell;
// create Process table
ProcessTable createProcessTable(int numberOfCell);
// print out ProcessTable
void printProcessTable(ProcessTable table);
// add a process
void addProcess2ProcessTable(ProcessTable table, int process_size, int id, int frame_count, int *frame_list);
// delete a process
int deleteProcessfromProcessTable(ProcessTable table, int id);

#endif