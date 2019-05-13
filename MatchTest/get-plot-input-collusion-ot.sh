#!/bin/bash

Xarray=(0.01 0.015 0.02 0.025 0.03 0.04 0.05 0.1 0.5 0.8 1)

# 6 total node, 3 node collusion
Pattern6_three=(911909+901919 911099 910199+901199)

OTs=(1-2 2-3 3-4)

# create plot input file
for i in "${Pattern6_three[@]}"
do
  rm -f different-ot-result/${i}
  touch different-ot-result/${i}
done

for i in "${OTs[@]}"
do
  for j in "${Pattern6_three[@]}"
  do
    for k in "${Xarray[@]}"
    do
      ./test-collusion-ot.py different-ot/${j}-${i}-${k} 6 ${i} ${k} 0 >> different-ot-result/${j}
    done
  done
done