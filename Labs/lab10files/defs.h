#ifndef DEFS_H_
#define DEFS_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

//linked list def
#define NODE struct Node
//must define and declare here otherwise no files beside main will know what 'Node' is
struct Node{
    char groupName[10];
    int groupSize;
    NODE *next;
};


//function defs
void insert(char*, int);
void write_file(char*, char*);
void read_file(char*, char*);
void removeGroup(void);
void list(void);
void checkSize(void);
int check_duplicate(char*);
void listBackwards(NODE*);
void namesBackward(char*);
void freeNodes(NODE*);
void read_auto(char*);

//thread function
void *auto_save(void*);

//global vars
extern pthread_mutex_t mutex;

//nodes
extern NODE *head;
extern NODE *tail;




#endif //DEFS_H_
