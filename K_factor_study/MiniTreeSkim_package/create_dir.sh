#!/bin/bash

# this script is used to create directory for each dataset

# please do these first
# (1) .L skimTree.C++ in ROOT
# (2) export X509_USER_PROXY=$HOME/private/grid.proxy, voms-proxy-init --voms cms

function create(){
 
  inputFile=$1
  echo "inputFile is $inputFile"

  new_dir=skimmedFile_$inputFile
  mkdir $new_dir

  cp sample_path/path_ReOrganize/$inputFile $new_dir
  cp launch_ntuple.sh runNtuple.sh skimTree* run.C $new_dir
  cp untuplizer.h $new_dir

  cd $new_dir 

  # send jobs to batch by nohup
#  nohup sh ./launch_ntuple.sh $inputFile &

  cd $current

}

current=$PWD

# create directory

#create DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8 

#create DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
#create DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
#create DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

create DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
create DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
create DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
create DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

