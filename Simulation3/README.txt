%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Please refer to Chang, Taylor, Rastle and Monaghan (2020) paper for the model architecture and training/testing procedures.
The simulations are run using the Mikenet simulator: https://github.com/gtojty/OtoP/blob/master/Mikenet/mikenet_v8.tar.gz

Created by Ya-Ning Chang, 5 Aug 2020
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Simulation 3 folder contains the files for training and testing the english reading model. 
The compiled versions are bulit using Mac terminal, with the Mikenet simulator installed.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Model:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Executable files and training and testing scripts:
eng_oral: oral language training
eng_OP_focused_reading: training the OP focused reading model
eng_OS_focused_reading: training the OS focused reading model
eng_evaluator: evaluating the model’s performance
eng_evaluator_dol: evaluating the model’s division of labour
eng_oral.sh: a script for oral language training
eng_reading.sh: a script for reading training
eng_dol.sh: a script for the division of labour test

Training example files (*.pat):
Examples for english reading are the same as in Simulation 2.

Matlab files:
6ksem.mat: semantic vectors
examine_semantic_output.m

Other files:
6kdict.txt: the information (frequency, orthography, phonology) about the training set
eng_oral.c: english oral language training
eng_reading.c: english reading training
eng_mapping: phonemic features for each english letter
Others are the same as in Simulation 2.

%%%%%%%%%%%%%%%%%
Weight files:
%%%%%%%%%%%%%%%%%

Oral: Weight files of the five versions of the english word learning model with different levels of proficiency, including the weights for the speaking task (SP), for the hearing task (PS) and the combination of both (Oral).

Reading: Weight files of the five versions of the OP focused and OS focused model at the end of the reading training with different levels of proficiency. 

%%%%%%%%%%%%%%%%%
Data:
%%%%%%%%%%%%%%%%%

Model accuracy and division of labour data.
Datasets for the linear mixed-effect model analyses on model performance.
R script is the same as in Simulation 1.
