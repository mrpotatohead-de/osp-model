#!/bin/bash
#Reading training: Training the OP and OS focused training models with different levels of oral language proficiency 
#(LP:low proficiency, MP:Moderate proficiency, HP:High proficiency) 

for k in 'LP' 'MP' 'HP'
do
	for i in 1 2 3 4 5
	do
     
     echo "OP focused training: version=${i}, proficiency level=${k}"
     ./eng_OP_focused_reading -seed ${i} -trained_weights ../TrainedWeights/Oral/${k}/Oral_Weight_${k}_v${i} -epsilon 0.05 -iteration 1000000

     echo "OS focused training: version=${i}, proficiency level=${k}"
     ./eng_OS_focused_reading -seed ${i} -trained_weights ../TrainedWeights/Oral/${k}/Oral_Weight_${k}_v${i} -epsilon 0.05 -iteration 1000000

	done
done
