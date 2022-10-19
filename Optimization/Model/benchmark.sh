#!/bin/bash

mkdir -p log

for i in $@
do
    echo "blis"
    ./bin/eng_oral_blis -seed 1 -epsilon 0.05 -iteration $i 2>> log/opt.txt
    #./bin/eng_oral_openmp -seed 1 -epsilon 0.05 -iteration $i 2>> log/openmp.txt
    echo "raw"
    ./bin/eng_oral_raw -seed 1 -epsilon 0.05 -iteration $i 2>> log/raw.txt
done
