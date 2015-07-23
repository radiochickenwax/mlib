#!/bin/bash

# this file should get output the nth ($2) row of a file ($1) containing a matrix of numbers
# I think this outperforms 'awk (NR == n)', but haven't run comparisons

echo $(cat $1 | head -$2 | tail -1);
