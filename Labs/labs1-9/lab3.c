#include<stdio.h>
#include<string.h>
//@ChrisGerbino
//COEN11


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
typedef struct list{
    char groupName[10];
    int groupSize;
}LIST;

LIST resList[10], *rlistP;



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

    if(groupCounter < 10){ //making sure there is room for the reservation on the list
        groupCounter++; //if there is room then I want to increase the amount of groups

        printf("\nPlease enter your group name: ");
        scanf("%s", tempName); //storing in temp variable bc i need to check if this name is avaliable

        rlistP = resList; //setting pointer(rlistP) = to the datastructure which holds peoples info

        if(check_duplicate(tempName) == 0){
            strcpy(rlistP->groupName, tempName); //if it passes through the code above the name is okay to put in global array
        }else{
            return;
        }

        printf("\nHow many people are in your group? "); //filling size area
        scanf("%d", &(rlistP->groupSize));
            
    }
}


void removeGroup(void){
    int openSpaces = 0;
    printf("Please enter the number of open spaces available: ");
    scanf("%d", &openSpaces);
    
    rlistP = resList;
    for(int i = 0; i < groupCounter; i++){
        if(rlistP->groupSize <= openSpaces){
            openSpaces -= rlistP->groupSize;
            //printf("%d", i);
                
            printf("\n%s's group  of size %d filled open spaces\n", rlistP->groupName, rlistP->groupSize);
            LIST *q;
            q = rlistP;
            q++;
            for(int n = i; n < groupCounter; n++, rlistP++, q++){
                //rlistP = &resList[n];//not sure if this is nessasary but put it here just to make sure that the pointer is pointing to the correct place in arr resList
                strcpy(rlistP->groupName, (q)->groupName);
                rlistP->groupSize = (q) -> groupSize;
            }
            groupCounter--;
            i--;     
            rlistP = resList;
            continue;
        }
        rlistP++;
    }
    
}
void list(void){
    rlistP = resList;
    for(int i = 0; i < groupCounter; i++, rlistP++){
        printf("\n%s, %d people", rlistP->groupName, rlistP->groupSize);
            
    }

}

int check_duplicate(char* tName){
    int i;

    for(i = 0; i < groupCounter - 1; i++, rlistP++){
        if(strcmp(tName, rlistP->groupName) == 0){
            printf("Sorry this name is already taken");
            groupCounter--;
            return 1;
        }
    }
    return 0;
}

void checkSize(void){
    int userNum; 
    int i;

    printf("\nEnter a size: ");
    scanf("%d", &userNum);

    printf("\nThese groups have size's <= to %d", userNum);

    rlistP = resList;
    for(i = 0; i < groupCounter; i++, rlistP++){
        if((rlistP->groupSize) <= userNum){
            printf("\n%s's group of size %d", (rlistP->groupName),(rlistP->groupSize));
        }
    }

}
