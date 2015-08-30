all: calc testda lib-shared lib-static

calc: dynamicArray.o calc.o
	gcc -g -Wall -std=c99 -o calc dynamicArray.o calc.o -lm

calc.o: calc.c dynamicArray.h
	gcc -g -Wall -std=c99 -c calc.c

testda-static: 

testda-shared: dynamicArray.o testDynArray.o
	gcc -g -Wall -std=c99 -o testda dynamicArray.o testDynArray.o

testDynArray.o: testDynArray.c dynamicArray.h
	gcc -g -Wall -std=c99 -c testDynArray.c

lib-shared: dynamicArray.o
	#gcc -c -fPIC dynamicArray.c -o dynamicArray.o
	gcc -shared -Wl,-soname,libDynArr.so -o libDynArr.so dynamicArray.o

lib-static: dynamicArray.o
	ar rcs libDynArr.a dynamicArray.o 

dynamicArray.o: dynamicArray.c dynamicArray.h 
	gcc -g -Wall -std=c99 -c dynamicArray.c	


clean:
	rm dynamicArray.o
	rm calc.o
	rm libDynArr.a
	rm testDynArray.o
	rm calc
	rm testda
