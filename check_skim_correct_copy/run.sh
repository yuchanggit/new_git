#!/bin/bash

  sample_path=ntuple_EleData/NCUGlobalTuples_1.root

  # use usual code for selection
  echo " "; echo "use xAna_skim_Ele.C"

  macro=xAna_skim_Ele
  root -q -b -l $macro.C+\(\"$sample_path\"\)

  rm *.d *.so *.pcm


  # use CopyTree to skim the TTree 
  echo " "; echo "use skimTree_Ele.C"

  macro=skimTree_Ele
  root -q -b -l $macro.C+\(\"$sample_path\"\)

  rm *.d *.so *.pcm 

