#!/bin/bash

Xarray=(0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1 0.15 0.2 0.25 0.3 0.4 0.5 0.8 1)
Alloc=(0 100 300 500 1000)

# 6 total node, 3 node collusion
Pattern6_three=(911909+901919 911099 910199+901199)

# create plot input file
for i in "${Pattern6_three[@]}"
do
  rm -f collusion-alloc-result/${i}
  touch collusion-alloc-result/${i}
  echo "ot receivers unique ratio acc" >> collusion-alloc-result/${i}
done

for i in "${Alloc[@]}"
do
  for j in "${Pattern6_three[@]}"
  do
    for k in "${Xarray[@]}"
    do
      ./identify-leakers.py collusion-alloc/${j}-${i}-${k}.txt 1-2 6 ${i} ${k} >> collusion-alloc-result/${j}
    done
  done
done