#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {
  assert(lst != NULL);
  lst->firstLink = malloc(sizeof(struct DLink));
  assert(lst->firstLink != 0);
  lst->lastLink = malloc(sizeof(struct DLink));
  assert(lst->lastLink);
  lst->firstLink->next = lst->lastLink;
  lst->lastLink->prev = lst->firstLink;
  lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
  assert ( !isEmptyList(lst) && l != NULL);  
  struct DLink *temp = (struct DLink *) malloc (sizeof(struct DLink));  
  assert (temp != 0);  // ensure it was created
  temp->value = v;
  temp->next = l;  
  temp->prev = l->prev;  
  l->prev = temp;  
  (temp->prev)->next = temp;  
  lst->size++; 
}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
  assert(lst != NULL);
  _addLinkBefore(lst, lst->firstLink->next,e);
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) {
  assert(lst != NULL);
  _addLinkBefore(lst, lst->lastLink->prev,e);  
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
  assert(lst != NULL);
  assert ( !isEmptyList(lst) );
  return(lst->firstLink->next->value);
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
  assert(lst != NULL);
  assert ( !isEmptyList(lst) );
  return(lst->lastLink->prev->value);  
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{
  assert(lst != NULL);
  assert (l != NULL );
  assert ( !isEmptyList(lst) ); // extra check
  (l->prev)->next = l->next;
  (l->next)->prev = l->prev;
  free(l);
  lst->size--;
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
  assert(lst != NULL);
  assert ( !isEmptyList(lst) );
  _removeLink(lst,lst->firstLink->next);

}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{	
  assert(lst != NULL);
  assert ( !isEmptyList(lst) );
  _removeLink(lst,lst->lastLink->prev);	
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
  return ( (lst->size == 0) && 
	   (lst->firstLink->next == lst->lastLink->prev) );
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
  assert(lst != NULL);

  // create placeholders
  struct DLink* i;
  i = lst->firstLink; // point placeholder at front's next value
  int j = 0;

  // traverse list
  while (i != lst->lastLink)
    {
      printf("lst[%d] = %d\n",j,i->value);
      i = i->next; // increment pointer
      j++;
    }
}

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
  assert(lst != NULL);
  addFrontList(lst,v); // wasn't clear if it should be front or back
}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {
  assert(lst != NULL);
  assert( !isEmptyList(lst) );
  
  struct DLink* i = lst->firstLink; // placeholder
  // traverse list
  while (i != lst->lastLink)
    {
      if ( i->value == e )
	return 1;
      else
	i = i->next;
    }
  return 0; // default return value
  
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
  assert(lst != NULL);
  assert( !isEmptyList(lst) );
  
  // couldn't think of a way to reuse containsList()

  struct DLink* i = lst->firstLink; // placeholder
  // traverse list
  while (i != lst->lastLink)
    {
      if ( i->value == e )
	_removeLink(lst,i);
      else
	i = i->next;
    }
}
