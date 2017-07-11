#!/bin/bash

scriptname=`basename $0`
EXPECTED_ARGS=2
if [ $# -ne $EXPECTED_ARGS ]
then
    echo "Usage: $scriptname inputPathFile outputFile"
    echo "Example: ./$scriptname TT_TuneCUETP8M2T4_13TeV-powheg-pythia8 path_ReOrganize/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"
    exit 1
fi

  # please provide the inputPathFile 
  # $1=inputFile
  # $2=outputFile

  # delete already existing txt

  save_txt=$2
  test -e $save_txt  && rm -r $save_txt  || echo " $save_txt  Not exist"

  save_txt=temp2.txt
  test -e $save_txt  && rm -r $save_txt  || echo " $save_txt  Not exist"

  # save path and number in temp2.txt
  inputfile=$1

  iteration=0
  lastfile=`cat $inputfile | wc -l`

  echo "the input file is: $inputfile, which has $lastfile files, starts in loop"

  while [ $iteration -lt $lastfile ]; 
  do
    iteration=$(( iteration + 1 ))
    string=`head -n $iteration $inputfile  | tail -1`
    number=`echo $string | cut -d '/' -f 16 | cut -d '_' -f 2 | cut -d '.' -f 1`  
    echo $string $number >> temp2.txt
  done

  # sort the temp2.txt and save in temp3.txt
  echo "finish loop, start sorting"
  cat temp2.txt | sort -t ' ' -k 2 -n > temp3.txt

  # take the path only from temp3.txt to save in temp_reOrder.txt
  echo "save path after sorting"
  cat temp3.txt | cut -d ' ' -f 1 > $2

  # remove temp file
  rm temp2.txt temp3.txt
  
  echo "done"; echo " "






