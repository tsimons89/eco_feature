#!/bin/bash

NUM_CREATURES=5
NUM_TREES=5
TREE_DEPTH=5
RESULTS_DIR=../results/compare_eco_setups_tmp
TRAIN_DATA_DIR=../../my_eco_feature/data/8fish/train
TEST_DATA_DIR=../../my_eco_feature/data/8fish/test
OUT_FILE=compare_eco_setups_out.txt
echo creatures trees depth nodes accuracy > $OUT_FILE
for NUM_CREATURES in 40 30 20 10 5
do
    for NUM_TREES in 20 15 10 5 2 1 
    do
	for TREE_DEPTH in 20 15 20 5 3 2
	do
	    if [ -d "$RESULTS_DIR" ]; then
		rm -r $RESULTS_DIR
	    fi
	    mkdir $RESULTS_DIR
	    ../bin/eco_train -n $NUM_CREATURES -t $NUM_TREES -e $TREE_DEPTH -d $TRAIN_DATA_DIR -o $RESULTS_DIR
	    result=$(../bin/eco_test -d $TEST_DATA_DIR -r $RESULTS_DIR)
	    percent=$(echo $result | awk '{print $(NF)}')
	    nodes=$(grep depth: $RESULTS_DIR/rf* |wc -l)
	    echo $NUM_CREATURES $NUM_TREES $TREE_DEPTH $nodes $percent >> $OUT_FILE
	    rm -r $RESULTS_DIR
	done
    done
done
