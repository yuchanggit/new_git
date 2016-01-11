#!/bin/bash

echo "run run_step1.sh "

test -e output && rm -r output || echo " output Not exist"
mkdir output

# in pcncu
time ./globalRun.sh eleVariable true true true true true  




