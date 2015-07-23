/*
  test drive the linkedList.c program



 */
#include "linkedList.c"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main(int argc, char* argv[]){

  struct linkedList* a; // initialize list
  a = createLinkedList();

  // push values to front
  for( int i = 0 ; i < 5; i++) {
    addFrontList(a, (TYPE)i);/*Add elements*/
  }

  // print list
  _printList(a);


  printf("\npushed to front, now pushing to back\n");

  addBackList(a, (TYPE)0);/*Add elements*/

  // push values to back
  for( int i = 5 ; i < 10; i++) {
    addBackList(a, (TYPE)i);/*Add elements*/
  }



  // print list
  _printList(a);

  // check if list contains 4
  printf("containsList(a,4):%d\n",containsList(a,4));
  printf("containsList(a,12):%d\n",containsList(a,12));


  // try removing an element
  printf("removing 5\n");
  removeList(a,5);
  
  // print list
  _printList(a);

  return 0;
}

  
