#!/bin/sh

# do 
# cmsenv
# voms-proxy-init --voms cms
# first



# 0000
dir_number=0000

lcg-ls -l srm://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/SingleElectron/crab_SingleElectron-Run2016B-PromptReco-v2/160706_120820/$dir_number > file_list_$dir_number.txt

cat file_list_$dir_number.txt | grep 'root' | cut -d '/' -f 14 > file_list_name_$dir_number.txt

# 0001

dir_number=0001

lcg-ls -l srm://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/SingleElectron/crab_SingleElectron-Run2016B-PromptReco-v2/160706_120820/$dir_number > file_list_$dir_number.txt

cat file_list_$dir_number.txt | grep 'root' | cut -d '/' -f 14 > file_list_name_$dir_number.txt

# 0002

dir_number=0002

lcg-ls -l srm://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/SingleElectron/crab_SingleElectron-Run2016B-PromptReco-v2/160706_120820/$dir_number > file_list_$dir_number.txt

cat file_list_$dir_number.txt | grep 'root' | cut -d '/' -f 14 > file_list_name_$dir_number.txt


