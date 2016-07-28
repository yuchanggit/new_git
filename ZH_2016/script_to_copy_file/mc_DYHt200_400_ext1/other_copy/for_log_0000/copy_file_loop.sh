#!/bin/bash

# cmsenv
# voms-proxy-init --voms cms

save_path=/data7/yuchang/NCUGlobalTuples_80X/mc_DYHt200_400_ext1/other_copy

dir_number=0000

file=../file_not_saved.txt

number1=`cat $file | wc -l`
echo $number1

loop_max=33

#for (( i=1; i<=${number1}; i=i+1 ))
for (( i=1; i<=$loop_max; i=i+1 ))
do

   echo "process $i/$loop_max"

   string1=`head -$i $file | tail -1`
   echo $string1


echo "xrdcp -r root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1/160706_094223/$dir_number/$string1 $save_path/$dir_number/"

xrdcp -r root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1/160706_094223/$dir_number/$string1 $save_path/$dir_number/


done

echo "finish"




