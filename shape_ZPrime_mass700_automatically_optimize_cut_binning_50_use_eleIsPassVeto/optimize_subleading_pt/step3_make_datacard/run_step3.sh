#!/bin/bash

echo "run run_step3.sh "

#test -e text_and_ROOT_files && echo "exist" || echo "Not exist"

test -e text_and_ROOT_files           && rm -r text_and_ROOT_files || echo " text_and_ROOT_files Not exist"
test -e Datacards_text_and_ROOT_files && rm -r Datacards_text_and_ROOT_files || echo " Datacards_text_and_ROOT_files Not exist"
test -e DataCard_MXXXGeV.txt          && rm -r DataCard_MXXXGeV.txt || echo " DataCard_MXXXGeV.txt Not exist"

cp -r ../step2_produce_TxtFile_and_ShapeROOT_for_each_cut_points/text_and_ROOT_files .

python MakeDataCardsForOptimization.py text_and_ROOT_files

