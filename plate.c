#include "plate.h"

int main(int argc, char **argv)
{
        int SIZE, cell;
        char *filename, plate[257], first[257], last[257], line[257];


	//parsing command line inputs
        if(argc <= 1){				// if args less than one, return
                printf("MISSING ARGUMENTS.\n");
                return 1;
        } else if(argc == 2){			//if two args, default table size is 50
                SIZE = 50;
                filename = argv[1];
        } else if(argc == 3){			//if 3 args, usr chooses table size
                sscanf(argv[1], "%d", &SIZE);
                filename = argv[2];
        } else{					//more than 3 args, not valid, return
                printf("TOO MANY ARGUMENTS.\n");
		return 1;
        }


    //initializing array (table) of linked lists
	struct node** Table = hashInit(SIZE);	


	//opening file and storing data in hash table
	FILE *fp = fopen(filename, "r");
	if(fp == NULL){				//return if file can't be opened
		printf("File couldn't be opened\n");
		return 1;
	}
	while(fgets(line, 257, fp) != NULL){	//max length for line in file is 257
		sscanf(line, "%s %s %s", plate, first, last); //store data from file 
		
		hashAdd(Table, plate, first, last);	//adds data to the hash table
	}
	fclose(fp);


	//taking commands and searching hash data
	while(1){				//ask for input till usr exits
		int n, status1, status2;
		char usr[120], command[120], *status;

		printf("Enter a command or plate: ");
		status = fgets(usr, 120, stdin);//status check for EOF
		if(status == NULL){		
			printf("\n");		//add new line bfr exiting	
			hashFree(Table);	//frees all dynamically allocated memory (table, linked list)
			return 0;
		}
		strcpy(plate, usr);     //doing this bfr parse in case no commands, and need to use full usr input
		if(strlen(plate) > 1) plate[strlen(plate)-1] = '\0';	//need to remove \n from usr bc hashfind will not work otherwise
                                                                //and take care of edge case where usr only inserts a \n
		status1 = sscanf(usr, "%s %d", command, &n); //nts: cant parse from var usr and store in same var
	
		if((status1 == 1) && (strcmp(command, "*DUMP") == 0)){	//if stat is 1 then, check for command
			n = -1;			//bc stat is 1, usr didn't pass a cell num so set flag (-1)
			hashDump(Table, n);	//hashDump will dump entire contents of table

		} else if((status1 == 2) && (strcmp(command, "*DUMP") == 0)){
			if(n >= 0 && n <= SIZE){ //n needs to be in range of table size
				hashDump(Table, n);//dumps content of one cell
			} else{
				printf("Cell number out of range (0 to %d).\n", SIZE);
			}
		} else if((status1 == 1) && (strcmp(command, "*DIST") == 0)){
			hashDist(Table); 	//dumps length of hash table
		} else{
			status2 = hashFind(Table, plate, first, last);	//first and last will have contents of 
									//last line in file but will be overwritten
			if(status2 == 0) printf("Plate not found.\n");
			if(status2 == 1){
				printf("Firstname: %s\n", first);
				printf("Lastname: %s\n", last);
			}
		} 
	}
}