#include<stdio.h>
#include<string.h>
#include<stdlib.h>



int main(void){

    FILE *fp;

    fp = fopen("test.bin", "wb");

    if(fp == NULL){
        printf("error\n");
        return 1;
    }

    int arr[8] = {1,2,3,4,5,6,7,8};

    fwrite(arr, sizeof(int), 8, fp);

    printf("sucsessful");
}
