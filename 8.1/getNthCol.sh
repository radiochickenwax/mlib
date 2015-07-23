#!/bin/bash

# output the nth ($2) column of a file ($1) containing a matrix of numbers
# alternatively, use awk '{print $2}'.  I think 'cut' is much cleaner.

cat $1 | cut -f$2
