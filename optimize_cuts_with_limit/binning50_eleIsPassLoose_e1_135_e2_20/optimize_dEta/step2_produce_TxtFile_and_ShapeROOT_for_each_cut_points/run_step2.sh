#!/bin/bash

echo "run run_step2.sh "

test -e text_and_ROOT_files && rm -r text_and_ROOT_files || echo " text_and_ROOT_files Not exist"
mkdir text_and_ROOT_files

#cmsenv
eval `scramv1 runtime -sh`

root -l -q -b produce_txt_ROOT_for_cuts.C++

#root -l -q -b plot_mass.C++

