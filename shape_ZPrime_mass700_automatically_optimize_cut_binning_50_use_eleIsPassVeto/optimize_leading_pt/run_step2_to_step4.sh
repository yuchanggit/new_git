#!/bin/bash

if [ -z $3 ]; then

    #                          10          115           20
    echo "Usage: $0 [number of cuts] [lowerest cut ] [cut scan width] "
    exit 0

fi

N_cut_points=$1 
lowest_cut=$2
scan_width=$3

echo "run run_step2_to_step4.sh "




#cmsenv
eval `scramv1 runtime -sh`

cd step2_produce_TxtFile_and_ShapeROOT_for_each_cut_points
./run_step2.sh $N_cut_points $lowest_cut $scan_width
cd ../

cd step3_make_datacard
./run_step3.sh 
cd ../

cd step4_run_limit_tool
./run_step4.sh
cd ../

#cd step5_plot
#./run_step5.sh
#cd ../


