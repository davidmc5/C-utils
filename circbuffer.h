/***** Cicrcular buffer -- File: circbuffer.h *************/



struct cirbuf {
  unsigned *buffer;  // void* ? dynamically alocated by cbuf_init()- https://stackoverflow.com/a/2061103
  unsigned size; //size of the buffer
  unsigned head; //next outbound cell
  unsigned tail; //next inbond cell
  unsigned length; //available buffer space
};

typedef struct cirbuf Cbuf;

// prototypes

/* Returns a new circular buffer with the given size */
extern Cbuf cbuf_new(unsigned bufsize);

/* free alocated buffer memory */
extern void cbuf_free(Cbuf cbuf);

/* Producer function to add objects to the buffer */
extern int cbuf_in(Cbuf *cbuf, int c); //pass a pointer since we need to modify head and tail

/* Consumer function to retrieve objects from the buffer */
extern int cbuf_out(Cbuf *cbuf); //pass a pointer since we need to modify head and tail

/* buffer full test */
extern int cbuf_full(Cbuf cbuf);

/* buffer empty test */
extern int cbuf_empty(Cbuf cbuf);

/* Demonstration/Test function */
extern void cbuf_test(unsigned size);

/*
* Example using the test function to demonstrate circular buffer
*
* To test, save (test.c) compile (cc test.c circbuffer.c -o test) and run (./test) the following program:

 #include "circbuffer.h"
 int main(){
  cbuf_test(10);
 }

*/

/*
// Example of usage using all interface functions
// gets one character from stdin and prints it out

#include "circbuffer.h"
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

int main(){
  void test(unsigned size);
  test(10);
}

*/
