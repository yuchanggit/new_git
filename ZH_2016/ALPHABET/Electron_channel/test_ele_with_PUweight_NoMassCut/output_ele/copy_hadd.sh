#!/bin/bash

# do cmsenv first

cp ../ele_data_runB/output_ele/SingleElectron-Run2016B-v2.root .
cp ../ele_data_runC/output_ele/SingleElectron-Run2016C-v2.root .
cp ../ele_data_runD/output_ele/SingleElectron-Run2016D-v2.root .

hadd SingleElectron-combine.root SingleElectron-Run2016B-v2.root SingleElectron-Run2016C-v2.root SingleElectron-Run2016D-v2.root


