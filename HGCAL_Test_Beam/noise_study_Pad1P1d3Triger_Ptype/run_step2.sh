#!/bin/sh

echo "start"
date

# SiPad1 trigger
root -l -b -q  step2_plot.C+\(\"Pad1Tri_Ele120um.root\"\)
root -l -b -q  step2_plot.C+\(\"Pad1Tri_Ele200um.root\"\)
root -l -b -q  step2_plot.C+\(\"Pad1Tri_Ele320um.root\"\)


# SiPad3 trigger
root -l -b -q  step2_plot.C+\(\"Pad3Tri_Ele120um.root\"\)
root -l -b -q  step2_plot.C+\(\"Pad3Tri_Ele200um.root\"\)
root -l -b -q  step2_plot.C+\(\"Pad3Tri_Ele320um.root\"\)


rm *.d *.so

echo "finish"
date
