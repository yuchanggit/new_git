#!/bin/bash

echo "run run_step2.sh "

test -e plot && rm -r plot || echo " plot Not exist"
cp -r ../step1_save_histogram/plot .

test -e plot_1st_pt && rm -r plot_1st_pt || echo " plot_1st_pt Not exist"
mkdir plot_1st_pt

test -e plot_2nd_pt && rm -r plot_2nd_pt || echo " plot_2nd_pt Not exist"
mkdir plot_2nd_pt

test -e plot_dEta && rm -r plot_dEta || echo " plot_dEta Not exist"
mkdir plot_dEta

test -e plot_dRapidity && rm -r plot_dRapidity || echo " plot_dRapidity Not exist"
mkdir plot_dRapidity

#time root -l -q -b Significance_auto.C++ </dev/null >& test.log &
root -l -q -b Significance_auto.C++





