pr1.out : driver.o processTable.o partitionTable.o
	gcc -o pr1.out driver.o processTable.o partitionTable.o
driver.o : driver.c processTable.h partitionTable.h
	gcc -c driver.c
processTable.o : processTable.c processTable.h
	gcc -c processTable.c
partitionTable.o : partitionTable.c partitionTable.h processTable.h
	gcc -c partitionTable.c
