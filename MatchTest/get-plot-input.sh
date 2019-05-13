#!/bin/bash

Xarray=(0.01 0.015 0.02 0.025 0.03 0.04 0.05 0.1 0.5 0.8 1)

# 6 total node, 2 node collusion
Pattern6_two=(911999+901999 991199 999119)
# 6 total node, 3 node collusion
Pattern6_three=(911909+901919 911099 910199+901199)
# 6 total node, 6 node collusion
Pattern6_six=(111000+100111 111111 111001)

# #######################################COLLUSION LEAKER############################
# rm -rf collusion-result
# mkdir collusion-result

for i in "${Pattern6_two[@]}"
do
  touch collusion-result/${i}
done
for i in "${Pattern6_three[@]}"
do
  touch collusion-result/${i}
done
for i in "${Pattern6_six[@]}"
do
  touch collusion-result/${i}
done
for i in "${Xarray[@]}"
do
  for j in "${Pattern6_two[@]}"
  do
    ./test.py collusion/${j}-${i}.txt ${i} >> collusion-result/${j}
  done

  for j in "${Pattern6_three[@]}"
  do
    ./test.py collusion/${j}-${i}.txt ${i} >> collusion-result/${j}
  done

  for j in "${Pattern6_six[@]}"
  do
    ./test.py collusion/${j}-${i}.txt ${i} >> collusion-result/${j}
  done
done

# #######################################DIFF OT############################
# rm -rf different-ot-result
# mkdir different-ot-result

OTs=(1-2 2-3 3-4)

# create plot input file
for i in "${Pattern6_two[@]}"
do
  touch different-ot-result/${i}
done
for i in "${Pattern6_three[@]}"
do
  touch different-ot-result/${i}
done
for i in "${Pattern6_six[@]}"
do
  touch different-ot-result/${i}
done
for i in "${OTs[@]}"
do
  for j in "${Pattern6_two[@]}"
  do
    ./test.py different-ot/${j}-${i}.txt ${i} >> different-ot-result/${j}
  done
  for j in "${Pattern6_three[@]}"
  do
    ./test.py different-ot/${j}-${i}.txt ${i} >> different-ot-result/${j}
  done
  for j in "${Pattern6_six[@]}"
  do
    ./test.py different-ot/${j}-${i}.txt ${i} >> different-ot-result/${j}
  done
done

#######################################DIFF ALLOC############################
# rm -rf different-alloc-result
# mkdir different-alloc-result

Alloc=(0 100 300 500 1000 2000)

touch different-alloc-result/999991
touch different-alloc-result/911099
for i in "${Alloc[@]}"
do
  for j in "${Pattern6_two[@]}"
  do
    ./test.py different-alloc/${j}-${i}.txt ${i} >> different-alloc-result/${j}
  done
  for j in "${Pattern6_three[@]}"
  do
    ./test.py different-alloc/${j}-${i}.txt ${i} >> different-alloc-result/${j}
  done
  for j in "${Pattern6_six[@]}"
  do
    ./test.py different-alloc/${j}-${i}.txt ${i} >> different-alloc-result/${j}
  done
done