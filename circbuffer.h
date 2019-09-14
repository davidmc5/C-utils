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

/* Producer function to add objects to the buffer */
extern int cbuf_in(Cbuf *cbuf, int c);

/* Consumer function to retrieve objects from the buffer */
extern int cbuf_out(Cbuf *cbuf);

/* buffer full test */
extern int cbuf_full(Cbuf cbuf);

/* buffer empty test */
extern int cbuf_empty(Cbuf cbuf);

/*
* test function to demonstrate circular buffer
*
* To test, compile and run the following program:
* #include "circbuffer.h"
* int main(){
*  cbuf_test(10);
* }
*/
extern void cbuf_test(unsigned size);
