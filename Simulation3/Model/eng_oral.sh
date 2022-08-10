#!/bin/bash
# Oral language training: training the model with different amounts of exposure (400000, 1200000, and 2000000)
# for three levels of oral proficiency 

for k in 400000 1200000 2000000
do
	for i in 1 2 3 4 5
	do
     
     echo "version=${i}, iteration=${k}"

     ./eng_oral -seed ${i} -epsilon 0.05 -iteration ${k}
     
	done
done
