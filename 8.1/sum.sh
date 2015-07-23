#!/bin/bash

# this file produces an integer sum of all input arguments if they are integers.
# a floating point sum would be more general, but it doesn't pass spec for this assignment


sum ()  # sum all input arguments
{
    length=$#;   # number of input arguments
    i=1;         # position in array of arguments                     
    sum=0;       # start sum with zero

    # NOTE:
    # i starts at 1 not 0.  The zeroth argument is the name of the file.
    

    while [ $i -lt $(expr $length + 1) ]; do
	# http://stackoverflow.com/questions/1497811/how-to-get-the-nth-positional-argument-in-bash
	# this uses bash indirection.  (http://tldp.org/LDP/abs/html/ivr.html)
    	nthArg="${!i}";                 
	
	# Create a regexp that searches for numbers only
	# http://stackoverflow.com/questions/806906/how-do-i-test-if-a-variable-is-a-number-in-bash
    	numRegExp='^[0-9]+$';         

	# if nthArg is numeric, then add it to sum.  
	# Otherwise output error msg and exit.

    	if [[ $nthArg =~ $numRegExp ]]; then  
    	    sum=$(expr $sum + $nthArg);
    	    i=$(expr $i + 1);	    
    	else
    	    echo "non-numeric input.";
    	    exit 1;
    	fi

    done

    # echo in a function is the equivalent of a return statement.
    echo $sum;
}

result=$(sum "$@");  # sum all commandline inputs if possible
echo $result;
exit 1;
