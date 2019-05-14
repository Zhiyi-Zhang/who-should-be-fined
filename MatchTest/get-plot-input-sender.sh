#!/bin/bash

Xarray=(0.01 0.015 0.02 0.025 0.03 0.04 0.05 0.1 0.5 0.8 1)

rm sender-leakage-result/sender-ot.txt
touch sender-leakage-result/sender-ot.txt
for i in "${Xarray[@]}"
do
  ./sender-leakage-input-gen.py 6 20000 0 1-2 ${i} >> sender-leakage-result/sender-ot.txt
done
for i in "${Xarray[@]}"
do
  ./sender-leakage-input-gen.py 6 20000 0 2-3 ${i} >> sender-leakage-result/sender-ot.txt
done
for i in "${Xarray[@]}"
do
  ./sender-leakage-input-gen.py 6 20000 0 3-4 ${i} >> sender-leakage-result/sender-ot.txt
done

Alloc=(0 100 300 500 1000 2000)

rm sender-leakage-result/sender-alloc.txt
touch sender-leakage-result/sender-alloc.txt
for i in "${Alloc[@]}"
do
  ./sender-leakage-input-gen.py 6 20000 ${i} 1-2 0.1 >> sender-leakage-result/sender-alloc.txt
done
for i in "${Alloc[@]}"
do
  ./sender-leakage-input-gen.py 6 20000 ${i} 2-3 0.1 >> sender-leakage-result/sender-alloc.txt
done
for i in "${Alloc[@]}"
do
  ./sender-leakage-input-gen.py 6 20000 ${i} 3-4 0.1 >> sender-leakage-result/sender-alloc.txt
done