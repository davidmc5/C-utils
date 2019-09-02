#include <stdio.h>
#include <ctype.h>



// circular buffer (FIFO)

#define BUFFSIZE 10
//#define ABS(x) (x) < 0 ? -(x) : (x)

char buffer[BUFFSIZE];
int head = 0; //next outbound cell
int tail = 0; //next inbond cell
int length = BUFFSIZE; //available buffer space

int bufIn(char c);
char bufOut();
int full();
int empty();

//test for buffer full
int full(){return (length == 0);}

//test for buffer empty
int empty(){return (length == BUFFSIZE);}


//Producer: adds elements to buffer if not Full.
//Copy given element to array cell, increment tail and decrease available lenght
int bufIn(char c){
  if (c == '\n') return -1;
  if (!full()){
    buffer[tail++] = c;
    length--;
    //wrapp tail back to begining of array
    if (tail == BUFFSIZE){
      // if (tail > BUFFSIZE-1){
      tail %= BUFFSIZE;
      //printf("Tail Wrapped\n");
    }
    return 1;
  }
  return 0;
}

//Consumer: Gets characters out of the buffer
char bufOut(){
  if(!empty()){
    char c = buffer[head++];
    length++;
    //wrapp head back to begining of array
    if (head == BUFFSIZE){
      // if (head > BUFFSIZE-1){
      head %= BUFFSIZE;
      //printf("Head Wrapped\n");
    }
    return c;
  }
  return '0'; //NEED TO RETURN AN INTEGER AND CHECK ON MAIN()
}



//TODO: SIMPLY THIS TEST function
//RUN MAIN() ONLY FOR TESTING, NOT AS A LIBRARY.
//USED DEBUG OPTION TO ENABLE PRINT STATEMENTS
//TEST IN SEPARATE TEST.C
//CONVERT TO A TYPE SO MULTIPLE BUFFERS CAN RUN SIMULTANEOUSLY
//TEST WITH RANDOM INPUT AND LONGER BUFFER SIZES
//ALLOW ANY TYPE INPUT. nOT JUST CHARACTERS FROM STDIN
int main(){
  int c;
  int blank = 0;
  printf("\n*******************************************************\n");
  printf("Circular Buffer Test (input: Keyboard, Output: Monitor)\n");
  printf("*******************************************************\n\n");
  printf("Enter character(s) to store. Press enter to retrieve the oldest\n\n");
  while(1){
    // printf("> ");
    if ( (c = bufIn(getchar())) > 0){
      blank = 0;
      printf("H:%d, T:%d - " , head, tail);
      for(int i = 0; i<BUFFSIZE; i++) printf("(%c) ", buffer[i]);
      printf(" %d\n", length);
    }else if (c < 0 ){
      if (blank && !empty())  {
        printf("<[%c]\n", bufOut());
        printf("H:%d, T:%d - " , head, tail);
        for(int i = 0; i<BUFFSIZE; i++) printf("(%c) ", buffer[i]);
        printf(" %d\n", length);
      }else
      if ( empty() ) printf("Buffer Empty\n");
      blank = 1;
    }else{
      printf("Buffer Full\n");
      blank = 0;
    }
  }
}
