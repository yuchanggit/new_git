#!/bin/bash

function reOrder(){ 

  inputFile=$1
  outputFile=path_ReOrganize/$1

  ./re_Order_Path.sh $inputFile $outputFile

}

reOrder DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8

