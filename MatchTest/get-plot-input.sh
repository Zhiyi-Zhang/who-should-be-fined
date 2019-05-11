#!/bin/bash

rm -rf non-collusion-result
rm -rf collusion-result
mkdir non-collusion-result
mkdir collusion-result

Xarray=(0.01 0.05 0.1 0.2 0.5)

touch non-collusion-result/919
for i in "${Xarray[@]}"
do
  ./test.py non-collusion/919-${i}.txt ${i} >> non-collusion-result/919
done

touch collusion-result/911909+900919
touch collusion-result/911099
touch collusion-result/910199+901199
touch collusion-result/999110
for i in "${Xarray[@]}"
do
  ./test.py collusion/911909+900919-${i}.txt ${i} >> collusion-result/911909+900919
  ./test.py collusion/911099-${i}.txt ${i} >> collusion-result/911099
  ./test.py collusion/910199+901199-${i}.txt ${i} >> collusion-result/910199+901199
  ./test.py collusion/999110-${i}.txt ${i} >> collusion-result/999110
done
