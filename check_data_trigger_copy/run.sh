#!/bin/bash



  macro=xAna_trig
  outputFolder=output_ROOT

  # SingleElectron data
  sample_path=Sample_checkTrigger/SingleElectron_Run2016H/NCUGlobalTuples_1.root
  output_name=SingleElectron_Run2016H_NCUGlobalTuples_1
#  root -q -b -l $macro.C+\(\"$sample_path\"\,\"$outputFolder\"\,\"$output_name\"\)

  # SingleMuon data 
  sample_path=Sample_checkTrigger/SingleMuon_Run2016H/NCUGlobalTuples_1.root
  output_name=SingleMuon_Run2016H_NCUGlobalTuples_1
#  root -q -b -l $macro.C+\(\"$sample_path\"\,\"$outputFolder\"\,\"$output_name\"\)

  # signal sample (Z' at mass 1000 GeV)

  sample_path=Sample_checkTrigger/ZprimeToZhToZlephbb_narrow_M-1000/NCUGlobalTuples_1to5.root
  output_name=ZprimeToZhToZlephbb_narrow_M-1000_NCUGlobalTuples_1to5
  root -q -b -l $macro.C+\(\"$sample_path\"\,\"$outputFolder\"\,\"$output_name\"\)




  rm *.d *.so *.pcm
 





