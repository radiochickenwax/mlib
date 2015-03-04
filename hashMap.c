#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}



/*function to find key index using either stringHash1 or stringHash2*/
int _findKey (struct hashMap *ht, KeyType k)
{
    assert (ht != NULL);

    int index;

    if (HASHING_FUNCTION == 1)
        index = stringHash1(k) % ht->tableSize;
    else if (HASHING_FUNCTION == 2)
        index = stringHash2(k) % ht->tableSize;

    if (index < 0)
        index += ht->tableSize;

    return (index);
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
  /*write this*/	
  assert (ht != 0);
  
  hashLink *cur = NULL;
  hashLink *next = NULL;
  
  for(int i = 0; i < ht->tableSize; i++)
    {
      cur = ht->table[i];
      while(cur != NULL)
        {
	  next = cur->next;
	  free(cur->key);
	  free(cur);
	  cur = next;
        }
      free(ht->table);
      ht->tableSize = 0;
      ht->count = 0;
    }
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
  /*write this*/	
  assert(ht != NULL);
  
  // general idea
  // create a new table at the new size, copy all elements over, destroy old table
  
  hashLink **old = ht->table; // store the old table
  int oldSize = ht->tableSize; 

  // init the new map 
  _initMap(ht,newTableSize); 

  // copy the old elements back
  for (int i=0; i < oldSize; i++)
    {
      hashLink *this = old[i];
      while (this != NULL)
	{
	  insertMap(ht, this->key, this->value);
	  hashLink *last = this;
	  this = this->next;
	  free(last);
	}
    }
  free(old);

}

/* 
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
  /*write this*/	
  assert(ht != NULL);
  assert(k != NULL);  // k is char*, v is int

  int index;  // get index from k in ht

  if (HASHING_FUNCTION == 1)
    index = stringHash1(k) % ht->tableSize;
  else if (HASHING_FUNCTION == 2)
    index = stringHash2(k) % ht->tableSize;
  
  index %= ht->tableSize; // wrap around if necessary

  if (index < 0)  // ensure positive index
    index += ht->tableSize;
  
  
  // if k is already in ht, replace value
  if (containsKey(ht,k))
    {
      ht->table[ index ]->value = v;
    }

  else // k isn't there so need to make a new link, fill it, add to table
    {
      struct hashLink *new = malloc(sizeof(struct hashLink)); // new link

      new->value = v; // fill it
      new->key = k;
      new->next = ht->table[ index ];
      
      ht->table[ index ] = new;  // add to table
      ht->count++;
    }
  
  // monitor load factor 
  if (tableLoad(ht) > LOAD_FACTOR_THRESHOLD)
    _setTableSize(ht, ht->tableSize * 2);
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
  /*write this*/
  assert (ht != NULL);
  assert (k != NULL);

  int index;  // get index from k in ht

  if (HASHING_FUNCTION == 1)
    index = stringHash1(k) % ht->tableSize;
  else if (HASHING_FUNCTION == 2)
    index = stringHash2(k) % ht->tableSize;
  
  index %= ht->tableSize; // wrap around if necessary

  if (index < 0)  // ensure positive index
    index += ht->tableSize;
  
  
  // if k is already in ht, replace value
  if (containsKey(ht,k))
    {
      ht->table[ index ]->value = v;
    }

  // get a pointer to the table at the generated index
  struct hashLink *ptr = ht->table[ index ];
  while(ptr != NULL)
    {
      /*
	strcmp (a,b) returns zero if a == b
	returns the difference of the int value 
	of first mismatched chars otherwise.
       */
      if (strcmp(ptr->key,k) == 0)
	return (&ptr->value);  
      ptr = ptr->next;
    }
  // else
  return NULL;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
  /*write this*/
  assert(ht!=NULL);

int index;  // get index from k in ht

 if (HASHING_FUNCTION == 1)
   index = stringHash1(k) % ht->tableSize;
 else if (HASHING_FUNCTION == 2)
   index = stringHash2(k) % ht->tableSize;
 
 index %= ht->tableSize; // wrap around if necessary
 
 if (index < 0)  // ensure positive index
   index += ht->tableSize;
 
 // create pointer to index
 struct hashLink* ptr = ht->table[ index ];
 
 
 // if k is already in ht, replace value
 if (containsKey(ht,k))
   {
     ht->table[ index ]->value = v;
   }
 
 while (ptr != NULL)
   {
     if (strcmp(ptr->key,k) == 0)
       return 1;
     ptr = ptr->next;
   }
  return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
  /*write this*/	
  assert(ht!=NULL);
  
  int index;  // get index from k in ht
  
  if (HASHING_FUNCTION == 1)
    index = stringHash1(k) % ht->tableSize;
  else if (HASHING_FUNCTION == 2)
    index = stringHash2(k) % ht->tableSize;
  
  index %= ht->tableSize; // wrap around if necessary
  
  if (index < 0)  // ensure positive index
    index += ht->tableSize;
  
  // create pointer to index
  struct hashLink* cur = ht->table[ index ];
  
  while (cur != NULL)
    {
      if (strcmp(cur->key, k) == 0 )
        {
	  struct hashLink *temp = cur->next;
	  free (cur->key);
	  free (cur);
	  ht->table[_findKey( ht, k ) ] = temp;
	  ht->count--;
	  return;
        }
      
      while (cur->next != NULL )
        {
	  if (strcmp(cur->next->key, k) == 0)
            {
	      struct hashLink *temp = cur->next->next;
	      free(cur->next->key);
	      free(cur->next);
	      cur->next = temp;
	      ht->count--;
	      return;
            }
	  cur = cur->next;
        }
    }
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	/*write this*/
	return 0;
	
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	/*write this*/
	return 0;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	/*write this*/
	return 0;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	/*write this*/
	return 0;
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


