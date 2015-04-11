#!/bin/bash

# this median is defined as the middle value of a sorted sequence
# when there is an odd number of elements.

# when there is an even number of elements, it is the larger of the
# two middle values 

# the sequence is defined on one line, separated by spaces

# echo the max of two numbers
# http://stackoverflow.com/questions/18668556/comparing-numbers-in-bash
function max()
{ 
    # expected input: two integers
    
    # check that there are two numbers given
    if [ $# = 2 ]; then
	echo $(( $1 > $2 ? $1 : $2 ));	
	exit 1;
    else
	echo "max(): wrong number of arguments";
	exit 1;
    fi
    


}


function median()
{
    # line is all of the input parameters as a single string
    line="$*";

    # get number of words in line
    numWords=$(echo $line | wc -w);

    # sort the sequence
    # sortedLine=$(echo $line | tr " " "\n" | sort | tr "\n" " " );
    sortedLine=$(./sort.sh $line);

    # if numWords is odd, get middle value
    # otherwise get largest value of two middle values

    # NOTE:  don't need to check if it's even or odd,
    # median will always be the the (length/2)th element
    # by this definition.



    if [ $(expr $numWords % 2) -eq 0 ]; then
    	# sequence is even

	mid=$(./roundUpOrDown.sh $(./div.sh $numWords 2));
	mid=$(expr $mid + 1);
	
	# store mid'th element of $line sequence in $median
	# median="${!mid}"; # this uses $* as input, but we want the sorted input
	# median=${#sortedLine[$mid]};
	
    else
    	# sequence is odd
	
	mid=$(./roundUpOrDown.sh $(./div.sh $numWords 2));

	# store mid'th element of $line sequence in $median
	# median="${!mid}";
	# median=${sortedLine[$mid]};

    fi
    
    median=$(echo $sortedLine | cut -d " " -f $mid);

    echo $median;

}

echo $(median $*)
