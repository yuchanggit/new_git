#!/bin/bash

echo "run run_step5.sh "

test -e Datacards_text_and_ROOT_files  && rm -rf  Datacards_text_and_ROOT_files || echo " Datacards_text_and_ROOT_files Not exist"   

cp -r ../step4_run_limit_tool/Datacards_text_and_ROOT_files .

eval `scramv1 runtime -sh`

root -l -q -b Control_all_cut_limit_auto.C++

