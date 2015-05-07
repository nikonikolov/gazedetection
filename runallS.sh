#!/bin/bash

for i in {1..3}
do
	echo "Processing pics/s"$i".jpg"
	./main pics/s$i.jpg pics/os$i.jpg
done

echo "Done running jobs"