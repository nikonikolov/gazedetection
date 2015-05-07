#!/bin/bash

for i in {1..132}
do
	picnumber="$(printf "%04d" $i)"
	infile="pics/videos/vid3/seq/out_$picnumber.jpg"
	outfile="pics/videos/vid3/out/out_$picnumber.jpg"

	echo "${filename}"
	./main $infile $outfile
done

echo "Done running jobs"