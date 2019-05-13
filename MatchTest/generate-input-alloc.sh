#!/bin/bash

# 6 total node, 2 node collusion
Pattern6_two=(911999+901999 991199 999119)
# 6 total node, 3 node collusion
Pattern6_three=(911909+901919 911099 910199+901199)
# 6 total node, 6 node collusion
Pattern6_six=(111000+100111 111111 111001)

Alloc=(0 100 300 500 1000 2000)
TotalObjectNum=20000

for j in "${Pattern6_two[@]}"
do
    for k in "${Alloc[@]}"
    do
        ./input-gen-alloc.py different-alloc/${j}-${k}.txt 6 ${TotalObjectNum} ${j} 0.1 ${k}
    done
done

for j in "${Pattern6_three[@]}"
do
    for k in "${Alloc[@]}"
    do
        ./input-gen-alloc.py different-alloc/${j}-${k}.txt 6 ${TotalObjectNum} ${j} 0.1 ${k}
    done
done

for j in "${Pattern6_six[@]}"
do
    for k in "${Alloc[@]}"
    do
        ./input-gen-alloc.py different-alloc/${j}-${k}.txt 6 ${TotalObjectNum} ${j} 0.1 ${k}
    done
done