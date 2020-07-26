#include <stdio.h>
#include <stdlib.h>

int nwords(char*);

int main(void){
    
    char name[20] = "testfile.txt";

    int numofa = 0;

    numofa = nwords(name);
    printf("\n%d", numofa);

}

int nwords(char *name){
    int counter = 0;
    FILE *fp;
    fp = fopen(name, "r");

    if(fp == NULL){
        printf("error");
        exit(0);
    }

    char word[50], *p;

    while(!feof(fp)){
        fscanf(fp, "%s", word);
        p = word;

        while(*p != '\0'){
            p++;
        }

        if(*(p-1) == 'A'){
            printf("%s\n", word);
            counter++;
        }
    }

    fclose(fp);
    return counter;
}
