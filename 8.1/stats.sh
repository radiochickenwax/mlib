#!/bin/bash
# calculuate averages and medians from an input file of numbers

# stats {-rows|-cols} [input_file]
# {-rows|-cols} is mandatory
# [input_file] is optional.  If left out, stats will use stdin

# ------------------------------
# This approach uses temp files 
# instead of arrays or functions
# ------------------------------


# "check for the right number and format of arguments"

if [ $1 = "-rows" ]; then
    op="rows";
elif [ $1 = "-cols" ]; then
    op="cols";
else
    printf "Usage: stats.sh {-rows|-cols} [input_file] \n";	    
    exit;
fi

# Check if a filename is given by counting number of arguments.

# (browse-url "http://tldp.org/LDP/abs/html/internalvariables.html#ARGLIST")

if [ $# = 2 ]; then  # a filename is given.  Store it in a variable.
    filename=$2;
    printf "You specified $filename as input\n";

    # (browse-url "http://tldp.org/LDP/abs/html/fto.html")
    if [ -e $2 ]; then     # check that $filename exists 
	
	# read file into array since it exists.
	# dump each line into a temp file and calculate average from that?
	
	

	if [ $op = "rows" ]; then

	    rowAvg=$(expr 1 + 1);
	    printf "rowAvg = $rowAvg\n";

	else # use cols
	    printf "using cols\n";
	fi
	
    else # a filename is not given.
	printf "file not found\n";
    fi
else
    printf "No file given\n"
fi


    
