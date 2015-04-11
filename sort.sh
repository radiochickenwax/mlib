#!/bin/bash

function sortLine ()
{
    line="$*";
    sortedLine=$(echo $line | tr " " "\n" | sort -g | tr "\n" " " );
    echo $sortedLine;
}

echo $(sortLine "$*");
