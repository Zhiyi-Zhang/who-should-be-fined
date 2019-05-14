#!/bin/bash

Xarray=(0.01 0.015 0.02 0.025 0.03 0.04 0.05 0.1 0.5 0.8 1)

# 6 total node, 3 node collusion
Pattern6_three=(911909+901919 911099 910199+901199)

Alloc=(0 100 300 500 1000 2000)

# create plot input file
for i in "${Pattern6_three[@]}"
do
  rm -f different-alloc-result/${i}
  touch different-alloc-result/${i}
done

for i in "${Alloc[@]}"
do
  for j in "${Pattern6_three[@]}"
  do
    for k in "${Xarray[@]}"
    do
      ./test-collusion-ot.py different-alloc/${j}-${i}-${k}.txt 6 1-2 ${k} ${i} >> different-alloc-result/${j}
    done
  done
done