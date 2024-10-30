#include <stdio.h> 
#include <stdbool.h> 
#define SIZE 24
#define nRows 8
#define nCols 3
// PROTOTYPES
// void print_array(int array[], int length);
// void print_matrix(int mat[][nCols], int rows);
bool isValid(const int arr[],int length, int pos);
void remove_element(int arr[],int length, int pos);
// void remove_element(int arr[],int length, int pos);
// void insert_element(int arr[],int length, int pos, int value);
// void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]);
// void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat[nCols][ nRows]);
// bool found_duplicate(int arr[],int length, ….);


int main()
{
int arr[SIZE];
for (int i = 0; i < SIZE; i++){
   arr[i] = i;
}
int arr2d[nRows][nCols];
int no = 20;
if (isValid(arr, SIZE, no)){
   printf("pos in range\n");
   remove_element(arr,SIZE,no);
   for (int j = 0; j < SIZE; j++){
      printf("%d\n",arr[j]);
   }


}
else{
    printf("false");
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
      if (i <= pos){
      arr[i] = arr[i-1];
      }

   }
}

// void insert_element(int arr[],int length, int pos, int value)
// void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols])
// void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat[nCols][ nRows]):
// bool found_duplicate(int arr[],int length, ….)
//FUNCTION DEFINITIONS































// void print_array(int array[], int length){
//    for(int i=0;i<length; i++)
//       printf("array[%d]= %d\n", i, array[i]);
// }

// void print_matrix(int mat[][nCols], int rows){
//    for(int i=0;i<rows; i++){
//     for(int j=0;j<nCols; j++)
//          printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
//     puts("");     
//    }     
// }




//print_matrix(arr2d,nRows);