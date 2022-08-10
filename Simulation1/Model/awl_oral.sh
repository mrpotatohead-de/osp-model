#!/bin/bash
# Oral language training: training the model with different amounts of exposure (500, 1000, and 2000)
# for three levels of oral proficiency 

for k in 500 1000 2000
do
	for i in 1 2 3 4 5
	do
     
     echo "version=${i}, iteration=${k}"
     ./awl_oral -seed ${i} -epsilon 0.05 -iteration ${k}

	done
done
