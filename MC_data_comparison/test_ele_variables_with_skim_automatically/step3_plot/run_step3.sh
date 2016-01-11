#!/bin/bash

echo "run run_step3.sh "

test -e outputEle && rm -r outputEle || echo " outputEle Not exist"
cp -r ../step2_save_histogram/output outputEle

cd outputEle

mkdir barrel
mv *barrel.root barrel/

mkdir endcap
mv *endcap.root endcap/

cd ../

# in lxplus is okay
time ./globalPlot.sh true false 




