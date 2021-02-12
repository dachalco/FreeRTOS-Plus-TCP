#!/bin/bash

# Get the filename from the command line (in this case, from CMake)
FILE=$1

#echo $FILE

# Get all the locations of function definitions in the file
#     Get the functions in tabular form.
#     Get all the static ones.
#     Ignore the casting functions
#     Get all line numbers and ignore all else.
#     Use grep once more to remove whitespace.
TEMP=$(ctags -x --c-types=f ${FILE}  \
      | grep "static" \
      | grep -v "ipDECL_CAST" \
      | grep -oh "[0-9]* " \
      | grep -o "[0-9]*")

# For all the lines we got from above,
for value in $TEMP
do
    # Note the initial line number
    loop_val=${value};

    # Sed is piped to do this:
    #   Get the line from the file
    #   Remove the static qualifier
    #   if a closing parantheses ')' is found, then return 0 or else return 100
    #     And print the sed modified value to the second argument passed to script
    sed "${value}q;d" ${FILE} |\
         sed -E "s/[_]?static/      /" |\
         sed '/)/!{q100}; s/)/);/' >> $2

    # Note the output of the last sed. (0 or 100)
    output=$?;

    # While the output is 100, it implies that we have not found ')' and thus the
    # end of the function
    while [ "$output" -ne 0 ]; do

         # Increment the line number
         loop_val=`expr $loop_val + 1`

         # Sed is piped as follows:
         #    Get the line from the file
         #    If a closing parantheses ')' is found, then return 0 or else return 100
         #       And print the sed modified value to the second argument passed to script
         sed "${loop_val}q;d" ${FILE} | sed '/)/!{q100}; s/)/);/' >> $2
         output=$?
    done;
done;
