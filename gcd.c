#include <stdio.h>
#include <stdlib.h>


/*
* put this in a header file
*/
#define MOD(x) ((x) < 0 ? -x : x)
int gcd(int, int); //function prototype


int gcd(int a, int b){
  /*
  * //recursive procedure to calculate the greatest common denominator
  * //given a is greater than b
  * int x = a % b; //x is the remainder
  * if (x==0) return b;
  * gcd(b, x);
  */
  //find the max and min operands
  int max, min;
  MOD(a) > MOD(b) ? (max=a, min=b) : (max=b, min=a);
  //find the gcd
  if (min == 0) return MOD(max);
  return (gcd(min, max % min));
}

int main(int argCount, char *argv[]){
  if (argCount != 3){
    printf ("Greatest common Denominator\nFormat gcd x y\n");
    return(0);
  }
  int x = atoi(argv[1]);
  int y = atoi(argv[2]);
  printf ("The gcd of %d and %d is %d\n", x, y, gcd(x,y));
  return 0;
}
