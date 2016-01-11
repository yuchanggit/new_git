#!/bin/bash

echo "run run_step2.sh "

test -e output && rm -r output || echo " output Not exist"
mkdir output

# in lxplus is okay
time ./globalRun_after_skim.sh eleVariable_after_skim true true true true true  




