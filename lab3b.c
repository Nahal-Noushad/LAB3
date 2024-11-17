#include <stdio.h> 
#include <stdbool.h> 

int main(void) {
    int k = 0; // Counter for unprocessed transactions
    int balance = 1000; // Initial account balance
    int transactions[] = {200, -150, -500, -400, -50, -100, 300, 500, 800}; // Array of transactions
    int length = sizeof(transactions) / sizeof(transactions[0]); // Number of transactions
    int tobeprocessed[10]; // Array to store unprocessed transactions

    // Process each transaction
    for (int i = 0; i < length; i++) {
        if (transactions[i] >= 0) // Deposit transactions
            balance = balance + transactions[i];
        if (transactions[i] < 0) { // Withdrawal transactions
            if (balance < (-transactions[i])) { // Check if sufficient balance
                printf("INVALID TRANSACTION HAS OCCURED\n");
                tobeprocessed[k] = transactions[i]; // Add invalid transaction to list
                k++;
            } else {
                balance = balance + transactions[i]; // Deduct valid transaction
            }

            if (balance == 0) { // Stop processing if balance reaches zero
                for (int m = i; m <= length; m++) {
                    tobeprocessed[k] = transactions[m + 1]; // Add remaining transactions to unprocessed list
                    k++;
                }
                k = k - 2; // Adjust counter
                printf("No further transactions can be processed\n");
                break;
            }
        }
    }

    // Print final balance
    printf("final amount= %d\n", balance);

    // Print unprocessed transactions
    printf("Unprocessed transaction below:\n");
    for (int j = 0; j < k; j++) {
        printf("%d\n", tobeprocessed[j]);
    }
}
