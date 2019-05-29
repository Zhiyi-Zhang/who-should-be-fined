#!/bin/bash

Xarray=(0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1 0.15 0.2 0.25 0.3 0.4 0.5 0.8 1)
ReceiverNum=(3 6 9)
Pattern=911909+901919
TotalObjectNum=20000

rm -rf collusion
mkdir collusion
for i in "${Xarray[@]}"
do
  ./input-gen.py collusion/3-${i}.txt 3 ${TotalObjectNum} 111 ${i}
  ./input-gen.py collusion/6-${i}.txt 6 ${TotalObjectNum} 991119 ${i}
  ./input-gen.py collusion/9-${i}.txt 9 ${TotalObjectNum} 999111999 ${i}
done