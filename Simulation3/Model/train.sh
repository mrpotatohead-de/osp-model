#!/bin/bash

# train the entire model

# train oral 
# Oral language training: training the model with different amounts of exposure (400000, 1200000, and 2000000)
# for three levels of oral proficiency 

#for k in 400000 1200000 2000000
#do
#	for i in 1 2 3 4 5
#	do
     
#        echo "version=${i}, iteration=${k}"

#        ./bin/eng_oral_blis -seed ${i} -epsilon 0.05 -iteration ${k}
     
#	done
#done

#mkdir ./TrainedWeights_BLIS
#mv ./*.gz ./TrainedWeights_BLIS

echo BLIS finifhed, strat training RAW

for k in 400000 1200000 2000000
do
	for i in 1 2 3 4 5
	do
     
        echo "version=${i}, iteration=${k}"

        ./bin/eng_oral -seed ${i} -epsilon 0.05 -iteration ${k}
     
	done
done

mkdir ./TrainedWeights_RAW
mv ./*.gz ./TrainedWeights_RAW

# train reading
#Reading training: Training the OP and OS focused training models with different levels of oral language proficiency 
#(LP:low proficiency, MP:Moderate proficiency, HP:High proficiency) 

for k in 'LP' 'MP' 'HP'
do
	for i in 1 2 3 4 5
	do
     
        echo "OP focused training: version=${i}, proficiency level=${k}"
        ./bin/eng_OP_focused_reading_blis -seed ${i} -trained_weights ./TrainedWeights_BLIS/Oral_Weight_${k}_v${i} -epsilon 0.05 -iteration 1000000

        echo "OS focused training: version=${i}, proficiency level=${k}"
        ./bin/eng_OS_focused_reading_blis -seed ${i} -trained_weights ./TrainedWeights_BLIS/Oral_Weight_${k}_v${i} -epsilon 0.05 -iteration 1000000

	done
done


mv ./*.gz ./TrainedWeights_BLIS

for k in 'LP' 'MP' 'HP'
do
	for i in 1 2 3 4 5
	do
     
        echo "OP focused training: version=${i}, proficiency level=${k}"
        ./bin/eng_OP_focused_reading -seed ${i} -trained_weights ./TrainedWeights_RAW/Oral_Weight_${k}_v${i} -epsilon 0.05 -iteration 1000000

        echo "OS focused training: version=${i}, proficiency level=${k}"
        ./bin/eng_OS_focused_reading -seed ${i} -trained_weights ./TrainedWeights_RAW/Oral_Weight_${k}_v${i} -epsilon 0.05 -iteration 1000000

	done
done


mv ./*.gz ./TrainedWeights_RAW