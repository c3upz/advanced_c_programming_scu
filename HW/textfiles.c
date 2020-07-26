#include <stdio.h>
#include <stdlib.h>

#define NODE struct Node

struct Node{
    int x;
    NODE *next;
};

NODE *head = NULL;
NODE *tail = NULL;

void oddNumbers(FILE*);
void writetext(FILE*);
void readnumbers(FILE*);
void writenumbers(FILE*);

int main(void){
    
    FILE *fPointer;

    writetext(fPointer);
    //readnumbers(fPointer);
    //writenumbers(fPointer);
    //oddNumbers(fPointer);
}

void writetext(FILE *fPointer){
    char words[20]; 
    
    fPointer = fopen("testfile.txt", "w+");
    
    if(fPointer == NULL){
        printf("Cant open the file");
        exit(0);
    }

    printf("What do you want to write in the file?");
    scanf("%s", words);

    fseek(fPointer, 30, SEEK_SET);

    fprintf(fPointer, "%s", words);

    fclose(fPointer);
}

void readnumbers(FILE *fPointer){
    NODE *temp;

    fPointer = fopen("testfile.txt", "r");
    
    if(fPointer == NULL){
        printf("Cannot open file");
        exit(0);
    }

    while(!feof(fPointer)){
        if((temp = (NODE*)malloc(sizeof(NODE))) == (NODE*)NULL){
            printf("ERROR");
            return;
        }
        fscanf(fPointer, "%d ", &temp->x);
        //case 1 if there are no nodes
        if(head == NULL){
            head = temp;
            tail = temp;
            head->next = NULL;
        }else{//case 2 there is a node already
            tail->next = temp;
            tail = temp;
            tail->next = NULL;
        }
    }

    temp = head;

    while(temp != NULL){
        printf("%d ", temp->x);
        temp = temp->next;
    }

    printf("run");
    fclose(fPointer);
}


void writenumbers(FILE *fPointer){
    

    fPointer = fopen("testfile.txt", "w");

    if(fPointer == NULL){
        printf("Error opening file");
        exit(0);
    }

    NODE* temp = head;

    while(temp!=NULL){
        fprintf(fPointer, "%d,", temp->x);

        temp = temp->next;
    }

    fclose(fPointer);

}



void oddNumbers(FILE *fPointer){
   fPointer = fopen("testfile.txt", "w");
   
   printf("run ");

   if(head == NULL){
        printf("empty");
   }
   
   if(fPointer == NULL){
        exit(0);
   }

    NODE* temp = head;

    while(temp != NULL){
        if(temp->x % 2 == 1){
            fprintf(fPointer, "%d..", temp->x);
        }
        temp = temp->next;
    }

    fclose(fPointer);
}
