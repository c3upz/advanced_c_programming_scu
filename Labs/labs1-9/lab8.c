#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum{
    true = 1, false = 0
}bool;

//@ChrisGerbino
//COEN11

//functions

void insert(char*, int);
void write_file(char*);
void read_file(char*);
void removeGroup(void);
void list(void);
void printMenu(void);
void checkSize(void);
int check_duplicate(char*);

//linked list
#define NODE struct Node
struct Node{
    char groupName[10];
    int groupSize;
    NODE *next;
};

void listBackwards(NODE*);
void namesBackward(char*);
void freeNodes(NODE*);

NODE *head = NULL;
NODE *tail = NULL;

int main(int argc, char *argv[]){

    //if argc = 1 then that means the user didnt give us a file to open/read/insert stuff too so the program will end
    if(argc == 1){
        printf("file missing");
        return 1;
    }else{
        //we want to read file bc if the file has information we want to put that in our linked list before we do anything else
        read_file(argv[1]);
    }

    int userAction = 0;
    char tempName[10];
    int size = 0;

    for(;;){
        printMenu(); //outputing user options
        scanf("%d", &userAction); //storing there choice
        bool notDupName = false;
        switch(userAction){

            case(1):

                do{
                    /*case 1-- will be dealing with inserting names to the list once the txt file has been copied to the linked list

                    (note)-- insert function is only going to append names and group sizes to the end of the list so we must
                    ask for name and size outside of the function
                    */

                    printf("\nGroup name: ");
                    scanf("%s", tempName);

                    if((check_duplicate(tempName)) ==  0){ //if check returns 1 that means the name has already been taken
                        notDupName = true;
                    }
                }while(!notDupName);
                //program should only execute this code if it passes check_duplicate
                printf("\nGroup size: ");
                scanf("%d", &size);


                //calling insert bc we have a groupName(not duplicate), and groupSize
                insert(tempName, size);
                break;

            case(2):
                removeGroup();
                break;

            case(3):
                list();
                break;

            case(4):
                checkSize();
                break;

            case(5):
                listBackwards(head);
                break;

            case(6): ;
                NODE *z;
                z = head;

                while(z != NULL){
                    namesBackward(z->groupName);
                    printf("\n");
                    z = z->next;
                }
       
                break;

            case(9):
                //need to insert all information in linked list to the file
                write_file(argv[1]);
                freeNodes(head);
                return 1;
                break;

            default:
                printf("Invalid input");

        }
    }
}

void printMenu(void){
    printf("\n\n1: insert\n2: remove\n3: list\n4: size\n5: list backwards\n6: reverse names\n9: quit\n");
}


void insert(char *tName, int gSize){

    NODE *temp;

    if((temp = (NODE*)malloc(sizeof(NODE))) == (NODE*)NULL){
        printf("eroor");
        return;
    }

    strcpy(temp->groupName, tName);
    temp->groupSize = gSize;

    //case 1 (no nodes in linked list)
    if(head == NULL){
        head = temp;
        tail = temp;
        head->next = NULL;
        tail->next = NULL;
    }

    //case 2 (nodes in linked list)
    if(head != NULL){
        tail->next = temp;
        temp->next = NULL;
        tail = temp;
    }
}


void read_file(char *fileName){
    int gSize;
    char gName[20];
    FILE *fPointer = NULL;
    FILE *header = NULL;
    fPointer = fopen(fileName, "r");

    if(fPointer == NULL){
        return;
    }

    fseek(fPointer, 34, SEEK_SET);
    while(fscanf(fPointer, "%s%d", gName, &gSize) == 2){
        //inserting to linked list
        insert(gName, gSize);
    }
    fclose(fPointer);
}


void list(void){
    NODE* temp;

    temp = head;

    //header
    printf("\nName    Group Size\n--------------------");
    while(temp != NULL){
        printf("\n%-6s\t   %d", temp->groupName, temp->groupSize);
        temp = temp->next;
    }
}

void removeGroup(void){
    int openSpaces = 0;
    printf("Please enter the number of open spaces available: ");
    scanf("%d", &openSpaces);

    NODE *rlistP = head;
    NODE *q = head;

    while(rlistP != NULL){

        if(rlistP->groupSize <= openSpaces){

            if(rlistP == head){
                openSpaces -= rlistP->groupSize;
                printf("\n%s's group  of size %d filled open spaces\n", rlistP->groupName, rlistP->groupSize);
                head = head->next;
                free(rlistP);
                rlistP = q = head;

            }else if(rlistP == tail){
                openSpaces -= rlistP->groupSize;
                printf("\n%s's group  of size %d filled open spaces\n", rlistP->groupName, rlistP->groupSize);
                free(rlistP);
                tail = q;
                q->next = NULL;
                rlistP = tail;
            }else{
                openSpaces -= rlistP->groupSize;
                printf("\n%s's group  of size %d filled open spaces\n", rlistP->groupName, rlistP->groupSize);
                q->next = rlistP->next;
                free(rlistP);
                rlistP = q;
            }

        }else{
            q = rlistP;
            rlistP = rlistP->next;
        }
    }
}

void checkSize(void){
    int userNum;
    int i;

    printf("\nEnter a size: ");
    scanf("%d", &userNum);

    printf("\nThese groups have size's <= to %d", userNum);

    NODE* rlistP;
    rlistP = head;
    while(rlistP != NULL){
        if((rlistP->groupSize) <= userNum){
            printf("\n%s's group of size %d", (rlistP->groupName),(rlistP->groupSize));
        }
        rlistP = rlistP->next;
    }

}

int check_duplicate(char* tName){
    int i;
    NODE* rlistP;
    rlistP = head;
    while(rlistP != NULL){
        if(strcmp(tName, rlistP->groupName) == 0){
            printf("name is already in use\n");
            return 1;
        }
        rlistP = rlistP->next;
    }
    return 0;
}

void write_file(char *fileName){
    FILE *fPointer;

    fPointer = fopen(fileName, "w");\

    if(fPointer == NULL){
        printf("error");
        exit(0);
    }

    fprintf(fPointer, "Name\t   Size\n--------------------\n");

    NODE *p;
    p = head;

    while(p != NULL){
        fprintf(fPointer, "%-7s\t   %d\n", p->groupName, p->groupSize);
        p = p->next;
    }

    fclose(fPointer);
}

void listBackwards(NODE* p){
    if(p == NULL) return;

    else{
        listBackwards(p->next);
    }

    printf("\n%s  %d", p->groupName, p->groupSize);

}

void namesBackward(char *p){    
    
    if(*p == '\0') return;

    else{
        namesBackward(p+1);
        printf("%c", *p);
    }

    return;
}


void freeNodes(NODE *p){
    //in this function we just want to free all nodes as this will be called only when the program
    //is quitting
    if(p == NULL) return;

    else{
        freeNodes(p->next);
        free(p);
    }

}

