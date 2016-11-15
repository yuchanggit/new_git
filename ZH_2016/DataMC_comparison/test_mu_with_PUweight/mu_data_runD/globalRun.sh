#!/bin/sh

echo "start"
date

# -- decide run electron or muon variable here ----

#channel=ele 
channel=mu

echo "channel=" $channel

# which sample you want to run? 1 for True and 0 for False 

flag_DATA_ele_runB=0
flag_DATA_ele_runC=0
flag_DATA_ele_runD=0

flag_DATA_mu_runB=0
flag_DATA_mu_runC=0
flag_DATA_mu_runD=1

flag_MC_DY_100=0
flag_MC_DY_200=0
flag_MC_DY_400=0
flag_MC_DY_600=0

flag_MC_TT=0

flag_MC_diboson=0

echo "which sample are used?"
echo "flag_DATA_ele_runB: $flag_DATA_ele_runB ,flag_DATA_ele_runC: $flag_DATA_ele_runC ,flag_DATA_ele_runD: $flag_DATA_ele_runD" 
echo "flag_DATA_mu_runB: $flag_DATA_mu_runB,flag_DATA_mu_runC: $flag_DATA_mu_runC,flag_DATA_mu_runD: $flag_DATA_mu_runD," 
echo "flag_MC_DY_100: $flag_MC_DY_100 , flag_MC_DY_200: $flag_MC_DY_200 , flag_MC_DY_400: $flag_MC_DY_400 , flag_MC_DY_600: $flag_MC_DY_600 , flag_MC_TT: $flag_MC_TT , flag_MC_diboson: $flag_MC_diboson "

# ----------------------------------

if [ $channel == ele  ];then
  macro=xAna_ele
  outputFolder=output_ele
fi

if [ $channel == mu  ];then
  macro=xAna_mu
  outputFolder=output_mu
fi


# ----------------------------------
pcncu_path=/data7/yuchang/NCUGlobalTuples_80X_20160821

# ----------------------------------



function Macro(){

     # $1=macro, $2=sample_name, $3=save_name

     sample_path=$pcncu_path/$2

     echo "root -q -b -l $1.C+\(\"$sample_path\"\,\"$outputFolder\"\,\"$3\"\) "
     root -q -b -l $1.C+\(\"$sample_path\"\,\"$outputFolder\"\,\"$3\"\)
}

# ----------------------------------

if [ $flag_DATA_ele_runB == 1  ];then
    # SingleElectron RunB
     sample_name=SingleElectron/crab_SingleElectron-Run2016B-PromptReco-v2
     save_name=SingleElectron-Run2016B-v2
     Macro $macro $sample_name $save_name
fi

if [ $flag_DATA_ele_runC == 1  ];then
    # SingleElectron RunC
     sample_name=SingleElectron/crab_SingleElectron-Run2016C-PromptReco-v2
     save_name=SingleElectron-Run2016C-v2
     Macro $macro $sample_name $save_name
fi

if [ $flag_DATA_ele_runD == 1  ];then
    # SingleElectron RunD
     sample_name=SingleElectron/crab_SingleElectron-Run2016D-PromptReco-v2
     save_name=SingleElectron-Run2016D-v2
     Macro $macro $sample_name $save_name
fi

if [ $flag_DATA_mu_runB == 1  ];then

     # SingleMuon RunB
     sample_name=SingleMuon/crab_SingleMuon-Run2016B-PromptReco-v2
     save_name=SingleMuon-Run2016B-v2
     Macro $macro $sample_name $save_name
fi

if [ $flag_DATA_mu_runC == 1  ];then

     # SingleMuon RunC
     sample_name=SingleMuon/crab_SingleMuon-Run2016C-PromptReco-v2
     save_name=SingleMuon-Run2016C-v2
     Macro $macro $sample_name $save_name
fi

if [ $flag_DATA_mu_runD == 1  ];then

     # SingleMuon RunD
     sample_name=SingleMuon/crab_SingleMuon-Run2016D-PromptReco-v2
     save_name=SingleMuon-Run2016D-v2
     Macro $macro $sample_name $save_name

fi

# ----------------------------------

if [ $flag_MC_DY_100 == 1  ];then 

     # DY-Ht_100to200 
     sample_name=DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-100to200_13TeV
     Macro $macro $sample_name $save_name
fi

if [ $flag_MC_DY_200 == 1  ];then
     # DY-Ht_200to400 
     sample_name=DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-200to400_13TeV
     Macro $macro $sample_name $save_name
fi

if [ $flag_MC_DY_400 == 1  ];then
     # DY-Ht_400to600 
     sample_name=DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-400to600_13TeV
     Macro $macro $sample_name $save_name
fi


if [ $flag_MC_DY_600 == 1  ];then
     # DY-Ht_600toInf 
     sample_name=DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-600toInf_13TeV
     Macro $macro $sample_name $save_name

fi

# ----------------------------------

if [ $flag_MC_TT == 1  ];then

     # TT
     sample_name=TT_TuneCUETP8M1_13TeV-powheg-pythia8
     save_name=TT_TuneCUETP8M1_13TeV
     Macro $macro $sample_name $save_name

fi

# ----------------------------------

if [ $flag_MC_diboson == 1  ];then

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

# delete temp file and end the code
rm -f inputdir.txt
rm -f *.pcm *.d *.so

echo "finish"
date

exit
# -------- end ----------

