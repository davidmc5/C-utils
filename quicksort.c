#include <stdio.h>
#include <string.h>
#include <stdlib.h> //rand(), srand()
#include <time.h> //time()
#include <unistd.h> //sleep()


/*
* quicksort:
* Sort an array of integers so they are in an increasing order
*
* Procedure:
* pick a arbitrary element of the array as the partition element pe
* move all values greater than pe to the right of pe
* and all the values less than pe to the left
* Return the pe.
*
* Recursively call this function to repeat the process
* with each of the two sides of the partition element returned.
*/


/* test array */
//int a[] = {5,9,3,0,7,4,8,1,6,2};
//9 6 16 19 75 34 26 54 56 73

#define arraySize 10
int *a; // pointer for the array to be sorted



/* function declarations */
void swap(int *, int, int);
int partition(int *, int, int);
void sortArray(int *, int, int);
void printArray(int *, int);
int * randArray(int, int);

int main(){
  //use this main function for testing qsort()
  /* define variables */
  int aLow = 0;
  int aHigh = arraySize-1;
  /* populate test array with random numbers */
  a = randArray(arraySize, 2);
  printf ("Unsorted Array:");
  printArray(a, arraySize);
  sortArray(a, aLow, aHigh);
  printf ("Sorted Array:");
  printArray(a, arraySize);
  return(0);
}


void swap(int a[], int low, int high){
  /*swaps values between array indices low and high */
  int temp = a[low];
  a[low] = a[high];
  a[high] = temp;
}

int partition(int a[], int low, int high){
  /*
  * Returns the index of one of the array values between low and high
  * and moves all the values less than the partition element to the left,
  * and all the values higher than the partition element to the right
  */
  int i = low;
  int j = high;
  /* pick the midle element and move it to the right end */
  swap(a, (i+j)/2, j);
  int pe = a[j];
  /*
  * scan left side for higher than pe values
  * and right side for lower than pe values
  * and swap them
  */
  while (i<j){
    while (i<j && a[i] <= pe) i++;
    while (i<j && a[j] >= pe) j--;
    if (i < j) swap(a, i, j);
  }
  if (i!=high) swap(a, i, high); //move the partition element to its correct place
  return i;
}

void printArray(int a[], int aSize){
    for (int i = 0; i < aSize; i++){
    printf("%d ", a[i]);
  }
  putchar('\n');
}


//TODO
//CHANGE SORTARRAY TO qsort
void sortArray(int *a, int low, int high){
  /*
  * Calls partition() to divide the array into two sorted halfs
  * and calls itself recursively on each array halfs
  * until the size becomes 1 or zero.
  */
  if (high <= low) return;
  int pIndex = partition(a, low, high);
  sortArray(a, low, pIndex-1);
  sortArray(a, pIndex+1, high);
}

int * randArray(int numElements, int numDigits){
  /*
  * Returns an array of random integers with the specicied number of elements <numElements>
  * and with the integers up to the specified number of digits <numDigits>
  */
  static int array[arraySize];
  /* set the seed */
  srand( (unsigned)time( NULL ) );
  /* populate the array with random numbers */
  int i, j;
  for (i = 0; i < arraySize; ++i){
    array[i] = rand() % 100;
    /* Remove repeated numbers */
    //check if current random value already came up
    // for (j = 0; j<i; j++){
    //   if (array[j] == array[i]){
    //     //replace repeated value
    //     array[i] = rand() % 100;
    //     j=0; //check new number again from start
    //   }
    // }
  }
  return array;
}
