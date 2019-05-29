#!/bin/bash

Xarray=(0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1 0.15 0.2 0.25 0.3 0.4 0.5 0.8 1)
ReceiverNum=(3 6 9)
Pattern=911909+901919

# #######################################COLLUSION LEAKER############################

rm -rf collusion-result
mkdir collusion-result
for j in "${ReceiverNum[@]}"
do
  echo "ot receivers unique ratio acc" >> collusion-result/${j}.txt
  for i in "${Xarray[@]}"
  do
    ./identify-leakers.py collusion/${j}-${i}.txt 1-2 ${j} 0 ${i} >> collusion-result/${j}.txt
  done
done