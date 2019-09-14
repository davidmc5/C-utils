#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> //for malloc
#include "circbuffer.h"

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




#define PRINTBUFF(cbuf) \
    printf("H:%d, T:%d - " , cbuf.head, cbuf.tail); \
    for(int i = 0; i<cbuf.size; i++) printf("(%c) ", cbuf.buffer[i]); \
        printf(" %d\n", cbuf.length);



//function definitions

//test for buffer full
int cbuf_full(Cbuf cbuf){return (cbuf.length == 0);}

//test for buffer empty
int cbuf_empty(Cbuf cbuf){return (cbuf.length == cbuf.size);}

// //Producer: adds elements to buffer if not Full.
int cbuf_in(Cbuf *cbuf, int c){
  if (c == '\n') return -1;
  if (!cbuf_full(*cbuf)){
    cbuf->buffer[cbuf->tail++] = c;
    cbuf->length--;
    //wrapp tail back to begining of array
    if (cbuf->tail == cbuf->size){
      cbuf->tail %= cbuf->size;
    }
    return 1;
  }
  return 0;
}

//Consumer: Gets characters out of the buffer
int cbuf_out(Cbuf *cbuf){
  if(!cbuf_empty(*cbuf)){
    int c = cbuf->buffer[cbuf->head++];
    cbuf->length++;
    //wrapp head back to begining of array
    if (cbuf->head == cbuf->size){
      cbuf->head %= cbuf->size;
    }
    return c;
  }
  return 0;
}

/*
* Initialize a circular buffer object with given arguments
* Return a copy of the new cbuf object
*/
Cbuf cbuf_new(unsigned bufsize){
  /*
  * Include formal parameters for:
  * --type of the buffer elements,
  * --type input and output streams(stdin/file),
  * --end delimeter of input (like \n for stdin)
  * --FIFO / LIFO
  */
  Cbuf cbuf = {NULL, 0, 0, 0, 0};
  cbuf.buffer = malloc(bufsize * sizeof(cbuf.buffer)); //https://stackoverflow.com/q/5327012
  cbuf.size = bufsize;
  cbuf.length = bufsize;
  return cbuf;
}



/*
* Test function for the circular buffer
*/
void cbuf_test(unsigned size){
  Cbuf cbuf = cbuf_new(size);

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
          PRINTBUFF(cbuf);
          break;
      case 0:
          /* Buffer full */
          printf("Buffer Full\n");
          blank = 0;
          break;
      case -1:
          /* User Pressed only Enter key */
          if (blank && !cbuf_empty(cbuf))  {
            printf("[%c]\n", cbuf_out(&cbuf));
            PRINTBUFF(cbuf)
          }else
          if ( cbuf_empty(cbuf) ) printf("Buffer Empty\n");
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

// int main(){
//   cbuf_test(10);
// }
