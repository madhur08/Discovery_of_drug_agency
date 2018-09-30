#!/bin/bash

if [ -e "./bin/code" ]; then
    ./bin/code $1 2
else
    echo "First run compile.sh to compile the code"
fi