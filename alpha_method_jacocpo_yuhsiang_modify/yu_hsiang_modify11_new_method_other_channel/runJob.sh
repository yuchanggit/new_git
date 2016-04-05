#!/bin/bash

cd /afs/cern.ch/work/y/yuchang/13_TeV_Task/alpha_method_background_estimate/CMSSW_7_4_5/src/
eval `scramv1 runtime -sh`

cd yu_hsiang_modify11_new_method_other_channel

python alpha_Yu_new_bias_study.py -b -c XZhnnb




