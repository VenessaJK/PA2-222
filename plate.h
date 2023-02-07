#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char *plate;
    char *first;
    char *last;
    struct node *next;
};

struct node** hashInit(int );

void hashAdd(struct node**, char*, char*, char*);

int hashFind(struct node** hashTable,
                         char *plate,
                         char *first,
                         char *last);

void hashDump(struct node** hashTable, int n);

void hashDist(struct node** hashTable);

void hashFree(struct node** hashTable);

int hash(char *);

struct node* listInit();

void listAdd(struct node*, char*, char*, char*);

int listFind(struct node*, char*, char*, char*);

int listLen(struct node *sent);

void listPrint(struct node *sent);

void listFree(struct node *sent);