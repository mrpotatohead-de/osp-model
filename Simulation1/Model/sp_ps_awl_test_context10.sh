#!/bin/bash
# this program computes ps performance with different trained weights:
#for i in {0..5000000}; do
#   ./bin/evaluator -key 6kdict -patterns sp.pat -weights sp_attractonly_impairphon0.0_impairsem0.0_s1_t$i
#done
#export FILE_ROOT=~/triangle/training\ weights/mikenet_epsilon_02_01after200000
#FILE_ROOT="~/triangle/training\ weights/mikenet_epsilon_02_01after200000"
#export PATH=$PATH:$FILE_ROOT
for k in $(seq -f "%7.0f" 1 1 5)
do
	for i in $(seq -f "%7.0f" 11000 1000 20000)
	do
   	
#   	./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns ps_randcon_awl.pat -semantic -weights output/pretrain/weights/ps_attractonly_recur50_randcon10_s${k}_ep0.050_t${i} >> output/pretrain/results/ps_result_s${k}_ep0.050_t${i}.txt   	
#   	./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns sp_awl.pat -weights output/pretrain/weights/sp_attractonly_recur50_randcon10_s${k}_ep0.050_t${i} >> output/pretrain/results/sp_result_s${k}_ep0.050_t${i}.txt

   	./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns ps_randcon_awl.pat -semantic -weights output/triangle/weights/sep/10_001/ps_pretrainawl_s${k}_ep0.010_t${i} >> output/triangle/results/pretrain_awl/10_001/sep_ps_result_s${k}_ep0.010_t${i}.txt   	
   	./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns sp_awl.pat -weights output/triangle/weights/sep/10_001/sp_pretrainawl_s${k}_ep0.010_t${i} >> output/triangle/results/pretrain_awl/10_001/sep_sp_result_s${k}_ep0.010_t${i}.txt

   	#./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns ps_randcon_awl.pat -semantic -weights output/triangle/weights/comb/ps_pretrainawl_s${k}_ep0.050_t${i} >> output/triangle/results/pretrain_awl/comb_ps_result_s${k}_ep0.050_t${i}.txt   	
   	#./bin/awl_evaluator -key exp_jo_taylor_set1.txt -patterns sp_awl.pat -weights output/triangle/weights/comb/sp_pretrainawl_s${k}_ep0.050_t${i} >> output/triangle/results/pretrain_awl/comb_sp_result_s${k}_ep0.050_t${i}.txt


	done
done
