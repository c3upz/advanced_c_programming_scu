#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int numOfEvens(FILE*);

int main(void){
    FILE* fp;
    //fp = fopen("testfile.txt", "br");
    int counter = numOfEvens(fp);
    printf("%d", counter);
}


int numOfEvens(FILE *fPointer){

    fPointer = fopen("test.bin", "rb");

    if(fPointer == NULL){
        printf("error\n");
        return 0;
    }

    //printf("flag\n");

    fseek(fPointer, 0, SEEK_END);

    int size = ftell(fPointer);

    rewind(fPointer);

    int counter = 0;
    int temp[20];
    int total = 0;
    int x;

    printf("%d\n", size);

    fread(temp, sizeof(int), size/4, fPointer);

    int i;

    for(i = 0; i < size/4; i++){
        printf("%d \n", temp[i]);
        total += temp[i];
    }

    counter = total/(size/4);

    fclose(fPointer);
    return counter;

}
