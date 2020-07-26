#include<stdio.h>
#include<string.h>
//@ChrisGerbino
//COEN11


//functions
void insert(void);
void removeGroup(void);
void list(void);
void printMenu(void);

//global variables
char groupName[10][20];
int groupSize[20];
int groupCounter = 0;

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

            case(9):
                return 1;
                break;

            default:
                printf("\nInvalid Input");


        }//switch

    }//for
    


}//main



void printMenu(void){
    printf("\n\n1: Insert a Group\n2: Remove a Group\n3: List Groups\n9: Quit Program\n");
}

void insert(void){
    char tempName[20];

    if(groupCounter < 10){ //making sure there is room for the reservation on the list
        groupCounter++; //if there is room then I want to increase the amount of groups

        printf("\nPlease enter your group name: ");
        scanf("%s", tempName); //storing in temp variable bc i need to check if this name is avaliable

        for(int i = 0; i < 10; i++){//comparing the inputed name with the liist of names... if name is same the function should return to main menu
            if(strcmp(tempName, groupName[i]) == 0){
                printf("\nThis name is already taken! Sorry!\n");
                groupCounter--;
                return;
            }
        }
        
        strcpy(groupName[groupCounter - 1], tempName); //if it passes through the code above the name is okay to put in global array

        printf("\nHow many people are in your group? "); //filling size area
        scanf("%d", &groupSize[groupCounter - 1]);
            
    }
}


void removeGroup(void){
    int openSpaces = 0;
    printf("Please enter the number of open spaces available: ");
    scanf("%d", &openSpaces);
    
    while(openSpaces > 0){
        for(int i = 0; i < 10; i++){
            if(groupSize[i] <= openSpaces){
                openSpaces -= groupSize[i];
                //printf("%d", openSpaces);
                
                printf("\n%s's group  of size %d filled open spaces\n", groupName[i], groupSize[i]);

                for(int n = i; n < groupCounter; n++){
                    strcpy(groupName[n], groupName[n + 1]);
                    groupSize[n] = groupSize[n + 1];
                }
                groupCounter--;
            
            break;
            }
        }
    }
}
void list(void){
    for(int i = 0; i < groupCounter; i++){
        printf("\n%s, %d people", groupName[i], groupSize[i]);
            
    }

}
