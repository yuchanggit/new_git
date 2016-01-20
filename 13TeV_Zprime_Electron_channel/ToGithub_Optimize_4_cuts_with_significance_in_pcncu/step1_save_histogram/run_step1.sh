#!/bin/bash

echo "run run_step1.sh "

test -e plot && rm -r plot || echo " plot Not exist"
mkdir plot

cd /afs/cern.ch/work/y/yuchang/13_TeV_Task/limit_setting_test/CMSSW_7_1_5/src/
cmsenv
cd -

time root -l -q -b Control_auto.C++





