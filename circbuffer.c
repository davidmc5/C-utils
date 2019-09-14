#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> //for malloc

// circular buffer (FIFO)

//TODO:

//UNDERSTAND WHY CBUF_NEW WORKS WITH MALLOC
//GIT MERGE BRANCH TO MASTER AND PUSH
//build test function and remove main()
//TEST IN SEPARATE TEST.C
// Add more parameter options to cbuf_new()
//test multiple buffers SIMULTANEOUSLY
//ALLOW multiple sources. NOT JUST int FROM STDIN
//allow MULTIPLE DESTINATIONS (MONITOR, FILE, SERIAL PORT, ETC)
//USED DEBUG OPTION TO ENABLE PRINT STATEMENTS
//TEST WITH RANDOM INPUT




#define BUFSIZE 10
//#define ABS(x) (x) < 0 ? -(x) : (x)

#define PRINTBUFF \
    printf("H:%d, T:%d - " , cbuf.head, cbuf.tail); \
    for(int i = 0; i<BUFSIZE; i++) printf("(%c) ", cbuf.buffer[i]); \
    printf(" %d\n", cbuf.length);

typedef struct{
  unsigned size; //size of the buffer
  unsigned *buffer;  // void* ? dynamically alocated by cbuf_init()- https://stackoverflow.com/a/2061103
  unsigned head; //next outbound cell
  unsigned tail; //next inbond cell
  unsigned length; //available buffer space
} Cbuf;


// prototypes
Cbuf cbuf_new(unsigned bufsize);
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

/*
* Initialize a circular buffer object with given arguments
* Return a pointer to the new cbuf object
*/
Cbuf cbuf_new(unsigned bufsize){
  /*
  * Include formal parameters for:
  * --type of the buffer elements,
  * --type input and output streams(stdin/file),
  * --end delimeter of input (like \n for stdin)
  * --FIFO / LIFO
  */
  Cbuf *cbuf = malloc(sizeof(Cbuf)); //https://stackoverflow.com/q/5327012
  cbuf->size = bufsize;
  cbuf->head = 0;
  cbuf->tail = 0;
  cbuf->length = bufsize;
  cbuf->buffer = malloc(bufsize * sizeof(cbuf->buffer));
  return *cbuf;
}


//TEST

//CHANGE THIS TO A TEST function instead of main()
//TEST IN A SEPARATE TEST.C FILE
int main(){
//4
  Cbuf cbuf = cbuf_new(BUFSIZE);
  // Cbuf cbuf = *cbuf_init(BUFSIZE);

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
