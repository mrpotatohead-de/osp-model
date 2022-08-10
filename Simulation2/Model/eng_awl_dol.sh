#!/bin/bash
#compute unique contributions to semantics and phonology from different pathways in the OP focused and OS focused models

for k in 'LP' 'MP' 'HP'
do
	for i in 1 2 3 4 5
	do

    #for semantics
	./awl_evaluator_dol -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -OSalone 1 -semantic -weights ../TrainedWeights/English_Artificial/Phase2/${k}/OP/English_Artificial_OP_Reading_Weight_${k}_v${i}_t4000 > OPFocused_OSalone_${k}_v${i}_t4000.txt
	./awl_evaluator_dol -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -PSalone 1 -semantic -weights ../TrainedWeights/English_Artificial/Phase2/${k}/OP/English_Artificial_OP_Reading_Weight_${k}_v${i}_t4000 > OPFocused_PSalone_${k}_v${i}_t4000.txt
	./awl_evaluator_dol -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -OSalone 1 -semantic -weights ../TrainedWeights/English_Artificial/Phase2/${k}/OS/English_Artificial_OS_Reading_Weight_${k}_v${i}_t4000 > OSFocused_OSalone_${k}_v${i}_t4000.txt
	./awl_evaluator_dol -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -PSalone 1 -semantic -weights ../TrainedWeights/English_Artificial/Phase2/${k}/OS/English_Artificial_OS_Reading_Weight_${k}_v${i}_t4000 > OSFocused_PSalone_${k}_v${i}_t4000.txt


    #for phonology
	./awl_evaluator_dol -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -OPalone 1 -weights ../TrainedWeights/English_Artificial/Phase2/${k}/OP/English_Artificial_OP_Reading_Weight_${k}_v${i}_t4000 > OPFocused_OPalone_${k}_v${i}_t4000.txt
	./awl_evaluator_dol -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -SPalone 1 -weights ../TrainedWeights/English_Artificial/Phase2/${k}/OP/English_Artificial_OP_Reading_Weight_${k}_v${i}_t4000 > OPFocused_SPalone_${k}_v${i}_t4000.txt
	./awl_evaluator_dol -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -OPalone 1 -weights ../TrainedWeights/English_Artificial/Phase2/${k}/OS/English_Artificial_OS_Reading_Weight_${k}_v${i}_t4000 > OSFocused_OPalone_${k}_v${i}_t4000.txt
	./awl_evaluator_dol -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -SPalone 1 -weights ../TrainedWeights/English_Artificial/Phase2/${k}/OS/English_Artificial_OS_Reading_Weight_${k}_v${i}_t4000 > OSFocused_SPalone_${k}_v${i}_t4000.txt


	done
done
