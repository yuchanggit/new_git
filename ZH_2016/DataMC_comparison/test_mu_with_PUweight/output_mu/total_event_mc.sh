#!/bin/sh


function Macro(){

root -l $1 <<EOF
totalEvents->Integral()
.q
EOF

}

file=DYJetsToLL_M-50_HT-100to200_13TeV.root
Macro $file

file=DYJetsToLL_M-50_HT-200to400_13TeV.root
Macro $file

file=DYJetsToLL_M-50_HT-400to600_13TeV.root
Macro $file

file=DYJetsToLL_M-50_HT-600toInf_13TeV.root
Macro $file

file=TT_TuneCUETP8M1_13TeV.root
Macro $file

file=ZZ_TuneCUETP8M1_13TeV.root
Macro $file

file=WZ_TuneCUETP8M1_13TeV.root
Macro $file

file=WW_TuneCUETP8M1_13TeV.root
Macro $file

file=ZH_HToBB_ZToLL_M125_13TeV_amcatnlo.root
Macro $file

file=ZH_HToBB_ZToLL_M125_13TeV_powheg.root
Macro $file









