#!/bin/bash
# Oral language training: training the model with different amounts of exposure (4000, 8000, and 15000)
# for three levels of oral proficiency 

for k in 4000 8000 15000
do
	for i in 1 2 3 4 5
	do
     
     echo "version=${i}, iteration=${k}"

     ./eng_awl_oral  -seed ${i} -trained_weights ../TrainedWeights/English/Phase2/English_Phase2_v${i} -epsilon 0.01 -iteration ${k}

	done
done
