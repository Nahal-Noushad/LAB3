#include <stdio.h> 
#include <stdbool.h> 
#define SIZE 6
#define noRows 2
#define noCols 3
// PROTOTYPES
bool isValid(const int arr[],int length, int pos);
void remove_element(int arr[],int length, int pos);
void insert_element(int arr[],int length, int pos, int value);
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]);
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int transpose_mat[nCols][ nRows]);
bool found_duplicate(int arr[],int length);


int main()
{
int arr[SIZE];
for (int i = 0; i < SIZE; i++){
      arr[i] = (i+1) * 10;
}
arr[0] = 10;
arr[1] = 10;
int arr2d[noRows][noCols];
int no;
int value = 80;
int func;
printf("Which function do you want use on the array \n (1- remove element 2- insert element 3-reshape 4-trans_matrix 5-Duplicate_arr)\n");
scanf("%d",&func);

if (func == 1 || func == 2){
printf("enter pos value\n");
scanf("%d",&no);
}

if (isValid(arr, SIZE, no)){
   printf("pos in range\n");
   if (func == 1)
   remove_element(arr,SIZE,no);
   if (func == 2)
   insert_element(arr,SIZE, no,value);

   
   for (int j = 0; j < SIZE; j++){
      printf("%d\n",arr[j]);
   }
   }


if (func == 3){
   reshape(arr, SIZE, noRows, noCols, arr2d);
      for (int i = 0;i < noRows; i++){
         for (int j = 0;j < noCols; j++){
            printf("%d  ",arr2d[i][j]);
         }
         printf("\n");
      }
}
else if (func == 4){
   int mat[noRows][noCols] = {{10,20,30},{80,90,100}};
   int mat_t[noCols][noRows];
   trans_matrix(noRows, noCols, mat, mat_t);
   for (int i = 0; i < noCols; i++) {
        for (int j = 0; j < noRows; j++) {
            printf("%d  ",mat_t[i][j]);
   }
   printf("\n");
}
}
else if (func == 5){
   if (found_duplicate(arr, SIZE))
   printf("Array has duplicate values\n");
   else {
      printf("Array has no duplicate elements");
   }
}
  

//Call to different functions
}

bool isValid(const int arr[],int length, int pos){
   if (pos >= 0 && pos < length){
   return true;
   }
   return false;
}

void remove_element(int arr[],int length, int pos){
   for (int i = pos; i > 0; i--){
      arr[i] = arr[i-1];

   }
}

void insert_element(int arr[],int length, int pos, int value){
   for (int i = 0; i < pos; i++){
      arr[i] = arr[i+1];
}
arr[pos] = value;
}

void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]){
   if (length != nRows * nCols){
      printf("Dimensions of 1d array do not match with 2d\n");
   }
   else{
      int k = 0;
      for (int i = 0;i < nCols; i++){
         for (int j = 0;j < nRows; j++){
            arr2d[j][i] = arr[k];
            k++;
         }
      }

   }
}

void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int transpose_mat[nCols][ nRows]){
   for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            transpose_mat[i][j] = mat[j][i];
   }
}
}

bool found_duplicate(int arr[],int length){
   for (int i = 0; i < length; i++){
      for (int j = i+1; j < length; j++){
         if (arr[i] == arr[j])
         return true;
      }
   }
   return false;
}
