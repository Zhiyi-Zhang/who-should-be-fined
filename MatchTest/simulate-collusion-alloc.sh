#!/bin/bash


Xarray=(0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1 0.15 0.2 0.25 0.3 0.4 0.5 0.8 1)
Alloc=(0 100 300 500 1000)
# 6 total node, 3 node collusion
Pattern6_three=(911909+901919 911099 910199+901199)
TotalObjectNum=20000

for j in "${Pattern6_three[@]}"
do
    for k in "${Alloc[@]}"
    do
        for i in "${Xarray[@]}"
        do
            ./input-gen-alloc.py collusion-alloc/${j}-${k}-${i}.txt 6 ${TotalObjectNum} ${j} ${i} ${k}
        done
    done
done