#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q) 
{
  assert( q!= NULL);
  q->Sentinel = malloc(sizeof(struct DLink));
  assert(q->Sentinel != NULL); // make sure it's allocated
  q->Sentinel->next = q->Sentinel;
  q->Sentinel->prev = q->Sentinel;
  q->size=0;
}

/*
 create a new circular list deque
 
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
  struct DLink* link = malloc(sizeof(struct DLink));
  link->value = val;
  return link;
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
int containsCirListDeque (struct cirListDeque *lst, TYPE e) {
  assert(lst != NULL);
  assert( !isEmptyCirListDeque(lst) );
  
  struct DLink* i = lst->Sentinel->next; // placeholder
  // traverse list
  while (i != lst->Sentinel)
    {
      if ( i->value == e )
	return 1;
      else
	i = i->next;
    }
  return 0; // default return value
  
}



/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
  assert(q != NULL);
  assert(lnk != NULL);
  // assert() // make sure lnk is in deque
 
  struct DLink* new = _createLink(v);
  struct DLink* old = lnk->next;
  
  lnk->next = new;
  new->next = old;
  
  old->prev = new;
  new->prev = lnk;

  q->size++;
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
  assert( q != NULL);

  //struct DLink* new = _createLink(val);
  
  // if ( q->Sentinel->prev != NULL )
  _addLinkAfter(q,q->Sentinel->prev,val);

  
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
  assert( q != NULL);
  _addLinkAfter(q,q->Sentinel,val);
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
  assert ( q != NULL && !isEmptyCirListDeque(q) );
  
  return q->Sentinel->next->value;
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
  assert ( q != NULL && !isEmptyCirListDeque(q) );
  
  return q->Sentinel->prev->value;

}

/* Remove a link from the deque
   
	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
  assert ( q != NULL && !isEmptyCirListDeque(q) );
  
  lnk->prev->next = lnk->next;
  lnk->next->prev = lnk->prev;
  
  free(lnk);
  q->size--;

}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
  assert( q != NULL && !isEmptyCirListDeque(q) );
  _removeLink(q,q->Sentinel->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
  assert( q != NULL && !isEmptyCirListDeque(q) );
  _removeLink(q,q->Sentinel->prev);
  
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
  struct DLink* i = q->Sentinel; // start from 1st element, delete Sentinel on last op
  int j = 0;

  // empty the list
  while ( !isEmptyCirListDeque(q) )
    {
      i = i->next;
      j++;
      // printf("freeing element %d, containing %g\n",j,i->value);
      _removeLink(q,i); 
    }

  // remove the sentinel
  free(q->Sentinel);

  free(q); 

}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
  assert( q!= NULL);
  return ( (q->size == 0) &&
	   ( q->Sentinel->next == q->Sentinel->prev ) );
  
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
  assert (q != NULL && !isEmptyCirListDeque(q) );
  // traverse list

  int j = 0;
  struct DLink* i = q->Sentinel->next;  
  while ( i != q->Sentinel )
    {
      printf("CirListDeque[%d] : %f\n",j,i->value);
      i = i->next;
      j++;
    }

}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
  assert ( q != NULL);
  assert ( !isEmptyCirListDeque(q) );

  // 3 methods:

  // first is to create a new list and fill it in reverse
  // second is to find the middle of the list
  // third is to swap next, prev for each link and follow the prev links

  struct DLink* i = q->Sentinel->next;
  struct DLink* j = NULL;  
  int k = 0;

  while(i != q->Sentinel)  // traverse list
  // while(i != NULL)  // traverse list infinitely
    {
      j = i->next;
      i->next = i->prev;
      i->prev = j;

      i = i->prev; // move to next link (using prev)
      k++;
    }

  // swap sentinel
  j = q->Sentinel->prev;
  q->Sentinel->prev = q->Sentinel->next;
  q->Sentinel->next = j;

}
