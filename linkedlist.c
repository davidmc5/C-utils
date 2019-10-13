#include <stdio.h>
#include <stdlib.h> /* for malloc */

/*
* Linked list practice

* linked list is built with a recursive structure
* - element 1: object to be stored
* - element 2: pointer to the next structure
*
*/

/* THIS WILL GO TO LINKEDLIST.H */
struct list_item {
  int myNumb;
  struct list_item *next;
};

typedef struct list_item ListItem;
typedef ListItem *List;

/*********************/

List list_new(int item){
  List new_item = (List) malloc(sizeof(ListItem));
  new_item->myNumb = item;
  new_item->next = NULL;
  return (new_item);
}

List list_add(List list, int item){
  /* allocate space for a new list item */
  List new_item = (List) malloc(sizeof(ListItem));
  new_item->myNumb = item;
  new_item->next = list;
  return (new_item);
}

void list_print(List list){
  for (;; list=list->next){
    printf("%d, ", list->myNumb);
    if(list->next == NULL){
      break;
    }
  }
}

/****** TEST *******/

int main() {
  List myList = list_new(3);
  myList = list_add(myList, 7);
  myList = list_add(myList, 4);
  myList = list_add(myList, 8);
  list_print(myList);
}
