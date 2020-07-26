//@ChrisGerbino
//COEN11

//header file inclusion
#include "defs.h"

//defining boolean (looking back on this project I should have just inluded
//the boolean lib)
typedef enum{
    true = 1, false = 0
}bool;

//linked list is defined in defs.h

//nodes
NODE *head = NULL;
NODE *tail = NULL;

//why do i have to redefine?
pthread_mutex_t mutex;

//function
void printMenu(void);


int main(int argc, char *argv[]){

    //if argc = 1 then that means the user didnt give us a file to open/read/insert stuff too so the program will end
    if(argc < 4){
        printf("file missing");
        return 1;
    }

    //create the thread var
    pthread_t thr;

    //initialize the thread
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thr, NULL, auto_save, (void*)argv[2]);


    //we want to read file bc if the file has information we want to put that in our linked list before we do anything else
    read_file(argv[1], argv[3]);

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

            case(7):
                //printf("flag in case\n");
                read_auto(argv[2]);
                break;

            case(9):
                //need to insert all information in linked list to the file
                write_file(argv[1], argv[3]);
                freeNodes(head);
                pthread_mutex_lock(&mutex);
                pthread_cancel(thr);
                pthread_mutex_unlock(&mutex);
                return 1;
                break;

            default:
                printf("Invalid input");

        }
    }
}

void printMenu(void){
    printf("\n\n1: insert\n2: remove\n3: list\n4: size\n5: list backwards\n6: reverse names\n7: auto_read\n9: quit\n");
}
