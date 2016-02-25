#!/bin/bash

if [ -z $3 ]; then

    #                          10          115           20
    echo "Usage: $0 [number of cuts] [lowerest cut ] [cut scan width] "
    exit 0

fi

N_cut_points=$1  
lowest_cut=$2
scan_width=$3

echo "run run_step2.sh "

test -e text_and_ROOT_files && rm -r text_and_ROOT_files || echo " text_and_ROOT_files Not exist"
mkdir text_and_ROOT_files

#cmsenv
eval `scramv1 runtime -sh`

#root -l -q -b produce_txt_ROOT_for_cuts.C++
root -l -q -b produce_txt_ROOT_for_cuts.C++\($N_cut_points\,$lowest_cut\,$scan_width\)

#root -l -q -b plot_mass.C++

