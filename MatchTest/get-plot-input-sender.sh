#!/bin/bash

Xarray=(0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1 0.15 0.2 0.25 0.3 0.4 0.5 0.8 1)
Alloc=(0 100 300 500 1000)

rm sender-leakage-result/sender-alloc-1-2.txt
touch sender-leakage-result/sender-alloc-1-2.txt
echo "ot receivers unique ratio acc" >> sender-leakage-result/sender-alloc-1-2.txt
for i in "${Alloc[@]}"
do
  for j in "${Xarray[@]}"
  do
    ./sender-leakage-input-gen.py 6 20000 ${i} 1-2 ${j} >> sender-leakage-result/sender-alloc-1-2.txt
  done
done

rm sender-leakage-result/sender-ot.txt
touch sender-leakage-result/sender-ot.txt
echo "ot receivers unique ratio acc" >> sender-leakage-result/sender-ot.txt
for j in "${Xarray[@]}"
do
  ./sender-leakage-input-gen.py 6 20000 ${i} 1-2 ${j} >> sender-leakage-result/sender-ot.txt
done
for j in "${Xarray[@]}"
do
  ./sender-leakage-input-gen.py 6 20000 ${i} 2-3 ${j} >> sender-leakage-result/sender-ot.txt
done
for j in "${Xarray[@]}"
do
  ./sender-leakage-input-gen.py 6 20000 ${i} 3-4 ${j} >> sender-leakage-result/sender-ot.txt
done