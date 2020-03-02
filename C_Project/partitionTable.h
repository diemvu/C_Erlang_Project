#ifndef PARTITIONTABLE_H
#define PARTITIONTABLE_H
#include "processTable.h"

// define pointer of frame Table
typedef struct frameTable * FrameTable;
// define pinter of partition
typedef struct partition * Partition;
// create frame table
FrameTable createFrameTable(int numberOfPart, int maximum);
// print out partitiontable
void printPartitionTable(FrameTable table);
// add process to frame table
void addProcess(ProcessTable protable, FrameTable table, int process_size, int process_id);
// delete process from frame table
void deleteProcess(ProcessTable protable, FrameTable table,int process_id);

#endif