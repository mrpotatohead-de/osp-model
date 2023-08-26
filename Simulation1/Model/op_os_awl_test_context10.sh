#!/bin/bash
# this program computes ps performance with different trained weights:
#for i in {0..5000000}; do
#   ./bin/evaluator -key 6kdict -patterns sp.pat -weights sp_attractonly_impairphon0.0_impairsem0.0_s1_t$i
#done
#export FILE_ROOT=~/triangle/training\ weights/mikenet_epsilon_02_01after200000
#FILE_ROOT="~/triangle/training\ weights/mikenet_epsilon_02_01after200000"
#export PATH=$PATH:$FILE_ROOT

pre=8000
for k in $(seq -f "%7.0f" 1 1 1)
do
	for i in $(seq -f "%7.0f" 0 100 4000)
	do
  	./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -weights output/triangle/weights/reading/basedonpretrain${pre}/trianglereading_OP_s${k}_ep0.010_t${i} >> output/triangle/results/reading/basedonpretrain${pre}/OP_phonology_awl_s${k}_t${i}.txt
 	./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -semantic -weights output/triangle/weights/reading/basedonpretrain${pre}/trianglereading_OP_s${k}_ep0.010_t${i} >> output/triangle/results/reading/basedonpretrain${pre}/OP_semantics_awl_s${k}_t${i}.txt

 	./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -weights output/triangle/weights/reading/basedonpretrain${pre}/trianglereading_OS_s${k}_ep0.010_t${i} >> output/triangle/results/reading/basedonpretrain${pre}/OS_phonology_awl_s${k}_t${i}.txt
	./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -semantic -weights output/triangle/weights/reading/basedonpretrain${pre}/trianglereading_OS_s${k}_ep0.010_t${i} >> output/triangle/results/reading/basedonpretrain${pre}/OS_semantics_awl_s${k}_t${i}.txt

   	#./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -weights output/triangle/weights/trianglereading_OP_s${k}_ep0.050_t${i} >> output/triangle/results/OP_phonology_result_s${k}_t${i}.txt
   	#./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -semantic -weights output/triangle/weights/trianglereading_OP_s${k}_ep0.050_t${i} >> output/triangle/results/OP_semantics_result_s${k}_t${i}.txt

   	#./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -weights output/triangle/weights/trianglereading_OS_s${k}_ep0.050_t${i} >> output/triangle/results/OS_phonology_result_s${k}_t${i}.txt
   	#./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -semantic -weights output/triangle/weights/trianglereading_OS_s${k}_ep0.050_t${i} >> output/triangle/results/OS_semantics_result_s${k}_t${i}.txt


	done
done
