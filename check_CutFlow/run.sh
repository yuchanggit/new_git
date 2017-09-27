#!/bin/bash




  outputFolder=output_ROOT

  # signal sample (Z' at mass 1000 GeV)
  sample_path=../check_data_trigger/Sample_checkTrigger/ZprimeToZhToZlephbb_narrow_M-1000/NCUGlobalTuples_1to8.root



#  macro=xAna_CutFlow_Mu
  macro=xAna_CutFlow_Ele

#  output_name=ZprimeToZhToZlephbb_narrow_M-1000_NCUGlobalTuples_1to8_DiMuonChannel
  output_name=ZprimeToZhToZlephbb_narrow_M-1000_NCUGlobalTuples_1to8_DiElectronChannel

  root -q -b -l $macro.C+\(\"$sample_path\"\,\"$outputFolder\"\,\"$output_name\"\)

  root -l plot.C+\(\"$outputFolder\"\,\"$output_name\"\)

  rm *.d *.so *.pcm
 





