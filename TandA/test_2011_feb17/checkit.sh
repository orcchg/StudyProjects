#!/bin/bash
# UNIX or Linux
# Automatic check system scriprt for offline testing

PROGNAME=`basename $0`
TASK_DIR="./tasks"
SOLUTION_DIR="./solutions"

function usage()
{
	echo "Usage: $PROGNAME chapter task_number" 1>&2
	echo "Example: $PROGNAME arr 00" 1>&2
	exit 0
}
# Check for correct number of parameters
test $# -gt 1 || usage;

SUBDIR="$1"
TASKID="${SUBDIR}_$2"
PREFIX_BEFORE="_begin"
PREFIX_AFTER="_end"

# Compile task before testing
CFILE="$SOLUTION_DIR/$SUBDIR/__$TASKID.c"
test -f $CFILE && rm -f $CFILE 
test -f "$TASK_DIR/$SUBDIR/$TASKID/${TASKID}${PREFIX_BEFORE}.c" && \
	cp "$TASK_DIR/$SUBDIR/$TASKID/${TASKID}${PREFIX_BEFORE}.c" "$CFILE"
cat "$SOLUTION_DIR/$SUBDIR/$TASKID.c" >> "$CFILE"
test -f "$TASK_DIR/$SUBDIR/$TASKID/${TASKID}${PREFIX_AFTER}.c" && \
	cat "$TASK_DIR/$SUBDIR/$TASKID/${TASKID}${PREFIX_AFTER}.c" >> "$CFILE"
gcc -Wall -o "$SOLUTION_DIR/$TASKID.exe" "$CFILE"
if test $? -ne 0; then
	# Error message is printed by compiler
	exit 1
fi

# Run all tests
for ID in $TASK_DIR/$SUBDIR/$TASKID/tests/*.dat ; do
	ID=`basename $ID .dat`
	# echo $ID
	echo "======================= TEST $ID"
	"$SOLUTION_DIR/$TASKID.exe" < "$TASK_DIR/$SUBDIR/$TASKID/tests/$ID.dat" | diff -b -B - "$TASK_DIR/$SUBDIR/$TASKID/tests/$ID.ans"
	if test $? -ne 0; then
		# Error message is printed by compiler
		echo "........................FAIL"
		echo "INPUT DATA:"
		cat "$TASK_DIR/$SUBDIR/$TASKID/tests/$ID.dat"
		exit 1
	fi
	echo "....................... OK"
done
exit 0

