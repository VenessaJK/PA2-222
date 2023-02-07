#include "plate.h"

int SIZE = 0;

/*----------------------------------------
The hashInit function initializes the table 
of linked lists 
----------------------------------------*/
struct node** hashInit(int hashSize){

	SIZE = hashSize;	//globalizes size var
	struct node** table;	//table is a pointer 
	table = malloc(SIZE*sizeof(struct node*));
        for(int i=0; i < SIZE; i++){
                table[i] = listInit();
	}
	return(table);
}

/*------------------------------------------
The hash function
------------------------------------------*/
int hash(char *plate)
{
	int sum=0, total=0;
	for(int i=0; i <= (strlen(plate)-1); i++){

		sum = ((2*i)+3) * ((2*i)+3) * plate[i]; //using the ascii value of plate
		total += sum;
	}
	int index = total % SIZE;
	return index;
}

/*----------------------------------------------
The hashAdd function
-----------------------------------------------*/
void hashAdd(struct node** Table, char *plate, char *first, char *last)
{
	int index;
	index = hash(plate);
	listAdd(Table[index], plate, first, last);
	return;
}

/*--------------------------------------------
The hashDump function. If usr doesn't specify n
then n is used as a flag and set to -1, meaning
print contents of every cell. Otherwise, n
specifies which cell in table to print.
-------------------------------------------*/
void hashDump(struct node** Table, int n)
{
	if(n == -1){	//flag set in main
		for(int i=0; i < SIZE; i++){
			printf("CELL %d\n", i);
                        listPrint(Table[i]); //prints every cell
			printf("------------------------------------------\n");
                }
	} else{
		printf("CELL %d\n", n);
		listPrint(Table[n]);	//prints one specific cell
		printf("------------------------------------------\n");
	}
	return;
}

/*-------------------------------------------------
The hashDist function prints a length of each linked 
list in the hash table
--------------------------------------------------*/
void hashDist(struct node** Table)
{
	for(int i=0; i < SIZE; i++){
		int length = listLen(Table[i]);	// returns length of one list
		printf("CELL %d length: %d\n", i, length);
	}
	return;
}

/*----------------------------------------------------
the hashFind function uses the hash function to figure
out where in the hash table to look for a plate
----------------------------------------------------*/
int hashFind(struct node** Table, char *plate, char *first, char *last)
{
	int index, status;

	index = hash(plate);	//uses hash to find where to look in list
	
	status = listFind(Table[index], plate, first, last);
	if(status == 1) return 1;	//success
	if(status == 0) return 0;	//fail
}

/*-----------------------------------------------
hashFree function frees the memory allocated for
each data feild in node, each node, and the table
-----------------------------------------------*/
void hashFree(struct node** Table)
{
	for(int i=0; i < SIZE; i++){
		listFree(Table[i]);
	}
	free(Table);	//frees mem allocated for table
	return;
}
