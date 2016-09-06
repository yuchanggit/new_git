#!/bin/bash

test -e nohup.out  && rm -r nohup.out  || echo " nohup.out Not exist" 

nohup sh run_step1.sh &  

