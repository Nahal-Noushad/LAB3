#include <stdio.h> 
#include <stdbool.h> 
#define SIZE 24
#define noRows 8
#define noCols 3

// Function prototypes
bool isValid(const int arr[], int length, int pos); // Check if position is valid
void remove_element(int arr[], int length, int pos); // Remove element from array
void insert_element(int arr[], int length, int pos, int value); // Insert element into array
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]); // Reshape 1D array to 2D
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int transpose_mat[nCols][nRows]); // Transpose a 2D matrix
bool found_duplicate(int arr[], int length); // Check for duplicates in the array

int main() {
    int arr[SIZE]; // Initialize 1D array
    for (int i = 0; i < SIZE; i++) {
        arr[i] = (i + 1) * 10;
    }

    int arr2d[noRows][noCols];
    int no; // Position for insert/remove
    int value = 80; // Value to insert
    int func; // Choice of function
    printf("Which function do you want use on the array \n (1- remove element 2- insert element 3-reshape 4-trans_matrix 5-Duplicate_arr)\n");
    scanf("%d", &func);

    // Get position input if applicable
    if (func == 1 || func == 2) {
        printf("enter pos value\n");
        scanf("%d", &no);
    }

    // Check if position is valid
    if (isValid(arr, SIZE, no)) {
        printf("pos in range\n");
        if (func == 1)
            remove_element(arr, SIZE, no); // Remove element
        if (func == 2)
            insert_element(arr, SIZE, no, value); // Insert element

        // Print updated array
        for (int j = 0; j < SIZE; j++) {
            printf("%d\n", arr[j]);
        }
    }

    // Reshape array
    if (func == 3) {
        reshape(arr, SIZE, noRows, noCols, arr2d);
        for (int i = 0; i < noRows; i++) {
            for (int j = 0; j < noCols; j++) {
                printf("%d  ", arr2d[i][j]);
            }
            printf("\n");
        }
    } 
    // Transpose a matrix
    else if (func == 4) {
        int mat[noRows][noCols] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90},
        {100, 110, 120},
        {130, 140, 150},
        {160, 170, 180},
        {190, 200, 210},
        {220, 230, 240}
    };
        int mat_t[noCols][noRows];
        trans_matrix(noRows, noCols, mat, mat_t);
        for (int i = 0; i < noCols; i++) {
            for (int j = 0; j < noRows; j++) {
                printf("%d  ", mat_t[i][j]);
            }
            printf("\n");
        }
    } 
    // Check for duplicates
    else if (func == 5) {
        if (found_duplicate(arr, SIZE))
            printf("Array has duplicate values\n");
        else {
            printf("Array has no duplicate elements\n");
        }
    }
}

// Check if position is valid
bool isValid(const int arr[], int length, int pos) {
    return pos >= 0 && pos < length;
}

// Remove element from array
void remove_element(int arr[], int length, int pos) {
    for (int i = pos; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
}

// Insert element into array
void insert_element(int arr[], int length, int pos, int value) {
    for (int i = 0; i < pos; i++) {
        arr[i] = arr[i + 1];
    }
    arr[pos] = value;
}

// Reshape 1D array into 2D array
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Dimensions of 1d array do not match with 2d\n");
    } else {
        int k = 0;
        for (int i = 0; i < nCols; i++) {
            for (int j = 0; j < nRows; j++) {
                arr2d[j][i] = arr[k++];
            }
        }
    }
}

// Transpose a 2D matrix
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int transpose_mat[nCols][nRows]) {
    for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            transpose_mat[i][j] = mat[j][i];
        }
    }
}

// Check if array has duplicate elements
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j])
                return true;
        }
    }
    return false;
}
