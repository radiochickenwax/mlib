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


# Check if a filename is given by counting number of arguments.
# (browse-url "http://tldp.org/LDP/abs/html/internalvariables.html#ARGLIST")

if [ $# = 2 ]; then  # a filename is given.  Store it in a variable.
    filename=$2;
    # printf "You specified $filename as input\n";
    
    # check if file exists
    if [ -e $filename ]; then  # file exists
	fileExists="true";# file exists so move on
    else 
	printf "file '%s' not found\n" $filename;
	exit 1;
	
    fi
else
    filename="$*";
fi


declare -a avgs;  # array container to store averages
declare -a meds;  # array container to store medians


function getMedianAndAverageFromLine
{
    line=$1;

    # compute average of row
    lineAvg=$(./avg.sh $line);
    
    # store result in array container
    avgs+=($lineAvg);
    
    # get median of line
    lineMedian=$(./medians.sh $line);
    
    # store result in array container
    meds+=($lineMedian);
}

function displayRowResults
{
    # display averages if they exist
    avgArrLength=${#avgs[@]};
    # echo "array length: "  $avgArrLength; 
    
    printf "Averages\tMedians\n";
    #printf "--------\t--------";
    
    i=0;
    while [ $i -lt $avgArrLength ]; do
	printf "${avgs[$i]}\t\t${meds[$i]}\n";
	i=$(expr $i + 1 );
    done
}


function displayColResults
{
    avgArrLength=${#avgs[@]};

    # print averages    
    printf "Averages:\n";
    #printf "--------\t--------";
    
    i=0;
    while [ $i -lt $avgArrLength ]; do
	printf "${avgs[$i]}\t";
	i=$(expr $i + 1 );
    done
    printf "\n";

    # print medians
    printf "Medians:\n";
    i=0;
    while [ $i -lt $avgArrLength ]; do
	printf "${meds[$i]}\t";
	i=$(expr $i + 1 );
    done
    printf "\n";

}




if [ $(echo $1 | cut -c -2 ) = "-r" ]; then
    op="rows";
    # echo "Averaging rows";
    
    # loop over rows, storing ith row in $row
    max=$(cat $filename | wc -l);
    i=1; 	    
    
    while [ $i -le $max ]; do
	
	# extract row from matrix in file
	line=$(./getNthRow.sh $filename $i);
	
	# $(getMedianAndAverageFromLine $line)

	# compute average of row
	lineAvg=$(./avg.sh $line);
	
	# store result in array container
	avgs+=($lineAvg);
	
	# get median of line
	lineMedian=$(./medians.sh $line);
	
	# store result in array container
	meds+=($lineMedian);
		
	# increment i
	i=$( expr $i + 1 );
	
    done
    
    displayRowResults;

elif [ $(echo $1 | cut -c -2 ) = "-c" ]; then
    op="cols";

    max=$(./getNthCol.sh $filename 1 | wc -w);
    i=1;

    while [ $i -le $max ]; do

	# get column from input, convert to a line of words
	line=$(echo $(./getNthCol.sh $filename $i));
	
	# $(getMedianAndAverageFromLine $line)

	# compute average of col
	lineAvg=$(./avg.sh $line);
	
	# store result in array container
	avgs+=($lineAvg);
	
	# get median of line
	lineMedian=$(./medians.sh $line);
	
	# store result in array container
	meds+=($lineMedian);
	
	# increment i
	i=$( expr $i + 1 );

    done
    
    displayColResults;
	
else
    printf "Usage: stats.sh {-rows|-cols} [input_file] \n";	    
    exit 1;
fi


