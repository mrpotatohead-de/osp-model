#!/bin/bash
#compute unique contributions to semantics and phonology from different pathways in the OP focused and OS focused models

for k in 'LP' 'MP' 'HP'
do
	for i in 1 2 3 4 5
	do

    #for semantics
	./eng_evaluator_dol -key 6kdict.txt -patterns englishdict_randcon.pat -OSalone 1 -semantic -weights ../TrainedWeights/Reading/${k}/OP/OP_Reading_Weight_${k}_v${i}_t1000000 > OPFocused_OSalone_${k}_v${i}_t1000000.txt
	./eng_evaluator_dol -key 6kdict.txt -patterns englishdict_randcon.pat -PSalone 1 -semantic -weights ../TrainedWeights/Reading/${k}/OP/OP_Reading_Weight_${k}_v${i}_t1000000 > OPFocused_PSalone_${k}_v${i}_t1000000.txt
	./eng_evaluator_dol -key 6kdict.txt -patterns englishdict_randcon.pat -OSalone 1 -semantic -weights ../TrainedWeights/Reading/${k}/OS/OS_Reading_Weight_${k}_v${i}_t1000000 > OSFocused_OSalone_${k}_v${i}_t1000000.txt
	./eng_evaluator_dol -key 6kdict.txt -patterns englishdict_randcon.pat -PSalone 1 -semantic -weights ../TrainedWeights/Reading/${k}/OS/OS_Reading_Weight_${k}_v${i}_t1000000 > OSFocused_PSalone_${k}_v${i}_t1000000.txt


    #for phonology
	./eng_evaluator_dol -key 6kdict.txt -patterns englishdict_randcon.pat -OPalone 1 -weights ../TrainedWeights/Reading/${k}/OP/OP_Reading_Weight_${k}_v${i}_t1000000 > OPFocused_OPalone_${k}_v${i}_t1000000.txt
	./eng_evaluator_dol -key 6kdict.txt -patterns englishdict_randcon.pat -SPalone 1 -weights ../TrainedWeights/Reading/${k}/OP/OP_Reading_Weight_${k}_v${i}_t1000000 > OPFocused_SPalone_${k}_v${i}_t1000000.txt
	./eng_evaluator_dol -key 6kdict.txt -patterns englishdict_randcon.pat -OPalone 1 -weights ../TrainedWeights/Reading/${k}/OS/OS_Reading_Weight_${k}_v${i}_t1000000 > OSFocused_OPalone_${k}_v${i}_t1000000.txt
	./eng_evaluator_dol -key 6kdict.txt -patterns englishdict_randcon.pat -SPalone 1 -weights ../TrainedWeights/Reading/${k}/OS/OS_Reading_Weight_${k}_v${i}_t1000000 > OSFocused_SPalone_${k}_v${i}_t1000000.txt


	done
done
