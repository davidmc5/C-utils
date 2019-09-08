#include <stdio.h>
#include <ctype.h>

// circular buffer (FIFO)

//TODO:
//
// MODIFY the four BUFFER fuctions to use struct
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

//used for testing
// #define PRINTBUFF \
//   printf("H:%d, T:%d - " , head, tail); \
//   for(int i = 0; i<BUFSIZE; i++) printf("(%c) ", buffer[i]); \
//   printf(" %d\n", length);

  #define PRINTBUFF \
    printf("H:%d, T:%d - " , cbuf.head, cbuf.tail); \
    for(int i = 0; i<BUFSIZE; i++) printf("(%c) ", cbuf.buffer[i]); \
    printf(" %d\n", cbuf.length);

//CAN't INITIALIZE BUFSIZE
//create a cbuf init function, to set the buffer size and the head/tail pointers.
//https://stackoverflow.com/questions/42615329/create-a-variable-length-int-array-inside-a-structure-using-a-pointer
struct Cbuf{
  int buffer[BUFSIZE];
  int head; //next outbound cell
  int tail; //next inbond cell
  int length; //available buffer space
}; //use here a name to avoid declaring using struct Cbuf!



//remove this when cbuf struct is implemented
// int buffer[BUFSIZE];
// int head = 0; //next outbound cell
// int tail = 0; //next inbond cell
// int length = BUFSIZE; //available buffer space

//DO DEFINITION FOR BUFINIT to define its size, the type of object, the input and output files, and the end of input (like \n for stdin)
struct Cbuf bufInit(int bufsize, char elementType, int endmark);


//MODIFY THESE FUCTIONS TO USE CBUF STRUCT
// int bufIn(int c);
// int bufOut();
// int full();
// int empty();
int bufIn(struct Cbuf *cbuf, int c);
int bufOut(struct Cbuf *cbuf);
int full(struct Cbuf *cbuf);
int empty(struct Cbuf *cbuf);

//CONVERT THESE TO DEFINITIONS
//test for buffer full
//int full(){return (length == 0);}
int full(struct Cbuf *cbuf){return (cbuf->length == 0);}

//test for buffer empty
int empty(struct Cbuf *cbuf){return (cbuf->length == BUFSIZE);}


//Producer: adds elements to buffer if not Full.
//Copy given element to array cell, increment tail and decrease available lenght
// int bufIn(int c){
//   if (c == '\n') return -1;
//   if (!full()){
//     buffer[tail++] = c;
//     length--;
//     //wrapp tail back to begining of array
//     if (tail == BUFSIZE){
//       tail %= BUFSIZE;
//     }
//     return 1;
//   }
//   return 0;
// }
int bufIn(struct Cbuf *cbuf, int c){
  if (c == '\n') return -1;
  if (!full(cbuf)){
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
// int bufOut(){
//   if(!empty()){
//     int c = buffer[head++];
//     length++;
//     //wrapp head back to begining of array
//     if (head == BUFSIZE){
//       head %= BUFSIZE;
//     }
//     return c;
//   }
//   return 0;
// }
int bufOut(struct Cbuf *cbuf){
  if(!empty(cbuf)){
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



int main(){

  struct Cbuf cbuf;
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
    c = bufIn(&cbuf, getchar());
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
          if (blank && !empty(&cbuf))  {
            printf("[%c]\n", bufOut(&cbuf));
            PRINTBUFF
          }else
          if ( empty(&cbuf) ) printf("Buffer Empty\n");
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
