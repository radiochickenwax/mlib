#!/bin/bash

# outline of strategy:
# mantissa = string up until period.  
#   example:  for 5.34,  mantissa = 5

# decimal = first character after period.
# if it's >= 5, round mantissa up, otherwise leave mantissa alone.

function roundUpOrDown ()  
{
    # expected input:  1 string possibly containing decimals
    
    # check if string contains period
    if [[ $1 == *"."* ]]; then
	# string contains period.

	# get mantissa 
	mantissa=$(echo $1 | cut -d "." -f 1);

	# get decimal
	decimal=$(echo $1 | cut -d "." -f 2 | cut -c 1);
	# the first cut gets everything after the period,
	# the 2nd removes everything after the first character

	# round mantissa up if the decimal part is greater than 5,
	# otherwise just return it.

	if [ $decimal -ge 5 ]; then
	    echo $(expr $mantissa + 1);
	    exit 1;
	else
	    echo $(expr $mantissa);
	    exit 1;
	fi
	
	
    else
	# string is already an integer, return it.
	echo $1;
	exit 1;
    fi
}


echo $(roundUpOrDown $1);
exit 1;
