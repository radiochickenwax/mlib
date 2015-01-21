#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else 
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
  printf("sizeDynArr(stack) = %d\n",sizeDynArr(stack));
  assert(sizeDynArr(stack) >= 2);
  double param1 = topDynArr(stack);
  printf("p1: %f\n",param1);
  popDynArr(stack);
  double param2 = topDynArr(stack);
  printf("p2: %f\n",param2);
  popDynArr(stack);
  pushDynArr(stack,param1 + param2);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 2);
  double param1 = topDynArr(stack);
  popDynArr(stack);
  double param2 = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,param1 - param2);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 2);
  double param1 = topDynArr(stack);
  popDynArr(stack);
  double param2 = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,param1 / param2);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their product is pushed back onto the stack.
*/
void multiply(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 2);
  double param1 = topDynArr(stack);
  popDynArr(stack);
  double param2 = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,param1*param2);
}


/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their power is pushed back onto the stack.
*/
void power(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 2);
  double param1 = topDynArr(stack);
  popDynArr(stack);
  double param2 = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,pow(param1,param2));
}


/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and 
	its square is pushed back onto the stack.
*/
void square(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 1);
  double param = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,pow(param,2));
}


/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and 
	its cube is pushed back onto the stack.
*/
void cube(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 1);
  double param = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,pow(param,3));
}


/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and 
	its abs is pushed back onto the stack.
*/
void absVal(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 1);
  double param = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,abs(param));
}


/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and 
	its sqrt is pushed back onto the stack.
*/
void squareRoot(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 1);
  double param = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,sqrt(param));
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and 
	its exp is pushed back onto the stack.
*/
void expNat(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 1);
  double param = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,exp(param));
}


/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and 
	its ln is pushed back onto the stack.
*/
void ln(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 1);
  double param = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,log(param));
}


/*	param: stack the stack being manipulated
	pre: the stack contains at least one element
	post: the top element is popped and 
	its log_10 is pushed back onto the stack.
*/
void log_10(struct DynArr *stack)
{
  assert(sizeDynArr(stack) >= 1);
  double param = topDynArr(stack);
  popDynArr(stack);
  pushDynArr(stack,log10(param));
}


double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	//struct DynArr *stack;
	DynArr *stack;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0)
		  add(stack);
		else if(strcmp(s,"-") == 0)
		  subtract(stack);
		else if(strcmp(s, "/") == 0)
		  divide(stack);
		else if(strcmp(s, "x") == 0)
		  multiply(stack);
		else if(strcmp(s, "^") == 0)
		  power(stack);
		else if(strcmp(s, "^2") == 0)
		  square(stack);
		else if(strcmp(s, "^3") == 0)
		  cube(stack);
		else if(strcmp(s, "abs") == 0)
		  absVal(stack);
		else if(strcmp(s, "sqrt") == 0)
		  squareRoot(stack);
		else if(strcmp(s, "exp") == 0)
		  expNat(stack);
		else if(strcmp(s, "ln") == 0)
		  ln(stack);
		else if(strcmp(s, "log") == 0)
		  log_10(stack);
		else if (isNumber(s, &result))
		  pushDynArr(stack,result);
		else 
		{
			// FIXME: You need to develop the code here (when s is not an operator)
			// Remember to deal with special values ("pi" and "e")
		  printf("Error\n");
		}
	}	//end for 

	/* FIXME: You will write this part of the function (2 steps below) 
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */
	if (sizeDynArr(stack) != 1)
	  printf("Error");
	else
	  result = topDynArr(stack);
	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	printf("Result: %f\n",calculate(argc,argv));
	return 0;
}
