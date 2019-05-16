#!/bin/bash

Xarray=(0.01 0.015 0.02 0.025 0.03 0.04 0.05 0.1 0.5 0.8 1)

# rm non-collusion-result/single-leaker-ot.txt
# touch non-collusion-result/single-leaker-ot.txt
# for i in "${Xarray[@]}"
# do
#   ./single-leaker-input-gen.py 6 20000 0 1-2 ${i} >> non-collusion-result/single-leaker-ot.txt
# done
# for i in "${Xarray[@]}"
# do
#   ./single-leaker-input-gen.py 6 20000 0 2-3 ${i} >> non-collusion-result/single-leaker-ot.txt
# done
# for i in "${Xarray[@]}"
# do
#   ./single-leaker-input-gen.py 6 20000 0 3-4 ${i} >> non-collusion-result/single-leaker-ot.txt
# done

Alloc=(0 100 300 500 1000)

for j in "${Alloc[@]}"
do
  for i in "${Xarray[@]}"
  do
    ./single-leaker-input-gen.py 6 20000 ${j} 1-2 ${i} >> non-collusion-result/single-leaker-alloc-1-2.txt
  done
done

