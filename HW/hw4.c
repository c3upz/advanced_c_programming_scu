#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NODE struct Node


struct Node{
    int number;
    NODE *next;
    NODE *previous;  
};

NODE *tail = NULL;
NODE *head = NULL;

//function declarations
void insert(NODE*);

int main(){
    NODE *numP;
    for(;;){
        if((numP = (NODE*)malloc(sizeof(NODE))) == (NODE*)NULL){
            printf("Error has occured");
            return 0;
        }

        int rNum = 0; //requested number
        printf("\nAt what number would you like to insert?");
        scanf("%d", &rNum);
        numP->number = rNum;
        //function to insert a node to the left
        insert(numP);
    
        NODE *printerP = head;
        while(printerP != NULL){
            printf("%d ", printerP->number);
            printerP = printerP->next;
        }
    }

}

void insert(NODE* numP){ 
    //first case (no nodes yet)
    if(head == NULL){
        head = numP;
        tail = numP;
        head->next = NULL;
        tail->next = NULL;
        head->previous = NULL;
        tail->previous = NULL;
    }
    //second case (want to insert to left of head)
    else if(numP == head){
        numP->next = head;
        numP->previous = NULL;
        head->previous = numP;
        head = numP;

    }
    //third case (want to insert to left of tail)
    else if(numP == tail){
        numP->next = tail;
        numP->previous = tail;
        (tail->previous)->next = numP;
        tail->previous = numP;
    }
    else{
        NODE *trav = head->next;
        while(trav != NULL){
           if(numP == trav){
                numP->next = trav;
                numP->previous = trav->previous;
                (trav->previous)->next = numP;
                trav->previous= numP;
           }
        }

        if(trav == NULL){
            numP->next = NULL;
            numP->previous = tail;
            tail->next = numP;
        }
    }

}



