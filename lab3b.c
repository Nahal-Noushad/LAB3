#include <stdio.h> 
#include <stdbool.h> 

int main(void){
    int k = 0;
    int balance = 1000;
    int transactions[] = {200, -150, -500, -400, -50, -100, 300, 500};
    int length = sizeof(transactions) / sizeof(transactions[0]);
    int tobeprocessed[10];
    for (int i = 0; i < length; i++){
        if (transactions[i] >= 0)
        balance = balance + transactions[i];
    if (transactions[i] < 0){
        if (balance < (transactions[i]*(-1))){
            printf("INVALID TRANSACTION\n");
            tobeprocessed[k] = transactions[i];
            k++;
        }
        else {
        balance = balance + transactions[i];
        }
        if (balance == 0){
            for (int m = i; m <= length; m++){
            tobeprocessed[k] =  transactions[m+1];
            k++;
            }
            k = k - 2;
            printf("No further transactions can be processed\n");
            break;
        }
        

    }
}
printf("final amt= %d\n", balance);
    for (int j=0; j<k; j++){
        printf("%d\n",tobeprocessed[j]);
}
}