#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//@ChrisGerbino
//COEN11 Thurs 1415-17

#define POINTERS struct pointers
#define NODE struct Node

struct Node{
    char groupName[15];
    int groupSize;
    NODE *next;
};

struct pointers{
    NODE *head;
    NODE *tail;
};

POINTERS resList[4];
/*[0] = groupSize 1-2
 *[1] = groupSize 3-4
 *[2] = groupSize 5-6
 *[3] = groupSize 7+
 */

//functions 
void insert(void);
void removeGroup(void);
void list(void);
void checkSize(void);
int check_duplicate(char*);
void printMenu(void);


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

        }

    }


}

void insert(void){
    char tempName[10];
    NODE *temp = NULL;

    printf("\nGroup name: ");
    
    scanf("%s", tempName); //scanning in name to temp var to check duplicate


    if(check_duplicate(tempName) == 0){ //check_duplicate returns 0 if it is not a duplicate
        //allocating memory for temp, if it cant allocate it will end the program
        if((temp = (NODE*)malloc(sizeof(NODE))) == (NODE*)NULL){
            printf("Error");
            return;
        }
    }else{ //if name is already taken
        printf("That name has already been taken");\
        return;
    }

    //if the function has not 'returned' by now that means there was no temp name and memory has been allocated
    printf("\nGroup size: ");
    scanf("%d", &temp->groupSize);

    //we now know no duplicates, groupSize, and memory allocation was sucessful so we can put this entry into our array 
    strcpy(temp->groupName, tempName);

    //inserting temp into array due to the group size.. [0] = 1||2, [1] = 3||4, [2] = 5||6, [3] = >7
    if(temp->groupSize == 1 || temp->groupSize == 2){
        if(resList[0].head == NULL){
             temp->next = NULL;
             resList[0].head = resList[0].tail = temp;
        }else{
            temp->next = NULL;
            resList[0].tail->next = temp;
            resList[0].tail = temp;
        }
            
    }else if(temp->groupSize == 3 || temp->groupSize == 4){
       if(resList[1].head == NULL){
            temp->next = NULL;
            resList[1].head = resList[1].tail = temp;
       }else{
           temp->next = NULL;
           resList[1].tail->next = temp;
           resList[1].tail = temp;
       }

    }else if(temp->groupSize == 5 || temp->groupSize == 6){
       if(resList[2].head == NULL){
            temp->next = NULL;
            resList[2].head = resList[2].tail = temp;
       }else{
           temp->next = NULL;
           resList[2].tail->next = temp;
           resList[2].tail = temp;
       }

    }else if(temp->groupSize >= 7){
        if(resList[3].head == NULL){
             temp->next = NULL;
             resList[3].head = resList[3].tail = temp;
        }else{
            temp->next = NULL;
            resList[3].tail->next = temp;
            resList[3].tail = temp;
        }

    }else{
        printf("\nInvalid group size");
        return;
    }
}

void removeGroup(void){
    int openSpace = 0;

    printf("\nOpen spaces: ");
    scanf("%d", &openSpace);
    
    NODE *p;
    NODE *q;

    while(openSpace != 0){ //checking if there are still spaces open

        if(openSpace >= 1 && resList[0].head != NULL){//seeing if it should enter this array to remove groups (bc if open spaces < group range(ex 3-4) then we dont want to check
            if((openSpace > 0 && openSpace < 3) && resList[0].head == NULL){
                openSpace = 0;
            }
            
            p = resList[0].head;
            q = resList[0].head; 
            while(p != NULL){

                if((p->groupSize) <= openSpace){
                    openSpace -= (p->groupSize);
                    printf("%d", openSpace);
                    printf("\n%s with size of %d filled open space(s)", p->groupName, p->groupSize);
                    
                    if(p == resList[0].head){ //case 1: if the spot filled was the head of that index of nodes
                        p = p->next;
                        resList[0].head = p;
                        free(q);
                        q = p;
                    }else if(p == resList[0].tail){//case 2: if tail is the node that filled spots
                        q->next = NULL;
                        resList[0].tail = q;
                        free(p);
                        p = q;
                    }else{ //case 3: if a node in the middle is the one that filled spots
                        q->next = p->next;
                        free(p);
                        p = q->next;
                    }
                }else{
                    q = p;
                    p = p->next;
                    
                }
            }                                                                                                 
        }else if(openSpace >= 3 && resList[1].head != NULL){
            if((openSpace > 0 && openSpace < 5) && resList[1].head == NULL){
                openSpace = 0;
            }
            
            p = resList[1].head;
            q = resList[1].head; 
            while(p != NULL){
                                                                                                              
                if((p->groupSize) <= openSpace){
                    openSpace -= (p->groupSize);
                    printf("\n%s with size of %d filled open space(s)", p->groupName, p->groupSize);
                    
                    if(p == resList[1].head){ //case 1: if the spot filled was the head of that index of nodes
                        p = p->next;
                        resList[1].head = p;
                        free(q);
                        q = p;
                    }else if(p == resList[1].tail){//case 2: if tail is the node that filled spots
                        q->next = NULL;
                        resList[1].tail = q;
                        free(p);
                        p = q;
                    }else{ //case 3: if a node in the middle is the one that filled spots
                        q->next = p->next;
                        free(p);
                        p = q->next;
                    }
                }else{
                    q = p;
                    p = p->next;
                    
                }
            }                                                                                               
        }else if(openSpace >= 5 && resList[2].head != NULL){
            if((openSpace > 0 && openSpace < 7) && resList[2].head == NULL){
                openSpace = 0;
            }
            
            p = resList[2].head;
            q = resList[2].head; 
            while(p != NULL){
                                                                                                              
                if((p->groupSize) <= openSpace){
                    openSpace -= (p->groupSize);
                    printf("\n%s with size of %d filled open space(s)", p->groupName, p->groupSize);
                    
                    if(p == resList[2].head){ //case 1: if the spot filled was the head of that index of nodes
                        p = p->next;
                        resList[2].head = p;
                        free(q);
                        q = p;
                    }else if(p == resList[2].tail){//case 2: if tail is the node that filled spots
                        q->next = NULL;
                        resList[2].tail = q;
                        free(p);
                        p = q;
                    }else{ //case 3: if a node in the middle is the one that filled spots
                        q->next = p->next;
                        free(p);
                        p = q->next;
                    }
                }else{
                    q = p;
                    p = p->next;
                    
                }
            }                                                                                               
        }else if(openSpace >= 7 && resList[3].head != NULL){
           if(resList[3].head == NULL){
               openSpace = 0;
           }
           
           p = resList[3].head;
           q = resList[3].head; 
           while(p != NULL){
                                                                                                             
               if((p->groupSize) <= openSpace){
                   openSpace -= (p->groupSize);
                   printf("\n%s with size of %d filled open space(s)", p->groupName, p->groupSize);
                   
                   if(p == resList[3].head){ //case 1: if the spot filled was the head of that index of nodes
                       p = p->next;
                       resList[3].head = p;
                       free(q);
                       q = p;
                   }else if(p == resList[3].tail){//case 2: if tail is the node that filled spots
                       q->next = NULL;
                       resList[3].tail = q;
                       free(p);
                       p = q;
                   }else{ //case 3: if a node in the middle is the one that filled spots
                       q->next = p->next;
                       free(p);
                       p = q->next;
                   }
               }else{
                   q = p;
                   p = p->next;
               }
           }                                                                                               
        }
    }

}

void printMenu(void){
    printf("\n1: Insert\n2: Remove\n3: List\n4: list size\n9: quit\n");
}

void checkSize(void){
    int size = 0;
    int i = 0;
    printf("\nSize: ");
    scanf("%d", &size);
    NODE *p;

    if(size > 6){
        p = resList[3].head;
        while(p != NULL){
            if(p->groupSize <= size){
                printf("\n%s's group of size %d", p->groupName, p->groupSize);
            }
            p = p->next;
        }
                
    }
    
    if(size > 4){
        p = resList[2].head;
        while(p != NULL){
            if(p->groupSize <= size){
                printf("\n%s's group of size %d", p->groupName, p->groupSize);
            }
            p = p->next;
        }

    }
    
    if(size > 2){
        p = resList[1].head;
        while(p != NULL){
            if(p->groupSize <= size){
                printf("\n%s's group of size %d", p->groupName, p->groupSize);
            }
            p = p->next;
        }
    }
    
    if(size > 0){
        p = resList[0].head;
        while(p != NULL){
            if(p->groupSize <= size){
                printf("\n%s's group of size %d", p->groupName, p->groupSize);
            }
            p = p->next;
        }
    }
}

int check_duplicate(char* tempName){
    POINTERS *p;
    NODE *traverse;
    int i;

    p = resList;

    for(i = 0; i < 4; i++, p++){
        traverse = resList[i].head;
        while(traverse != NULL){
            if(strcmp(traverse->groupName, tempName) == 0){
                return 1; 
            }
            traverse = traverse->next;
        }
    }
    return 0;
}

void list(void){
    //print names from each group, smallest group to largest group, names oldest to newest for each group
    int group = 1; //group is to help us print
    int index = 0;
    NODE *p;
    while(index < 4){
        p = resList[index].head;
        
        if(group == 7){
            printf("\nSize %d+:", group);
        }else{
            printf("\nSize %d - %d:", group, group+1);
        }

        while(p != NULL){
            printf("\n  %s    %d", p->groupName, p->groupSize);
            p = p->next;
        }
        printf("\n");

        group+=2;
        index++;
    }

}
