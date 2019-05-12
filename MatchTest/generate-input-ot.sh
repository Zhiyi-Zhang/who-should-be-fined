#!/bin/bash

# 6 total node, single node leaker
Pattern6_single=(919999 999991)

# 6 total node, 3 node collusion
Pattern6_three=(911909+900919 911099 910199+901199)

OTs=(1-2 2-3 3-4)

TotalObjectNum=20000

#######################################DIFF OT############################
 # single leaker
for j in "${Pattern6_single[@]}"
do
    for k in "${OTs[@]}"
    do
        ./input-gen.py different-ot/${j}-${k}-0.9.txt 6 ${TotalObjectNum} ${j} 0.9 ${k}
    done
done
# collusion
for j in "${Pattern6_three[@]}"
do
    for k in "${OTs[@]}"
    do
        ./input-gen.py different-ot/${j}-${k}-0.9.txt 6 ${TotalObjectNum} ${j} 0.9 ${k}
    done
done
