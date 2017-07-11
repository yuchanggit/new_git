#!/bin/bash

# this script is used to work something in all samples' directory


function create(){
 
  inputFile=$1
  echo "inputFile is $inputFile"

  new_dir=skimmedFile_$inputFile
  cd $new_dir

  # cleanning
#  echo "rm -r LSFJOB_*"  
#  rm -r LSFJOB_*
#  echo "rm skimmed_NCUGlobalTuples_*.root"
#  rm skimmed_NCUGlobalTuples_*.root
#  echo "done"

  # move skimTree.C and ROOT .L skimTree.C++
#  echo "rm *.so *.d *.pcm"
#  rm *.so *.d *.pcm
#  echo "cp ../skimTree.C ." 
#  cp ../skimTree.C .
#  echo "root .L skimTree.C++"
#  root -l -b <<KKK
#.L skimTree.C++
#.q
#KKK
#  echo "done"

  # ./launch_ntuple.sh DY...
#  ./launch_ntuple.sh $inputFile 

  # hadd and mv out
  echo "hadd $new_dir.root skimmed_NCUGlobalTuples_*.root"
  hadd $new_dir.root skimmed_NCUGlobalTuples_*.root   
  echo "mv $new_dir.root ../"
  mv $new_dir.root ../
  echo "done"


  cd $current

}

current=$PWD

# go and work in each directory

create DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8 

create DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
create DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
create DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

create DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
create DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
create DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
create DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

