#include <stdio.h>
#include <string.h>
#include <stdlib.h> //rand(), srand()
#include <time.h> //time()
#include <unistd.h> //sleep()
#include "c-utils.h"

int main(int argCount, char *argv[]){

//TO COMPILE:
//cc -o test test.c quicksort.c gcd.c


  //test gcd - greatest common denominator of the two integers
  // given in the command line
  if (argCount != 3){
    printf ("Greatest common Denominator\nSyntax gcd x y\n");
    return(0);
  }
  int x = atoi(argv[1]);
  int y = atoi(argv[2]);
  printf ("The gcd of %d and %d is %d\n", x, y, gcd(x,y));

  //test quicksort
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
