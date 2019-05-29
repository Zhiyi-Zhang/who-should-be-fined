#!/bin/bash

Xarray=(0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1 0.15 0.2 0.25 0.3 0.4 0.5 0.8 1)
ReceiverNum=(3 6 9)

rm sender-receiver-num.txt
touch sender-receiver-num.txt
echo "ot receivers unique ratio acc" >> sender-receiver-num.txt
for i in "${ReceiverNum[@]}"
do
  for j in "${Xarray[@]}"
  do
    ./sender-leakage-input-gen.py ${i} 20000 0 1-2 ${j} >> sender-receiver-num.txt
  done
done

rm single-receiver-num.txt
touch single-receiver-num.txt
echo "ot receivers unique ratio acc" >> single-receiver-num.txt
for i in "${ReceiverNum[@]}"
do
  for j in "${Xarray[@]}"
  do
    ./single-leaker-input-gen.py ${i} 20000 0 1-2 ${j} >> single-receiver-num.txt
  done
done