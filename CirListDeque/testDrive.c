#include "cirListDeque.c"
#include <stdio.h>

int main(){
	struct cirListDeque* q = createCirListDeque(); 

	// addBackCirListDeque(q, (TYPE)1);
	// addBackCirListDeque(q, (TYPE)2);
	// addBackCirListDeque(q, (TYPE)3);
	// addFrontCirListDeque(q, (TYPE)4);
	// addFrontCirListDeque(q, (TYPE)5);
	// addFrontCirListDeque(q, (TYPE)6);

	// push 1,2,3 in from back.  Contents: 1,2,3
	addBackCirListDeque(q, 1);
	addBackCirListDeque(q, 2);
	addBackCirListDeque(q, 3);

	printCirListDeque(q);

	printf("frontCirListDeque(q) = %g\n", frontCirListDeque(q)); // should be 1
	printf("backCirListDeque(q) = %g\n", backCirListDeque(q)); // should be 3
	
	printf("\nremoving front of deque\n");
	removeFrontCirListDeque(q);  // should now contain 2,3 
	printCirListDeque(q); // verificatiion

	printf("\nreplacing front of deque\n");
	addFrontCirListDeque(q,1); // push 1 back to front of list
	printCirListDeque(q); // verificatiion

	printf("\nadding to back of deque\n");
	addBackCirListDeque(q,4); // push 4 back to back of list
	printCirListDeque(q); // verificatiion

	printf("\n wiping list \n");
	freeCirListDeque(q);
	//printf("isEmptyCirListDeque(q) = %d\n",isEmptyCirListDeque(q));
	// printf("q->size = %d\n",q->size); // verify 
	// free(q); 


	// refill list to test reversal
	printf("\n refilling list\n");
	// struct cirListDeque* q = createCirListDeque();  // compile time error (redfinition)
	q = createCirListDeque();  // compile time error (redfinition)
	//_initCirListDeque(q); //(this adds extra zero?)
	// struct cirListDeque* r = createCirListDeque();
	for (int i = 1; i < 26; i++)
	  addBackCirListDeque(q,i);

	printCirListDeque(q);

	printf("\n reversing deque\n");
	reverseCirListDeque(q);
	printCirListDeque(q);

	printf("\n reversing deque\n");
	reverseCirListDeque(q);

	printCirListDeque(q);


	freeCirListDeque(q);


	// removeBackCirListDeque(q);
	// printCirListDeque(q);
	// reverseCirListDeque(q);
	// printCirListDeque(q);

	return 0;
}
