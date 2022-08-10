#!/bin/bash
# this program computes ps performance with different trained weights:
#for i in {0..5000000}; do
#   ./evaluator -key 6kdict -patterns sp.pat -weights sp_attractonly_impairphon0.0_impairsem0.0_s1_t$i
#done
#export FILE_ROOT=~/triangle/training\ weights/mikenet_epsilon_02_01after200000
#FILE_ROOT="~/triangle/training\ weights/mikenet_epsilon_02_01after200000"
#export PATH=$PATH:$FILE_ROOT

pre=10000

for k in $(seq -f "%7.0f" 1 1 5)
do
	for i in $(seq -f "%7.0f" 1000 50 1000)
	do
   	#./evaluator_dol_awl -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -weights output/triangle/weights/trianglereading_OP_s1_ep0.050_t1000 >> OP_avg_rawinputtophon_awl_t1000.txt
   	#./evaluator_dol_awl -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -weights output/triangle/weights/trianglereading_OS_s1_ep0.050_t1000 >> OS_avg_rawinputtophon_awl_t1000.txt

   	#./evaluator_dol_awl -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -weights output/triangle/weights/trianglereading_OP_s1_ep0.050_t1000 >> OP_avg_meanunitinputtosem_awl_t1000.txt
   	#./evaluator_dol_awl -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -weights output/triangle/weights/trianglereading_OS_s1_ep0.050_t1000 >> OS_avg_meanunitinputtosem_awl_t1000.txt

    #./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -OSalone 1 -semantic -weights output/triangle/weights/basedonpretrain10000/trianglereading_OP_s${k}_ep0.050_t1000 > Lesion_DOL/OP_OSalone_withcontextatt_basedonpretrain10000_s${k}_t1000.txt
    #./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -PSalone 1 -semantic -weights output/triangle/weights/basedonpretrain10000/trianglereading_OP_s${k}_ep0.050_t1000 > Lesion_DOL/OP_PSalone_withcontextatt_basedonpretrain10000_s${k}_t1000.txt
    #./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -OSalone 1 -semantic -weights output/triangle/weights/basedonpretrain10000/trianglereading_OS_s${k}_ep0.050_t1000 > Lesion_DOL/OS_OSalone_withcontextatt_basedonpretrain10000_s${k}_t1000.txt
    #./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -PSalone 1 -semantic -weights output/triangle/weights/basedonpretrain10000/trianglereading_OS_s${k}_ep0.050_t1000 > Lesion_DOL/OS_PSalone_withcontextatt_basedonpretrain10000_s${k}_t1000.txt

	./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -OSalone 1 -semantic -weights output/triangle/weights/basedonpretrain${pre}/trianglereading_OP_s${k}_ep0.050_t1000 > Lesion_DOL/OP_OSalone_withcontextatt_basedonpretrain${pre}_s${k}_t1000.txt
    ./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -PSalone 1 -semantic -weights output/triangle/weights/basedonpretrain${pre}/trianglereading_OP_s${k}_ep0.050_t1000 > Lesion_DOL/OP_PSalone_withcontextatt_basedonpretrain${pre}_s${k}_t1000.txt
    ./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -OSalone 1 -semantic -weights output/triangle/weights/basedonpretrain${pre}/trianglereading_OS_s${k}_ep0.050_t1000 > Lesion_DOL/OS_OSalone_withcontextatt_basedonpretrain${pre}_s${k}_t1000.txt
    ./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -PSalone 1 -semantic -weights output/triangle/weights/basedonpretrain${pre}/trianglereading_OS_s${k}_ep0.050_t1000 > Lesion_DOL/OS_PSalone_withcontextatt_basedonpretrain${pre}_s${k}_t1000.txt


    #./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -OPalone 1 -weights output/triangle/weights/basedonpretrain10000/trianglereading_OP_s${k}_ep0.050_t1000 > Lesion_DOL/OP_OPalone_withcontextatt_basedonpretrain10000_s${k}_t1000.txt
    #./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -SPalone 1 -weights output/triangle/weights/basedonpretrain10000/trianglereading_OP_s${k}_ep0.050_t1000 > Lesion_DOL/OP_SPalone_withcontextatt_basedonpretrain10000_s${k}_t1000.txt
    #./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -OPalone 1 -weights output/triangle/weights/basedonpretrain10000/trianglereading_OS_s${k}_ep0.050_t1000 > Lesion_DOL/OS_OPalone_withcontextatt_basedonpretrain10000_s${k}_t1000.txt
    #./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -SPalone 1 -weights output/triangle/weights/basedonpretrain10000/trianglereading_OS_s${k}_ep0.050_t1000 > Lesion_DOL/OS_SPalone_withcontextatt_basedonpretrain10000_s${k}_t1000.txt

    ./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -OPalone 1 -weights output/triangle/weights/basedonpretrain${pre}/trianglereading_OP_s${k}_ep0.050_t1000 > Lesion_DOL/OP_OPalone_withcontextatt_basedonpretrain${pre}_s${k}_t1000.txt
    ./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -SPalone 1 -weights output/triangle/weights/basedonpretrain${pre}/trianglereading_OP_s${k}_ep0.050_t1000 > Lesion_DOL/OP_SPalone_withcontextatt_basedonpretrain${pre}_s${k}_t1000.txt
    ./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -OPalone 1 -weights output/triangle/weights/basedonpretrain${pre}/trianglereading_OS_s${k}_ep0.050_t1000 > Lesion_DOL/OS_OPalone_withcontextatt_basedonpretrain${pre}_s${k}_t1000.txt
    ./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -SPalone 1 -weights output/triangle/weights/basedonpretrain${pre}/trianglereading_OS_s${k}_ep0.050_t1000 > Lesion_DOL/OS_SPalone_withcontextatt_basedonpretrain${pre}_s${k}_t1000.txt


	done
done


#./evaluator_all_context10_awl_lesion -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl.pat -OPalone 1 -weights output/triangle/weights/trianglereading_OP_s1_ep0.050_t1000