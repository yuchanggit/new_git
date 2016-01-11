#!/bin/bash

echo "run run_step2_to_step3.sh "


# in lxplus is okay

cd step2_save_histogram
./run_step2.sh
cd ..

cd step3_plot
./run_step3.sh
cd ..

