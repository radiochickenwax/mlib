#!/bin/bash
# calculuate averages and medians from an input file of numbers

# stats {-rows|-cols} [input_file]
# {-rows|-cols} is mandatory
# [input_file] is optional.  If left out, stats will use stdin


# "check for the right number and format of arguments"

if [ $1 = "-rows" ]; then
    op="rows";
elif [ $1 = "-cols" ]; then
    op="cols";
else
    printf "Usage: stats.sh {-rows|-cols} [input_file] \n";	    
    exit;
fi

# delete this checkpoint
printf "Summing across $op\n";

# Check if a filename is given by counting number of arguments.

# (browse-url "http://tldp.org/LDP/abs/html/internalvariables.html#ARGLIST")

if [ $# = 2 ]; then  # a filename is given.  Store it in a variable.
    filename=$2;
    printf "You specified $filename as input\n";

    # (browse-url "http://tldp.org/LDP/abs/html/fto.html")
    if [ -e $2 ]; then     # check that $filename exists 
	printf "file exists\n";
	printf "calculating average:\n"
	
	# read lines from file into an array

	# (browse-url "http://stackoverflow.com/questions/11393817/bash-read-lines-in-file-into-an-array")

	IFS=$'\n' GLOBIGNORE='*';  # what trickery is this?  
	# read -d '' -r -a lines < $filename;  

	# I prefer to use cat instead of read, it is more general.
	lines=($(cat $filename));

	# check number of lines
	numLines=${#lines[@]};  # note the hashtag in lines.  Why?
	
	echo "numLines = $numLines";

	# checkpoint:  test that lines are read properly.
	# for (( i=0; i<$numLines ));  # I wish this syntax worked more easily
	
	# for line in $lines  # broken

	# the following works.  It's unnecessary though.
	#-----------
	# for line in ${lines[@]}  # no hash tag here eh?  Why?!!
	#  do
	#     printf "%s\n" "$line";
	#     #printf "%s\n" ${lines[$i]};
	#  done;
	

	if [ $op = "rows" ]; then
	    # read 
	    rowAvg=$(expr 1 + 1);
	    printf "rowAvg = $rowAvg\n";

	else
	    printf "no thatnks";
	fi
	
    else # a filename is not given.
	printf "file not found\n";
    fi
else
    printf "No file given\n"
fi


    
