#!/bin/sh

pcncu_path=/data7/yuchang/NCUGlobalTuples_80X

# define flag 
flag_DATA=false

flag_MC_DY=false
flag_MC_TT=false
flag_MC_diboson=false

# -- decide run MC or data here ---- 

#flag_DATA=true

flag_MC_DY=true
#flag_MC_TT=true
#flag_MC_diboson=true


# -- decide run electron or muon variable here ---- 
macro=eleZVariable

# ----------------------------------



function Macro(){

     # $1=macro, $2=sample_name, $3=save_name

     sample_path=$pcncu_path/$2

     echo "root -q -b -l $1.C+\(\"$sample_path\"\,\"$3\"\) "
     root -q -b -l $1.C+\(\"$sample_path\"\,\"$3\"\)
}

# ----------------------------------

if [ $flag_DATA == true  ];then

    # SingleElectron

     sample_name=SingleElectron
     sample_path=$pcncu_path/$sample_name
     save_name=SingleElectron-Run2016B-v2
     root -q -b -l $macro.C+\(\"$sample_path\"\,\"$save_name\"\)

      # SingleMuon

#     sample_name=SingleMuon
#     sample_path=$pcncu_path/data_mu_temp/$sample_name
#     root -q -b -l $macro.C+\(\"$sample_path\"\,\"$sample_name\"\)

fi

# ----------------------------------

if [ $flag_MC_DY == true  ];then 

     # DY-Ht_100to200 
     sample_name=DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-100to200_13TeV
#     Macro $macro $sample_name $save_name

     # DY-Ht_200to400 
     sample_name=DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-200to400_13TeV
#     Macro $macro $sample_name $save_name

     # DY-Ht_400to600 
     sample_name=DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-400to600_13TeV
#     Macro $macro $sample_name $save_name

     # DY-Ht_600toInf 
     sample_name=DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-600toInf_13TeV
     Macro $macro $sample_name $save_name

fi

# ----------------------------------

if [ $flag_MC_TT == true  ];then

     # TT
     sample_name=TT_TuneCUETP8M1_13TeV-powheg-pythia8
     save_name=TT_TuneCUETP8M1_13TeV
     Macro $macro $sample_name $save_name

fi

# ----------------------------------

if [ $flag_MC_diboson == true  ];then

     # ZH
     sample_name=ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8
     save_name=ZH_HToBB_ZToLL_M125_13TeV_amcatnlo
     Macro $macro $sample_name $save_name

     sample_name=ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8
     save_name=ZH_HToBB_ZToLL_M125_13TeV_powheg
     Macro $macro $sample_name $save_name

     # WW
     sample_name=WW_TuneCUETP8M1_13TeV-pythia8
     save_name=WW_TuneCUETP8M1_13TeV
     Macro $macro $sample_name $save_name

     # WZ
     sample_name=WZ_TuneCUETP8M1_13TeV-pythia8
     save_name=WZ_TuneCUETP8M1_13TeV
     Macro $macro $sample_name $save_name

     # ZZ
     sample_name=ZZ_TuneCUETP8M1_13TeV-pythia8
     save_name=ZZ_TuneCUETP8M1_13TeV
     Macro $macro $sample_name $save_name

fi

# ----------------------------------

# mv ROOT file and end the code
rm -f inputdir.txt
rm -f *.pcm *.d *.so
mv *root output*

exit
# -------- end ----------

