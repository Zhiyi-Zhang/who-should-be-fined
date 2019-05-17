#!/bin/bash

Xarray=(0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1 0.15 0.2 0.25 0.3 0.4 0.5 0.8 1)
Alloc=(0 100 300 500 1000)

# 6 total node, 2 node collusion
Pattern6_two=(911999+901999 991199 999119)
# 6 total node, 3 node collusion
Pattern6_three=(911909+901919 911099 910199+901199)
# 6 total node, 6 node collusion
Pattern6_six=(111000+100111 111111 110000)

# #######################################COLLUSION LEAKER############################

for i in "${Pattern6_two[@]}"
do
  rm -f collusion-ratio-result/${i}
  touch collusion-ratio-result/${i}
  echo "ot receivers unique ratio acc" >> collusion-ratio-result/${i}
done
for i in "${Pattern6_three[@]}"
do
  rm -f collusion-ratio-result/${i}
  touch collusion-ratio-result/${i}
  echo "ot receivers unique ratio acc" >> collusion-ratio-result/${i}
done
for i in "${Pattern6_six[@]}"
do
  rm -f collusion-ratio-result/${i}
  touch collusion-ratio-result/${i}
  echo "ot receivers unique ratio acc" >> collusion-ratio-result/${i}
done
for i in "${Xarray[@]}"
do
  for j in "${Pattern6_two[@]}"
  do
    ./identify-leakers.py collusion-ratio/${j}-${i}.txt 1-2 6 0 ${i} >> collusion-ratio-result/${j}
  done

  for j in "${Pattern6_three[@]}"
  do
    ./identify-leakers.py collusion-ratio/${j}-${i}.txt 1-2 6 0 ${i} >> collusion-ratio-result/${j}
  done

  for j in "${Pattern6_six[@]}"
  do
    ./identify-leakers.py collusion-ratio/${j}-${i}.txt 1-2 6 0 ${i} >> collusion-ratio-result/${j}
  done
done