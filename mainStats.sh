#!/bin/bash

# calculate averages and medians from an input file of numbers

# stats {-rows|-cols} [input_file]
# {-rows|-cols} is mandatory
# [input_file] is optional.  If left out, stats will use stdin


# -------------------------------------------------------------
# this version broke everything into separate files.
# getNthRow.sh, getNthCol.sh, sum.sh, div.sh
# on the next iteration, I will merge these into a single file.
# -------------------------------------------------------------


#-----------------------------------------------------
# "check for the right number and format of arguments"
#-----------------------------------------------------

if [ $1 = "-rows" ]; then
    op="rows";
    # echo "Averaging rows";

    # Check if a filename is given by counting number of arguments.
    # (browse-url "http://tldp.org/LDP/abs/html/internalvariables.html#ARGLIST")
    
    if [ $# = 2 ]; then  # a filename is given.  Store it in a variable.
	filename=$2;
	# printf "You specified $filename as input\n";
	
	# check if file exists
	if [ -e $filename ]; then  # file exists
	    
	    # loop over rows, storing ith row in $row
	    numRows=$(cat $filename | wc -l);
	    i=1; 	    
	    declare -a avgs;  # array container to store averages
	    
	    while [ $i -lt $numRows ]; do
		
		# store ith row of in $line
		line=$(./getNthRow.sh $filename $i)
		
		# get number of words in line 
		numWords=$(echo $line | wc -w);
		
		# sum words
		lineSum=$(./sum.sh $line);
		
		# get average of line
		lineAvg=$(./div.sh $lineSum $numWords);
		
		# store result in array container
		avgs+=($lineAvg);
		
		# increment i
		i=$( expr $i + 1 );
		
	    done
	    
	else printf "file '%s' not found\n" $filename;
	fi
    fi

elif [ $1 = "-cols" ]; then
    op="cols";
else
    printf "Usage: stats.sh {-rows|-cols} [input_file] \n";	    
    exit;
fi


# display averages if they exist
avgArrLength=${#avgs[@]};
# echo "array length: "  $avgArrLength; 

printf "Averages\n";
echo "--------";

i=0;
while [ $i -lt $avgArrLength ]; do
    echo ${avgs[$i]};
    i=$(expr $i + 1 );
done

exit 1;
