#!/bin/bash

# calculate the average of a series
# where the series is all on one line, separated by spaces

function avg ()
{
    # "line" is all of the input parameters in a single string
    line="$*";

    # get number of words in line 
    numWords=$(echo $line | wc -w);
    
    # sum words
    lineSum=$(./sum.sh $line);
    
    # get decimal average of line
    lineAvg=$(./div.sh $lineSum $numWords);
    
    # convert average to an integer
    lineAvg=$(./roundUpOrDown.sh $lineAvg);

    echo $lineAvg;
    exit 1;
}

echo $(avg "$*")
