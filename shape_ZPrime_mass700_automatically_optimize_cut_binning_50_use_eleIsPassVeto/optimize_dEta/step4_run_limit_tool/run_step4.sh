#!/bin/bash

echo "run run_step4.sh "

test -e Datacards_text_and_ROOT_files  && rm -rf  Datacards_text_and_ROOT_files || echo " Datacards_text_and_ROOT_files Not exist"   
test -e text_and_ROOT_files  && rm -rf text_and_ROOT_files || echo " text_and_ROOT_files Not exist"

cp -r ../step3_make_datacard/Datacards_text_and_ROOT_files .
cp -r ../step3_make_datacard/text_and_ROOT_files .

eval `scramv1 runtime -sh`

python RunLimitForOptimization.py Datacards_text_and_ROOT_files


