%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Please refer to Chang, Taylor, Rastle and Monaghan (2020) paper for the model architecture and training/testing procedures.
The simulations are run using the Mikenet simulator: https://github.com/gtojty/OtoP/blob/master/Mikenet/mikenet_v8.tar.gz

Created by Ya-Ning Chang, 5 Aug 2020
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


Simulation 1 folder contains all of the files needed to train and test the simulations.
The compiled versions are bulit using Mac terminal, with the Mikenet simulator installed.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Model (incl. examples):
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

README: Examples are provided, including commands and parameters for training and testing the artificial word learning model


Executable files and training and testing scripts:
awl_oral: oral language training
awl_OP_focused_reading: training the OP focused reading model
awl_OS_focused_reading: training the OS focused reading model
awl_evaluator: evaluating the model’s performance
awl_evaluator_dol: evaluating the model’s division of labour
awl_oral.sh: a script for oral language training
awl_reading.sh: a script for reading training
awl_dol.sh: a script for the division of labour test


Training example files (*.pat):
englishdict_randcon_awl.pat: training examples of the artificial word learning task (24 items)
sp_awl.pat: training examples of the speaking task
ps_randcon_awl.pat: training examples of the listening comprehension task
phono_awl.pat: training examples of the phonological attractor task
sem_awl.pat: training examples of the semantic attractor task


Matlab files:
exp_jo_taylor_set1_meaning_in_6ksem.txt: semantic vectors
examine_semantic_output_awl: compute semantic accuracy and error scores generated from the evaluator output


Other files:
exp_jo_taylor_set1.txt: the information (frequency, orthography, phonology) about the training set
mapping: phonemic features for each letter
awl_oral.c: oral language training
awl_reading.c: reading training
reading_model_recur50_randcon.c: building the model

%%%%%%%%%%%%%%%%%
Weight files:
%%%%%%%%%%%%%%%%%

Oral: Weight files of the five versions of the artificial word learning model with different levels of proficiency, including the weights for the speaking task (SP), for the hearing task (PS) and the combination of both (Oral).

Reading: Weight files of the five versions of the OP focused and OS focused model at the end of the reading training with different levels of proficiency. 


%%%%%%%%%%%%%%%%%
Data:
%%%%%%%%%%%%%%%%%

Model accuracy and division of labour data.
R script and datasets for the linear mixed-effect model analyses on model performance.

