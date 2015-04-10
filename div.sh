#!/bin/bash
# ------------------------------------
# floating point division in bash
#
# taken mostly from
# http://stackoverflow.com/questions/12147040/division-in-script-and-floating-point/24431665#24431665
#
# see also 
# http://en.wikipedia.org/wiki/Division_algorithm
#----------------------------------------
div () # $1 = numerator,   $2 = denominator
{
    if [ $2 -eq 0 ]; then echo  "divideByZero"; exit; fi
    local p=12                            # precision
    local c=${c:-0}                       # precision counter.  Wat?  
                                          # what is ${c:-0} ?
					  # lookup "index slicing" 

    local d=.                             # decimal separator
    local r=$(($1/$2));                   # result of division

    echo -n $r                            # display result without newline

    # things get stranger here.
    local m=$(($r*$2))                           # what?
    [ $c -eq 0 ] && [ $m -ne $1 ] && echo -n $d  # echo decimal point if...
    [ $1 -eq $m ] || [ $c -eq $p ] && return     # return if..
    local e=$(($1-$m))               # subtract decimal portion
    let c=c+1                        # increment
    div $(($e*10)) $2                # recurse
}

printf "%s" $(div $1 $2);
printf "\n";

