#/bin/bash

# purpose: list the sample path

# do voms first
# voms-proxy-init --voms cms
# voms-proxy-init -valid 168:00  # this is the long time version of voms

function List_path(){

  # $1=path_site
  # $2=path_middle
  # $3=dataset_name
  # $4=date_number
  # $5=folder
  # $6=output_name

  save_txt=$6_$5;   test -e $save_txt  && rm -r $save_txt  || echo " $save_txt  Not exist"
  echo " "; echo "writing $save_txt from $1/$2/$3/$4/$5 "

  #echo "gfal-ls $1/$2/$3/$4/$5 | grep ".root" > temp.txt "
  gfal-ls $1/$2/$3/$4/$5 | grep ".root" > temp.txt

  inputfile=temp.txt ; iteration=0 ; lastfile=`cat $inputfile | wc -l`
  echo "There are "$lastfile" root files"

  while [ $iteration -lt $lastfile ]; 
  do

    iteration=$(( iteration + 1 ))
    input=(`head -n $iteration $inputfile  | tail -1`)

    #echo "$iteration"
    echo $1/$2/$3/$4/$5/$input >> $save_txt

  done

  rm temp.txt
  echo "finish writing $save_txt"; echo " "

}


Taiwan_Tier2=root://se01.grid.nchc.org.tw//dpm/grid.nchc.org.tw
NCU_Tier3=root://grid71.phy.ncu.edu.tw//dpm/phy.ncu.edu.tw

# DY NLO inclusive sample

# root://se01.grid.nchc.org.tw//dpm/grid.nchc.org.tw/home/cms/store/user/yuchang/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/170616_133608/0001

path_site=$Taiwan_Tier2
path_middle=home/cms/store/user/yuchang   # processed by YuHsiang

output_name=DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8
dataset_name=$output_name/crab_$output_name
date_number=170616_133608
folder=0000
List_path $path_site $path_middle $dataset_name $date_number $folder $output_name

folder=0001
List_path $path_site $path_middle $dataset_name $date_number $folder $output_name


<< kk
# M800

path_site=$NCU_Tier3
path_middle=home/cms/store/user/yuchang   # processed by YuHsiang

output_name=ZprimeToZhToZlephbb_narrow_M-800_13TeV-madgraph
dataset_name=$output_name/crab_$output_name
date_number=170221_163653
List_path $path_site $path_middle $dataset_name $date_number $folder $output_name

kk


