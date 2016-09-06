#!/bin/sh

echo "start"
date

#max_event_to_read=100
max_event_to_read=-1  # full statistics

# SiPad1 trigger
root -l -q -b step1_analyzer_MakeHisto.C+\(\"/SiPad1Trigger/recoTrees_vSlope0_in5_145_fit100Ele/\"\,$max_event_to_read\)
root -l -q -b step1_analyzer_MakeHisto.C+\(\"/SiPad1Trigger/recoTrees_vSlope0_in5_145_fit200Ele/\"\,$max_event_to_read\)
root -l -q -b step1_analyzer_MakeHisto.C+\(\"/SiPad1Trigger/recoTrees_vSlope0_in5_145_fit300Ele/\"\,$max_event_to_read\)

# SiPad3 trigger
root -l -q -b step1_analyzer_MakeHisto.C+\(\"/SiPad3Trigger/recoTrees_vSlope0_in5_145_fit100Ele/\"\,$max_event_to_read\)
root -l -q -b step1_analyzer_MakeHisto.C+\(\"/SiPad3Trigger/recoTrees_vSlope0_in5_145_fit200Ele/\"\,$max_event_to_read\)
root -l -q -b step1_analyzer_MakeHisto.C+\(\"/SiPad3Trigger/recoTrees_vSlope0_in5_145_fit300Ele/\"\,$max_event_to_read\)

rm *.d *.so

echo "finish"
date
