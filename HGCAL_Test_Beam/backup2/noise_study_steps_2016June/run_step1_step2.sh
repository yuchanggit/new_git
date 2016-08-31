#!/bin/sh

echo "execute run_step1_step2.sh"

# version of the used recoTrees

#v_recoTree=recoTrees_v2  
#v_recoTree=recoTrees_vSlope0
#v_recoTree=recoTrees_vSlope0_in5_145
#v_recoTree=recoTrees_vSlope_in5_145


# event to load in ntuples 
max_event=5000
#max_event=20000
#max_event=-1 # full statistics


echo "v_recoTree:" $v_recoTree
echo "max_event:" $max_event

v_recoTree=recoTrees_v2
root -l -b -q step1_analyzer_MakeHisto.C+\(\"$v_recoTree\"\,$max_event\) 
root -l -b -q step2_plot.C+\(\"$v_recoTree\"\)

v_recoTree=recoTrees_vSlope0
root -l -b -q step1_analyzer_MakeHisto.C+\(\"$v_recoTree\"\,$max_event\) 
root -l -b -q step2_plot.C+\(\"$v_recoTree\"\)

v_recoTree=recoTrees_vSlope0_in5_145
root -l -b -q step1_analyzer_MakeHisto.C+\(\"$v_recoTree\"\,$max_event\) 
root -l -b -q step2_plot.C+\(\"$v_recoTree\"\)

v_recoTree=recoTrees_vSlope_in5_145
root -l -b -q step1_analyzer_MakeHisto.C+\(\"$v_recoTree\"\,$max_event\) 
root -l -b -q step2_plot.C+\(\"$v_recoTree\"\)




