%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Please refer to Chang, Taylor, Rastle and Monaghan (2020) paper for the model architecture and training/testing procedures.
The simulations are run using the Mikenet simulator: https://github.com/gtojty/OtoP/blob/master/Mikenet/mikenet_v8.tar.gz

Created by Ya-Ning Chang, 5 Aug 2020
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Simulation 2 folder contains the files for training and testing the artificial word leanring and english reading model. 
The compiled versions are bulit using Mac terminal, with the Mikenet simulator installed.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Model:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Executable files and training and testing scripts:
eng_awl_oral: oral language training
eng_awl_OP_focused_reading: training the OP focused reading model
eng_awl_OS_focused_reading: training the OS focused reading model
awl_evaluator: evaluating the model’s performance
awl_evaluator_dol: evaluating the model’s division of labour
eng_awl_oral.sh: a script for oral language training
eng_awl_reading.sh: a script for reading training
eng_awl_dol.sh: a script for the division of labour test

Training example files (*.pat):
englishdict_randcon.pat: training examples of the english word learning task (6229 words)
sp.pat: training examples of the english speaking task
ps_randcon.pat: training examples of the english listening comprehension task
phono.pat: training examples of the english phonological attractor task
sem.pat: training examples of the english semantic attractor task
op_randcon_awl_neworth.pat: op examples of the artificial word learning task (24 items)
os_randcon_awl_neworth.pat: os examples of the artificial word learning task (24 items)
Others are the same as those in Simulation 1.

Matlab files:
The same as in Simulation 1.

Other files:
eng_awl_oral.c: oral language training
eng_awl_reading.c: reading training
Others are the same as in Simulation 1.

%%%%%%%%%%%%%%%%%
Weight files:
%%%%%%%%%%%%%%%%%

English: Weight files of the five versions of the english reading model at the end of the phase 1 and phase 2 training, including the weights for oral and reading.

English_Artificial: Weight files of the five versions of the artificial + english word learning model with different levels of proficiency at the end of the phase 1 and phase 2 training, including the weights for oral and reading. 

%%%%%%%%%%%%%%%%%
Data:
%%%%%%%%%%%%%%%%%

Model accuracy and division of labour data.
Datasets for the linear mixed-effect model analyses on model performance.
R script is the same as in Simulation 1.
