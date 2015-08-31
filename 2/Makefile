all: calc lib-shared lib-static testda-shared testda-static

calc: dynamicArray.o calc.o
	gcc -g -Wall -std=c99 -o calc dynamicArray.o calc.o -lm

# build object code from calc.c
calc.o: calc.c dynamicArray.h
	gcc -g -Wall -std=c99 -c calc.c

# build the executable testda from static lib
testda-static: lib-static
	gcc -g -static -Wall -std=c99 testDynArray.o -L. -lDynArr -o testda-static

# build the executable testda from shared lib
testda-shared: dynamicArray.o testDynArray.o
	gcc -g -Wall -std=c99 -o testda-shared testDynArray.o -L. -lDynArr

# build object code from testDynArray.c
testDynArray.o: testDynArray.c dynamicArray.h
	gcc -g -Wall -std=c99 -c testDynArray.c

# generate a shared library libDynArr.so
lib-shared: dynamicArray.o
	gcc -g -Wall -std=c99 -c -fPIC dynamicArray.c -o dynamicArray.o
	gcc -shared -Wl,-soname,libDynArr.so -o libDynArr.so dynamicArray.o

# generate a static library: libDynArr.a
lib-static: dynamicArray.o
	ar rcs libDynArr.a dynamicArray.o 

# generate object code 
dynamicArray.o: dynamicArray.c dynamicArray.h 
	gcc -g -Wall -std=c99 -c dynamicArray.c	


clean:
	rm libDynArr.a
	rm libDynArr.so
	rm dynamicArray.o
	rm calc.o
	rm testDynArray.o
	rm calc
	rm testda-shared
	rm testda-static
