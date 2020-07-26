#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int division();

int userAnswer = 0;

int main(){
    int divisor = 0;
    int quotient = 0;
    int dividend = 0;
    int numCorrect = 0;
    int percentCorrect = 0;

    srand((int)time(NULL));
    
    for(int i = 0; i < 10; i++){
        divisor = rand() % 12 + 1;
        quotient = rand() % 13;
        dividend = divisor * quotient;

        printf("%d / %d = ", dividend, divisor);
        scanf("%d", &userAnswer);

        if(division(dividend ,divisor, quotient) == 1){
            numCorrect++;
        
        }
        
    }
    percentCorrect = (numCorrect * 10);
    printf("\nYou got %d percent correct", percentCorrect);
}


int division(int a, int b, int c){
    if(userAnswer == c){
        printf("\nCorrect\n");
        return 1;
    }else{
        printf("\nWrong, the correct anwser is %d\n", c);
        
        return 0;
    }

}
