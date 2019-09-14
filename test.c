#include <stdio.h>
#include <string.h>
#include <stdlib.h> //rand(), srand()
#include <time.h> //time()
#include <unistd.h> //sleep()
#include "c-utils.h"
#include "circbuffer.h"



//Circular buffer demostration example from circbuffer.h
void test(unsigned size){
  Cbuf cbuf = cbuf_new(size);
  int c;
  printf("Type one character + <Enter>");
  if (!cbuf_full(cbuf)){
      c = cbuf_in(&cbuf, getchar()); //if c = 0, buffer is full, if -1, end of input
  }
  if (!cbuf_empty(cbuf))  {
      printf("The first character you typed was: %c\n", cbuf_out(&cbuf)); //get and print one character
  }
}


int main(int argCount, char *argv[]){

//This test.c code is to test library functions
// Uncomment the fucntion section to test
// See individual header files for usage

//*****************************************************
// Test circular buffer
//
//To Compile: cc test.c circbuffer.c -o test
//
//cbuf_test(5); //using the builtin test function
void test(unsigned size);
test(10);

//*****************************************************
  // //test gcd - greatest common denominator of the two integers
  //
  //TO COMPILE:
  // cc test.c gcd.c -o test
  //
  // // given in the command line
  // if (argCount != 3){
  //   printf ("Greatest common Denominator\nSyntax gcd x y\n");
  //   return(0);
  // }
  // int x = atoi(argv[1]);
  // int y = atoi(argv[2]);
  // printf ("The gcd of %d and %d is %d\n", x, y, gcd(x,y));
//*****************************************************
  // //test quicksort
  //
  //TO COMPILE:
  // cc test.c quicksort.c -o test
  //
  // /* define variables */
  // int aLow = 0;
  // int aHigh = arraySize-1;
  // /* populate test array with random numbers */
  // a = randArray(arraySize, 2);
  // printf ("Unsorted Array:");
  // printArray(a, arraySize);
  // sortArray(a, aLow, aHigh);
  // printf ("Sorted Array:");
  // printArray(a, arraySize);
  // return(0);
  //*****************************************************

}
