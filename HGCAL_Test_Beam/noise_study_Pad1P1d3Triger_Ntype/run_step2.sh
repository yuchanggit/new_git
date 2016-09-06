#!/bin/sh

echo "start"
date

# SiPad1 trigger
root -l -b -q  step2_plot.C+\(\"Pad1Tri_Ele100um_100GeV_600HV.root\"\)
root -l -b -q  step2_plot.C+\(\"Pad1Tri_Ele100um_150GeV_800HV.root\"\)

root -l -b -q  step2_plot.C+\(\"Pad1Tri_Ele200um_100GeV_600HV.root\"\)
root -l -b -q  step2_plot.C+\(\"Pad1Tri_Ele200um_150GeV_800HV.root\"\)

root -l -b -q  step2_plot.C+\(\"Pad1Tri_Ele300um_100GeV_600HV.root\"\)
root -l -b -q  step2_plot.C+\(\"Pad1Tri_Ele300um_150GeV_800HV.root\"\)


# SiPad3 trigger
root -l -b -q  step2_plot.C+\(\"Pad3Tri_Ele100um_150GeV_800HV.root\"\)
root -l -b -q  step2_plot.C+\(\"Pad3Tri_Ele200um_150GeV_800HV.root\"\)
root -l -b -q  step2_plot.C+\(\"Pad3Tri_Ele300um_150GeV_800HV.root\"\)

rm *.d *.so

echo "finish"
date
