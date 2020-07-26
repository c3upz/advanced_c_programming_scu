//self made header inclusion
#include "defs.h"

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
  NODE* temp;

  temp = head;

  //header
  printf("\nName    Group Size\n--------------------");
  while(temp != NULL){
      printf("\n%-6s\t   %d", temp->groupName, temp->groupSize);
      temp = temp->next;
  }
}

void checkSize(void){
  int userNum;

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

int check_duplicate(char *tName){

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

void listBackwards(NODE *p){
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
