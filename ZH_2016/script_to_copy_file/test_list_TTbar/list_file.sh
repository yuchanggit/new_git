#!/bin/sh

# do 
# cmsenv
# voms-proxy-init --voms cms
# first



# 0000
dir_number=0000

lcg-ls -l srm://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8/160705_165659/$dir_number > file_list_$dir_number.txt

cat file_list_$dir_number.txt | grep 'root' | cut -d '/' -f 14 > file_list_name_$dir_number.txt

# 0001

dir_number=0001

lcg-ls -l srm://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8/160705_165659/$dir_number > file_list_$dir_number.txt

cat file_list_$dir_number.txt | grep 'root' | cut -d '/' -f 14 > file_list_name_$dir_number.txt

# 0002

dir_number=0002

lcg-ls -l srm://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8/160705_165659/$dir_number > file_list_$dir_number.txt

cat file_list_$dir_number.txt | grep 'root' | cut -d '/' -f 14 > file_list_name_$dir_number.txt


