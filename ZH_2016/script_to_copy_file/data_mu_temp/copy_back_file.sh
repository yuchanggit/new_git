#!/bin/bash

# purpose: copy file from NCU_T3 to pcncu14

# setup:
#
# ssh pcncu14
# cd /afs/cern.ch/work/y/yuchang/produce_samples/CMSSW_8_0_8/src
# export SCRAM_ARCH=slc6_amd64_gcc530; eval `scramv1 runtime -sh`
# cmsenv
# cd /data7/yuchang/NCUGlobalTuples_80X 
# voms-proxy-init --voms cms



# create directory (mkdir -p  doesn't affect if the directory already exist) 
# copy back the file

current_dir=/data7/yuchang/NCUGlobalTuples_80X
#date_dir=160706_094151
NCU_T3_path=grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang

dir_path=DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
sub_dir=crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1


#   xrdcp -r root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw/home/cms/store/user/yuchang/


# DY HT 100-200
dir_name_DY_HT_100to200=DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
sub_dir_name_DY_HT_100to200_1=crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1
date_dir=160706_094151
#mkdir -p $dir_name_DY_HT_100to200/$sub_dir_name_DY_HT_100to200_1/$date_dir

sub_dir_name_DY_HT_100to200_2=crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1
#mkdir -p $dir_name_DY_HT_100to200/$sub_dir_name_DY_HT_100to200_2/$date_dir


       # I am forced to type rather than use variable because it's unstable
#xrdcp -r root://$NCU_T3_path/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1/160706_094204 $current_dir/$dir_name_DY_HT_100to200/$sub_dir_name_DY_HT_100to200_1/$date_dir

#xrdcp -r root://$NCU_T3_path/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1/160706_094204 $current_dir/$dir_name_DY_HT_100to200/$sub_dir_name_DY_HT_100to200_2/$date_dir
#xrdcp -r root://$NCU_T3_path/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1/160706_094204 .


# DY HT 200-400
dir_name_DY_HT_200to400=DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
sub_dir_name_DY_HT_200to400_1=crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1
sub_dir_name_DY_HT_200to400_2=crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1

date_dir=160706_094151
later_dir=$dir_name_DY_HT_200to400/$sub_dir_name_DY_HT_200to400_1/$date_dir
#mkdir -p $later_dir
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir 
#echo "xrdcp -r root://$NCU_T3_path/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1/160706_094151 $later_dir"
#xrdcp -r root://$NCU_T3_path/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1/160706_094151 $later_dir 

date_dir=160706_094223
later_dir=$dir_name_DY_HT_200to400/$sub_dir_name_DY_HT_200to400_2/$date_dir
#mkdir -p $later_dir
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir 




# DY HT 400-600, ignore now
dir_name_DY_HT_400to600=DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
sub_dir_name_DY_HT_400to600_1=crab_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

#mkdir -p $dir_name_DY_HT_400to600/$sub_dir_name_DY_HT_400to600_1/$date_dir

# DY HT 600-Inf
dir_name_DY_HT_600toInf=DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
sub_dir_name_DY_HT_600toInf_1=crab_DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1
sub_dir_name_DY_HT_600toInf_2=crab_DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1


date_dir=160706_094239
later_dir=$dir_name_DY_HT_600toInf/$sub_dir_name_DY_HT_600toInf_1/$date_dir
#mkdir -p $later_dir
#echo "xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir"
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir 


date_dir=160706_094247
later_dir=$dir_name_DY_HT_600toInf/$sub_dir_name_DY_HT_600toInf_2/$date_dir
#mkdir -p $later_dir
#echo "xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir"
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir 


# ZH

dir_name_ZH_1=ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8
sub_dir_name_ZH_1=crab_ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8

date_dir=160706_094950
later_dir=$dir_name_ZH_1/$sub_dir_name_ZH_1/$date_dir
#mkdir -p $later_dir
#echo "xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir"
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir


dir_name_ZH_2=ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8
sub_dir_name_ZH_2=crab_ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8

date_dir=160706_095000
later_dir=$dir_name_ZH_2/$sub_dir_name_ZH_2/$date_dir
#mkdir -p $later_dir
#echo "xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir"
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir

# ZZ
dir_name_ZZ=ZZ_TuneCUETP8M1_13TeV-pythia8
sub_dir_name_ZZ=crab_ZZ_TuneCUETP8M1_13TeV-pythia8

date_dir=160706_094942
later_dir=$dir_name_ZZ/$sub_dir_name_ZZ/$date_dir
#mkdir -p $later_dir
#echo "xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir"
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir

# WZ
dir_name_WZ=WZ_TuneCUETP8M1_13TeV-pythia8
sub_dir_name_WZ=crab_WZ_TuneCUETP8M1_13TeV-pythia8

date_dir=160706_094934
later_dir=$dir_name_WZ/$sub_dir_name_WZ/$date_dir
#mkdir -p $later_dir
#echo "xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir"
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir

# WW
dir_name_WW=WW_TuneCUETP8M1_13TeV-pythia8
sub_dir_name_WW=crab_WW_TuneCUETP8M1_13TeV-pythia8

date_dir=160706_094926
later_dir=$dir_name_WW/$sub_dir_name_WW/$date_dir
#mkdir -p $later_dir
#echo "xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir"
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir

# TT
dir_name_TT=TT_TuneCUETP8M1_13TeV-powheg-pythia8
sub_dir_name_TT=crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8

date_dir=160705_165659
later_dir=$dir_name_TT/$sub_dir_name_TT/$date_dir
#mkdir -p $later_dir
#echo "xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir"
#xrdcp -r root://$NCU_T3_path/$later_dir $current_dir/$later_dir


# data SingleElectron
dir_name_SingleElectron=SingleElectron
sub_dir_name_SingleElectron=crab_SingleElectron-Run2016B-PromptReco-v2

date_dir=160706_120820
later_dir=$dir_name_SingleElectron/$sub_dir_name_SingleElectron/$date_dir
#mkdir -p $later_dir
#echo "xrdcp -r root://$NCU_T3_path/$later_dir $later_dir"
#xrdcp -r root://$NCU_T3_path/$later_dir $later_dir

# data SingleMuon
dir_name_SingleMuon=SingleMuon
sub_dir_name_SingleMuon=crab_SingleMuon-Run2016B-PromptReco-v2

date_dir=160706_120755
later_dir=$dir_name_SingleMuon/$sub_dir_name_SingleMuon/$date_dir
mkdir -p $later_dir
echo "xrdcp -r root://$NCU_T3_path/$later_dir $later_dir"
xrdcp -r root://$NCU_T3_path/$later_dir $later_dir



#DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  
#DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  
#DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  
#DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8  

#ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8
#ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8
#ZZ_TuneCUETP8M1_13TeV-pythia8
#WZ_TuneCUETP8M1_13TeV-pythia8
#WW_TuneCUETP8M1_13TeV-pythia8
#TT_TuneCUETP8M1_13TeV-powheg-pythia8

#SingleElectron
#SingleMuon

# sub-directory name

     #crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1
     #crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1

     #crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1
     #crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1

     #crab_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

     #crab_DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0-v1
     #crab_DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_miniAODv2_v0_ext1-v1

     #crab_ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8



