#!/bin/bash

fileOne=cpu.log
fileTwo=mesen.log
numLines=${1:-"1"}

diff <(head -n ${numLines} ${fileOne}) <(head -n ${numLines} ${fileTwo})
