#!/bin/sh

if [ -z $1 ]; then
    echo "Usage: $0 [bool electron] [bool muon]"
    exit 0
fi

electron=$1
muon=$2

pwd=$PWD
#cmsswdr=/afs/cern.ch/work/h/htong/CMSSW_7_1_5/src
cmsswdr=/afs/cern.ch/work/y/yuchang/13_TeV_Task/alpha_method_background_estimate/CMSSW_7_4_5/src
cd $cmsswdr
#export SCRAM_ARCH=slc6_amd64_gcc481
export SCRAM_ARCH=slc6_amd64_gcc491
eval `scramv1 runtime -sh`
cd $pwd

if [ $electron == true ]; then

#    root -q -b -l dataMCplots.C+\(\"electron/dataMC_Ele/outputEle/barrel\"\,\"barrelEleVariables\"\)
#    root -q -b -l dataMCplots.C+\(\"electron/dataMC_Ele/outputEle/endcap\"\,\"endcapEleVariables\"\)
#    root -q -b -l dataMCplots.C+\(\"electron/dataMC_Zee/outputZee\"\,\"ZeeVariables\"\)
#    root -q -b -l dataMCplots.C+\(\"electron/dataMC_Jetee/outputJetee\"\,\"JeteeVariables\"\)

    root -q -b -l dataMCplots.C+\(\"Zee_output\"\,\"ZeeVariables\"\)

else

    electron=false

fi

if [ $muon == true ]; then

    root -q -b -l dataMCplots.C+\(\"muon/dataMC_Mu/outputMu/highpt\"\,\"highPtMuVariables\"\)
    root -q -b -l dataMCplots.C+\(\"muon/dataMC_Mu/outputMu/tracker\"\,\"trackerMuVariables\"\)
    root -q -b -l dataMCplots.C+\(\"muon/dataMC_Zmumu/outputZmumu\"\,\"ZmumuVariables\"\)
    root -q -b -l dataMCplots.C+\(\"muon/dataMC_Jetmumu/outputJetmumu\"\,\"JetmumuVariables\"\)

    root -q -b -l dataMCplots.C+\(\"muon/dataMC_ZHmu/outputmZHmu\"\,\"mZHmuVariables\"\)

else

    muon=false

fi

rm -f *.pcm *.d *.so
#mv *pdf /afs/cern.ch/user/h/htong/www
mv *pdf /afs/cern.ch/user/y/yuchang/www/MC_Data_comparison_Henry_code_2016_4_7

exit
