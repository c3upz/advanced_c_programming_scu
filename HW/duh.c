#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//functions
int numOfWords(char*);


//This program should count the number of words in a textfile
int main(int argc, char *argv[]){
  printf("what the");
  int numberOfWords;


  if(argc > 2 || argc < 2){ //making sure the user gave us a file to read from
      printf("file missing");
      return -1;
  }

  numberOfWords = numOfWords(argv[1]);

  printf("%d total words", numberOfWords);



}

int numOfWords(char *fileName){
  int totalNum = 0;
  char temp[20]; //should replace with max size later

  FILE *fp = NULL; //creating file pointer
  fp = fopen(fileName, "r"); //opening file
  printf("open");

  if(fp == NULL){ //checking if file could be opened
    printf("\nerror\n");
    exit(0);
  }

  while(fscanf(fp, "%s", temp) == 1){
    printf("\nin loop\n ");
    totalNum++;
  }


  fclose(fp);
  return totalNum;
}
