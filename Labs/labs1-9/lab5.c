#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//@ChrisGerbino
//COEN11
#define NODE struct Node

//functions
void insert(void);
void removeGroup(void);
void list(void);
void printMenu(void);
void checkSize(void);
int check_duplicate(char*);

//global variables
int groupCounter = 0;

//struct to combine groupName and groupSize
struct Node{
    char groupName[10];
    int groupSize;
    NODE *next;
};

NODE *head = NULL; 
NODE *tail = NULL;


int main(){
    int userAction = 0;

    for(;;){ 
        printMenu();
        scanf("%d", &userAction);
        
        switch(userAction){
            case(1):
                insert();
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

            case(9):
                return 1;
                break;

            default:
                printf("\nInvalid Input");


        }//switch

    }//for
    


}//main



void printMenu(void){
    printf("\n\n1: Insert a Group\n2: Remove a Group\n3: List Groups\n4: Check Size \n9: Quit Program\n");
}

void insert(void){
    char tempName[20];

    printf("\nPlease enter your group name: ");
    scanf("%s", tempName); //storing in temp variable bc i need to check if this name is avaliable
    
    NODE *rlistP;
    if(check_duplicate(tempName) == 0){
        if((rlistP = (NODE*)malloc(sizeof(NODE))) == (NODE*)NULL){
            printf("Error");
                return;
        }else{
            if(head == NULL){
                strcpy(rlistP->groupName, tempName);
                head = tail = rlistP;
                    
            }else{
                strcpy(rlistP->groupName, tempName);
                tail->next = rlistP;
                tail = tail->next; 
            }
        }
            
    }else{
        return;
    }

    printf("\nHow many people are in your group? "); //filling size area
    scanf("%d", &(tail->groupSize));
            
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
void list(void){
    NODE* rlistP;
    rlistP = head;
    while(rlistP != NULL){
        printf("\n%s, %d people", rlistP->groupName, rlistP->groupSize);
        rlistP = rlistP->next;    
    }

}

int check_duplicate(char* tName){
    int i;
    NODE* rlistP;
    rlistP = head;
    while(rlistP != NULL){
        if(strcmp(tName, rlistP->groupName) == 0){
            printf("Sorry this name is already taken");
            groupCounter--;
            return 1;
        }
        rlistP = rlistP->next;
    }
    return 0;
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
