#!/bin/bash
#compute unique contributions to semantics and phonology from different pathways in the OP focused and OS focused models

for k in 'LP' #'MP' 'HP'
do
	for i in 1 #2 3 4 5
	do
		#PS
		#./bin/evaluator_all -key ../Model/6kdict.txt -patterns ../Model/ps_randcon.pat -semantic -weights ../TrainedWeights/Oral/${k}/PS_Weight_${k}_v${i} #> PS_${k}_v${i}.txt
		#SP
		./bin/evaluator_all -key ../Model/6kdict.txt -patterns ../Model/sp.pat -weights ../TrainedWeights/Oral/${k}/SP_Weight_${k}_v${i} #> SP_${k}_v${i}.txt
		#OS
		#OP

	done
done
