#include <stdio.h>
#include <ctype.h>

// circular buffer (FIFO)

//TODO:
//
// Enable bufinit to initialize array size with calloc.

//test above with multiple buffers SIMULTANEOUSLY
//ALLOW multiple sources. nOT JUST int FROM STDIN
//allow MULTIPLE DESTINATIONS (MONITOR, FILE, SEIRAL PORT, ETC)
//RUN MAIN() ONLY FOR TESTING, NOT AS A LIBRARY.
//USED DEBUG OPTION TO ENABLE PRINT STATEMENTS
//TEST IN SEPARATE TEST.C
//TEST WITH RANDOM INPUT




#define BUFSIZE 10
//#define ABS(x) (x) < 0 ? -(x) : (x)

  #define PRINTBUFF \
    printf("H:%d, T:%d - " , cbuf.head, cbuf.tail); \
    for(int i = 0; i<BUFSIZE; i++) printf("(%c) ", cbuf.buffer[i]); \
    printf(" %d\n", cbuf.length);

//CAN't INITIALIZE BUFSIZE
//create a cbuf init function, to set the buffer size and the head/tail pointers.
//https://stackoverflow.com/questions/42615329/create-a-variable-length-int-array-inside-a-structure-using-a-pointer

typedef struct{
  int buffer[BUFSIZE];
  int head; //next outbound cell
  int tail; //next inbond cell
  int length; //available buffer space
} Cbuf;


// prototypes

//DO DEFINITION FOR BUFINIT to define its size, the type of object, the input and output files, and the end of input (like \n for stdin)
Cbuf *cbuf_init(int bufsize, char elementType, int endmark);
int cbuf_in(Cbuf *cbuf, int c);
int cbuf_out(Cbuf *cbuf);
int cbuf_full(Cbuf *cbuf);
int cbuf_empty(Cbuf *cbuf);

//function definitions

//test for buffer full
int cbuf_full(Cbuf *cbuf){return (cbuf->length == 0);}

//test for buffer empty
int cbuf_empty(Cbuf *cbuf){return (cbuf->length == BUFSIZE);}

//Producer: adds elements to buffer if not Full.
int cbuf_in(Cbuf *cbuf, int c){
  if (c == '\n') return -1;
  if (!cbuf_full(cbuf)){
    cbuf->buffer[cbuf->tail++] = c;
    cbuf->length--;
    //wrapp tail back to begining of array
    if (cbuf->tail == BUFSIZE){
      cbuf->tail %= BUFSIZE;
    }
    return 1;
  }
  return 0;
}

//Consumer: Gets characters out of the buffer
int cbuf_out(Cbuf *cbuf){
  if(!cbuf_empty(cbuf)){
    int c = cbuf->buffer[cbuf->head++];
    cbuf->length++;
    //wrapp head back to begining of array
    if (cbuf->head == BUFSIZE){
      cbuf->head %= BUFSIZE;
    }
    return c;
  }
  return 0;
}


//TEST

//CHANGE THIS TO A TEST function instead of main()
//TEST IN A SEPARATE TEST.C FILE
int main(){

  // struct Cbuf cbuf;
  Cbuf cbuf;
  cbuf.head = 0;
  cbuf.tail = 0;
  cbuf.length = BUFSIZE;

  //STRUCT TEST
  printf("Head: %d, Tail: %d, Length: %d", cbuf.head, cbuf.tail, cbuf.length);

  int c;
  int blank = 0; //Enter key without any characters. Retrieve a character from buffer
  printf("\n*******************************************************\n");
  printf("Circular Buffer Test (input: Keyboard, Output: Monitor)\n");
  printf("*******************************************************\n\n");
  printf("Enter character(s) to store. Press enter to retrieve the oldest\n\n");
  while(1){
    c = cbuf_in(&cbuf, getchar());
    switch (c) {
      case 1:
          /* user entered characters to store */
          blank = 0;
          PRINTBUFF;
          break;
      case 0:
          /* Buffer full */
          printf("Buffer Full\n");
          blank = 0;
          break;
      case -1:
          /* User Pressed only Enter key */
          if (blank && !cbuf_empty(&cbuf))  {
            printf("[%c]\n", cbuf_out(&cbuf));
            PRINTBUFF
          }else
          if ( cbuf_empty(&cbuf) ) printf("Buffer Empty\n");
          blank = 1;
          break;
        default:
              printf("Unexpected return code from buffIn: %d. Exiting\n", c);
              goto EXIT;
    }
  }
  EXIT:
  ;
}
