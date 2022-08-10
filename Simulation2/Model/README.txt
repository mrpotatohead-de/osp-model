#######################################################################################################
# Training the English + Artificial Word Learning model - oral language training and Reading training
# Executable files : eng_awl_oral and eng_awl_reading
# Parameters: 
# -seed : random seed for initial weights (integer)
# -iteration: training times
# -trained_weight: load the trained weight to the model
#######################################################################################################
To train eng+awl the model, enter the following command in the unix-like terminal with Mikenet installed:

## oral language training 
sh eng_awl_oral.sh

## reading training: training the OP and OS focused training models with different low oral language proficiency 
(LP:low proficiency)

sh eng_awl_reading.sh

#######################################################################################################
# Testing the model's phonological performance and semantic performance
# Executable file : awl_evaluator
# Parameters:
# -key: the information about the training set
# -patterns: testing set (e.g., exp_jo_taylor_set1.txt) 
# -semantic: test the model's semantic performance (without this index, the default is to test the model's phonological performance) 
# -weights: trained weight
# >:  output file 
#######################################################################################################
To test the model, enter the following command in the unix-like terminal with Mikenet installed:

e.g. for listening comprehension (PS)
./awl_evaluator -key exp_jo_taylor_set1.txt -patterns ps_randcon_awl.pat -semantic -weights ../TrainedWeights/English_Artificial/Phase1/LP/English_Artificial_PS_Weight_LP_v1 > PS_LP_v1.txt

e.g. for speaking (SP)
./awl_evaluator -key exp_jo_taylor_set1.txt -patterns sp_awl.pat -weights ../TrainedWeights/English_Artificial/Phase1/LP/English_Artificial_SP_Weight_LP_v1 > SP_LP_v1.txt

e.g. for word comprehension (OS)
./awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -semantic -weights ../TrainedWeights/English_Artificial/Phase2/LP/OP/English_Artificial_OP_Reading_Weight_LP_v1_t4000 > OP_focused_OS_LP_v1.txt

e.g. for word naming (OP)
./awl_evaluator -key exp_jo_taylor_set1.txt -patterns englishdict_randcon_awl_neworth.pat -weights ../TrainedWeights/English_Artificial/Phase2/LP/OP/English_Artificial_OP_Reading_Weight_LP_v1_t4000 > OP_focused_OP_LP_v1.txt


The evaluator output format:
For phonology, column names are 'test_name', 'word',  'correctness', 'error score'
For semantics, column names are 'test_name', 'word', 'unit activation....'

To further compute the accuracy and error scores (euclidean distance) for semantics, a Matlab function is provided    
e.g. In the Matlab terminal, enter:
>> examine_semantic_output_awl('PS_LP_v1.txt')
and this will generate an output file 'nearest_PS_LP_v1.txt'

################################################################################################################################
#
# Division of Labour: Compute unique contributions to semantics and phonology from different pathways
# in the OP focused and OS focused models using the lesioning technique
#
################################################################################################################################
Enter the following command in the unix-like terminal with Mikenet installed:

sh awl_dol.sh


