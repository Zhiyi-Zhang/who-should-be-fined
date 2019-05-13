#!/bin/bash

# rm -rf non-collusion
# rm -rf collusion
# mkdir non-collusion
# mkdir collusion

Xarray=(0.01 0.015 0.02 0.025 0.03 0.04 0.05 0.1 0.5 0.8 1)

# 6 total node, 2 node collusion
Pattern6_two=(911999+901999 991199 999119)
# 6 total node, 3 node collusion
Pattern6_three=(911909+901919 911099 910199+901199)
# 6 total node, 6 node collusion
Pattern6_six=(111000+100111 111111 110000)

TotalObjectNum=20000

for i in "${Xarray[@]}"
do
  #######################################COLLUSION LEAKER############################
  # 6 total node, 2 node collusion
  for j in "${Pattern6_two[@]}"
  do
    ./input-gen.py collusion/${j}-${i}.txt 6 ${TotalObjectNum} ${j} ${i}
  done

  # 6 total node, 3 node collusion
  for j in "${Pattern6_three[@]}"
  do
    ./input-gen.py collusion/${j}-${i}.txt 6 ${TotalObjectNum} ${j} ${i}
  done

  # 6 total node, 6 node collusion
  for j in "${Pattern6_six[@]}"
  do
    ./input-gen.py collusion/${j}-${i}.txt 6 ${TotalObjectNum} ${j} ${i}
  done
done