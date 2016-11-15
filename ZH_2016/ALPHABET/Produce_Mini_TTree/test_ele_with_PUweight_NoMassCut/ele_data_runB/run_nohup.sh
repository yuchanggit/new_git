#!/bin/bash

# cmsenv
# voms-proxy-init --voms cms

test -e nohup.out  && rm -r nohup.out  || echo " nohup.out Not exist" 

nohup sh globalRun.sh & 

