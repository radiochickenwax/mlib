#!/bin/bash
# calculuate averages and medians from an input file of numbers

# stats {-rows|-cols} [input_file]
# {-rows|-cols} is mandatory
# [input_file] is optional.  If left out, stats will use stdin


# "check for the right number and format of arguments"
# output error message to stderr if incorrect

# start by checking the number of arguments
# (browse-url "http://tldp.org/LDP/abs/html/internalvariables.html#ARGLIST")

numargs=$#;
# echo "number of  arguments:  $numargs";



#if [ $numargs -lt 1 ]; then
#    printf "Usage: stats.sh {-rows|-cols} [input_file] \n";

#else
    if [ $1 = "-rows" ]; then
	# sum rows
	printf "Summing rows\n";
    elif [ $1 = "-cols" ]; then
	printf "Summing cols\n"
    else
	printf "Usage: stats.sh {-rows|-cols} [input_file] \n";	    
    fi

    # check if a filename is given on the commandline
    
#fi
