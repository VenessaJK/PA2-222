#include "plate.h"

/*-----------------------------
initializing a sentinal node
and returning it to the array
of pointers to sent
-----------------------------*/
struct node *listInit()
{
	struct node *sent;
	sent = malloc(sizeof(struct node));
	
	sent->plate = malloc(8*sizeof(char));	//allocated memory for 
	sent->first = malloc(9*sizeof(char));	//sentinal data, thats
	sent->last = malloc(5*sizeof(char));	//why magic nums used

	strcpy(sent->plate, "000-000");
	strcpy(sent->first, "SENTINAL");
	strcpy(sent->last, "NODE");
	sent->next = NULL;

	return(sent);
}

/*------------------------------------
list add function adds to the linked
list, at the beginning
------------------------------------*/
void listAdd(struct node* sent, char *plateNum, char *firstname, char *lastname)
{
	struct node* new;
	new = malloc(sizeof(struct node));

	new->plate = malloc((strlen(plateNum)+1) * sizeof(char)); //must add 1 to strlen
	new->first = malloc((strlen(firstname)+1) * sizeof(char));//bc need to account
	new->last = malloc((strlen(lastname)+1) * sizeof(char));  //for null char

	strcpy(new->plate, plateNum);  //copying data to new
	strcpy(new->first, firstname); //node in list
	strcpy(new->last, lastname);

	new->next = sent->next;		//rearranging ptrs
	sent->next = new;

	return;
}

/*-----------------------------------------
listPrint function prints each data feild
in each node
-----------------------------------------*/
void listPrint(struct node* sent)
{
	struct node* temp;
	temp = sent->next;
	while(temp != NULL){	//until temp points at a null node, print each node
		printf("Plate: %s  Full Name: %s, %s\n", temp->plate, temp->first, temp->last);
		temp = temp->next;
	}
	return;
}

/*---------------------------------------
listLen function keeps count as loop goes
through each node until temp reaches null
---------------------------------------*/
int listLen(struct node* sent)
{
	int i=0;
	struct node* temp;
	temp = sent->next;
	while(temp != NULL){
		i++;
		temp = temp->next;
	}
	return i;
}

/*-------------------------------------
listFind function uses strcmp to find a 
plate in a linked list and if found, it
returns a 1 
-------------------------------------*/
int listFind(struct node* sent, char *plateNum, char *firstname, char *lastname)
{
	struct node* temp;
	temp = sent->next;	
	while(temp != NULL){
		if(strcmp(temp->plate, plateNum) == 0){
			strcpy(firstname, temp->first);
			strcpy(lastname, temp->last);
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

/*-------------------------------------
listFree function frees the memory 
allocated for each data feild in a node 
and the node itself
-------------------------------------*/
void listFree(struct node* sent)
{
	struct node* temp;
	temp = sent->next;
	while(temp != NULL){
		free(sent->plate);
		free(sent->first);
		free(sent->last);
		free(sent);
		sent = temp;
		temp = temp->next;
	}
	free(sent->plate);	//need to release last
        free(sent->first);	//node after while 
        free(sent->last);	//loop reaches null
        free(sent);
	return;
}