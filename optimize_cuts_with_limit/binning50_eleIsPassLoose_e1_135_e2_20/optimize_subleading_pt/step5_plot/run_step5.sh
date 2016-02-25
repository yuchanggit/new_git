#!/bin/bash

if [ -z $4 ]; then
    #                          10          115           20             Datacards_text_and_ROOT_files
    echo "Usage: $0 [number of cuts] [lowerest cut ] [cut scan width] [ input datacard dir ] "
    exit 0
fi

N_cut_points=$1  
lowest_cut=$2
scan_width=$3
input_dir=$4

#path_to_save=/afs/cern.ch/user/y/yuchang/www/optimize_cut_with_limit_use_eleIsPassVeto/leading_pt/
path_to_save=/afs/cern.ch/user/y/yuchang/www/optimize_cut_with_limit_use_eleIsPassLoose/subleading_pt/

echo "run run_step5.sh "

#test -e Datacards_text_and_ROOT_files  && rm -rf  Datacards_text_and_ROOT_files || echo " Datacards_text_and_ROOT_files Not exist"   

#cp -r ../step4_run_limit_tool/Datacards_text_and_ROOT_files .

eval `scramv1 runtime -sh`

root -l -q -b Control_all_cut_limit_auto.C++\($N_cut_points\,$lowest_cut\,$scan_width\,\"$input_dir\"\,\"$path_to_save\"\)

