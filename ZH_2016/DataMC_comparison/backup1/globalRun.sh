#!/bin/sh

flag_MC=false
flag_DATA=false

# -- decide run MC or data here ---- 
#flag_MC=true
flag_DATA=true

# -- decide run electron or muon variable here ---- 
macro=eleZVariable

# ----------------------------------

pcncu_path=/data7/yuchang/NCUGlobalTuples_80X

function Macro(){

     # $1=macro, $2=sample_name, $3=save_name

     sample_path=$pcncu_path/$2
     root -q -b -l $1.C+\(\"$sample_path\"\,\"$3\"\)
}

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


if [ $flag_MC == true  ];then 

  # DY-Ht 

     sample_name=DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-100to200_13TeV
     Macro $macro $sample_name $save_name

     sample_name=DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-200to400_13TeV
     Macro $macro $sample_name $save_name

#     sample_name=DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
#     Macro $macro $pcncu_path $sample_name

     sample_name=DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
     save_name=DYJetsToLL_M-50_HT-600toInf_13TeV
     Macro $macro $sample_name $save_name

  # TT
     sample_name=TT_TuneCUETP8M1_13TeV-powheg-pythia8
     save_name=TT_TuneCUETP8M1_13TeV
     Macro $macro $sample_name $save_name
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


# mv ROOT file and end the code
rm -f inputdir.txt
rm -f *.pcm *.d *.so
mv *root output*

exit
# -------- end ----------

<<COMMENT

if [ -z $8 ]; then

    echo "Usage: $0 [macro without .C] [channel] [data] [DY] [diboson] [ttbar] [singletop] [signal]"
    exit 0

fi

channel=$2
data=$3
DY=$4
diboson=$5
ttbar=$6
singletop=$7
signal=$8

pwd=$PWD
cmsswdr=/afs/cern.ch/work/y/yuchang/13_TeV_Task/alpha_method_background_estimate/CMSSW_7_4_5/src
cd $cmsswdr
#export SCRAM_ARCH=slc6_amd64_gcc491
export SCRAM_ARCH=slc6_amd64_gcc530
eval `scramv1 runtime -sh`
cd $pwd

samplePath=/data7/yuchang/Henry_skim_2016_4_11_no_pileup_weight/$channel

if [ $data == true ]; then

    if [ $channel == ele ]; then

	root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_crab_SingleElectron-Run2015D-05Oct2015-v1_20151117_2p2fb_SingleEleTextFile.root\"\,\"SingleElectron-Run2015D-V120151117\"\)
	root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_crab_SingleElectron-Run2015D-PromptReco-V420151117_2p2fb_SingleEleTextFile.root\"\,\"SingleElectron-Run2015D-V420151117\"\)

    elif [ $channel == mu ]; then

	root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_crab_SingleMuon-Run2015D-05Oct2015-v1_20151119_2p2fb_SingleMuTextFile.root\"\,\"SingleMuon-Run2015D-V120151119\"\)             
	root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_crab_SingleMuon-Run2015D-PromptReco-V420151119_2p2fb_SingleMuTextFile.root\"\,\"SingleMuon-Run2015D-V420151119\"\)

    fi

else

    data=false

fi

if [ $DY == true ]; then

    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root\"\,\"DYJetsToLL_M-50_HT-100to200_13TeV\"\)
    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root\"\,\"DYJetsToLL_M-50_HT-200to400_13TeV\"\)
    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root\"\,\"DYJetsToLL_M-50_HT-400to600_13TeV\"\)
    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root\"\,\"DYJetsToLL_M-50_HT-600toInf_13TeV\"\)

else

    DY=false

fi

if [ $diboson == true ]; then

    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_WW_TuneCUETP8M1_13TeV-pythia8.root\"\,\"WW_TuneCUETP8M1_13TeV\"\)
    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_WZ_TuneCUETP8M1_13TeV-pythia8.root\"\,\"WZ_TuneCUETP8M1_13TeV\"\)
    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_ZZ_TuneCUETP8M1_13TeV-pythia8.root\"\,\"ZZ_TuneCUETP8M1_13TeV\"\)

else

    diboson=false

fi

if [ $ttbar == true ]; then

    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_TT_TuneCUETP8M1_13TeV-powheg-pythia8.root\"\,\"TT_TuneCUETP8M1_13TeV\"\)

else

    ttbar=false

fi

if [ $singletop == true ]; then

    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root\"\,\"ST_s_4f_leptonDecays_13TeV\"\)
    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root\"\,\"ST_t_antitop_4f_leptonDecays_13TeV\"\)
    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root\"\,\"ST_t_top_4f_leptonDecays_13TeV\"\)
    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root\"\,\"ST_tW_antitop_5f_inclusiveDecays_13TeV\"\)
    root -q -b -l $1.C+\(\"$samplePath/skim_${channel}_ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root\"\,\"ST_tW_top_5f_inclusiveDecays_13TeV\"\)

else

    singletop=false;

fi

if [ $signal == true ]; then

    mass=(600 800 1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500)

    for i in "${mass[@]}"
    do

	signalName=skim_${channel}_ZprimeToZhToZlephbb_narrow_M-${i}_13TeV-madgraph.root
	root -q -b -l $1.C+\(\"$samplePath/$signalName\"\,\"ZprimeToZhToZlephbb_M-${i}_13TeV\"\)

    done
   
else 

    signal=false

fi

rm -f inputdir.txt
rm -f *.pcm *.d *.so
mv *root output*

exit

COMMENT

