#!/bin/bash

Xarray=(0.01 0.015 0.02 0.025 0.03 0.04 0.05 0.1 0.5 0.8 1)

# 6 total node, 3 node collusion
Pattern6_three=(911909+901919 911099 910199+901199)

OTs=(1-2 2-3 3-4)

TotalObjectNum=20000

#######################################DIFF OT############################

for j in "${Pattern6_three[@]}"
do
    for k in "${OTs[@]}"
    do
        for i in "${Xarray[@]}"
        do
            ./input-gen.py different-ot/${j}-${k}-${i} 6 ${TotalObjectNum} ${j} ${i} ${k}
        done
    done
done