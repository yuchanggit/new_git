#!/bin/sh

# do 
# cmsenv
# voms-proxy-init --voms cms
# first



# 0000
dir_number=0000



#lcg-ls -l srm://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/SingleElectron/crab_SingleElectron-Run2016B-PromptReco-v2/160706_120820/$dir_number > file_list_$dir_number.txt

lcg-ls -l srm://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1/160706_094223/$dir_number > file_list_$dir_number.txt

cat file_list_$dir_number.txt | grep 'root' | cut -d '/' -f 14 > file_list_name_$dir_number.txt



