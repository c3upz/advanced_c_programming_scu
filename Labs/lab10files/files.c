//self made header inclusion
#include "defs.h"


void write_file(char *fileName, char *key){
  FILE *fPointer;

  fPointer = fopen(fileName, "w");\

  if(fPointer == NULL){
      printf("error");
      exit(0);
  }

  fprintf(fPointer, "Name\t   Size\n--------------------\n");

  NODE *p;
  p = head;

  //we know want to encrypt each character we print
  while(p != NULL){
      int eInt = 0; //encrypted groupSize var
      int i = 0;
      int len = 0;

      len = strlen(p->groupName);

      for(i = 0; i < len; i++){
        p->groupName[i] ^= *key;
      }



      eInt = p->groupSize ^ *key; //calculating eName

      fprintf(fPointer, "%-7s\t   %d\n", p->groupName, eInt);

      p = p->next;
  }

  fclose(fPointer);

}

void read_file(char *fileName, char *key){
  int gSize;
  char gName[20];
  FILE *fPointer = NULL;
  fPointer = fopen(fileName, "r");

  if(fPointer == NULL){
      return;
  }

  fseek(fPointer, 34, SEEK_SET);

  while(fscanf(fPointer, "%s%d", gName, &gSize) == 2){
      long len;
      int i = 0;

      len = strlen(gName);

      for(i = 0; i < len; i++){
        gName[i] ^= *key;
      }

      gSize ^= *key;

      //inserting to linked list
      insert(gName, gSize);
  }
  fclose(fPointer);

}


void read_auto(char *name){
  FILE* fp;
  NODE p;

  fp = fopen(name, "rb");

  if(fp == NULL){
      printf("missing file\n");
      return;
  }

  pthread_mutex_lock(&mutex);
  while(fread(&p, sizeof(NODE), 1, fp) == 1){
      printf("%s  %d\n", p.groupName, p.groupSize);
  }
  fclose(fp);
  pthread_mutex_unlock(&mutex);


}

void *auto_save(void *bfilename){
  FILE *fp;
  NODE *p;
  for(;;){
    pthread_mutex_lock(&mutex);
    fp = fopen(bfilename, "wb");

  if(fp == NULL){
      pthread_mutex_unlock(&mutex);
      return 0;
  }

  p = head;

  while(p != NULL){
      fwrite(p, sizeof(NODE), 1, fp);
      p = p->next;
  }
  fclose(fp);
  pthread_mutex_unlock(&mutex);

  sleep(5);
}


  return bfilename;

}
