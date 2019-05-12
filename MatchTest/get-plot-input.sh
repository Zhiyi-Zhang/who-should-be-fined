#!/bin/bash

Xarray=(0.01 0.015 0.02 0.025 0.03 0.04 0.05 0.1 0.5 0.8 1)
# 3 total node, single node leaker
Pattern3_single=(919 991)
# 6 total node, single node leaker
Pattern6_single=(919999 999991)
# 9 total node, single node leaker
Pattern9_single=(999199999 999991999)

# 6 total node, 2 node collusion
Pattern6_two=(911999+901999 991199 999119)
# 6 total node, 3 node collusion
Pattern6_three=(911909+900919 911099 910199+901199)
# 6 total node, 6 node collusion
Pattern6_six=(111000+100111 111111 111001)

#######################################SINGLE LEAKER############################
rm -rf non-collusion-result
mkdir non-collusion-result

for i in "${Pattern3_single[@]}"
do
  touch non-collusion-result/${i}
done
for i in "${Pattern6_single[@]}"
do
  touch non-collusion-result/${i}
done
for i in "${Pattern9_single[@]}"
do
  touch non-collusion-result/${i}
done
# fulfill
for i in "${Xarray[@]}"
do
  for j in "${Pattern3_single[@]}"
  do
    ./test.py non-collusion/${j}-${i}.txt ${i} >> non-collusion-result/${j}
  done
  for j in "${Pattern6_single[@]}"
  do
    ./test.py non-collusion/${j}-${i}.txt ${i} >> non-collusion-result/${j}
  done
  for j in "${Pattern9_single[@]}"
  do
    ./test.py non-collusion/${j}-${i}.txt ${i} >> non-collusion-result/${j}
  done
done

# #######################################COLLUSION LEAKER############################
rm -rf collusion-result
mkdir collusion-result

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

# OTs=(1-2 2-3 3-4)

# # create plot input file
# for i in "${Pattern6_single[@]}"
# do
#   touch different-ot-result/${i}
# done
# for i in "${Pattern6_three[@]}"
# do
#   touch different-ot-result/${i}
# done
# for i in "${OTs[@]}"
# do
#   for j in "${Pattern6_single[@]}"
#   do
#     ./test.py different-ot/${j}-${i}-0.9.txt ${i} >> different-ot-result/${j}
#   done
#   for j in "${Pattern6_three[@]}"
#   do
#     ./test.py different-ot/${j}-${i}-0.9.txt ${i} >> different-ot-result/${j}
#   done
# done

#######################################DIFF ALLOC############################
# rm -rf different-alloc-result
# mkdir different-alloc-result

# Alloc=(0 100 300 500 1000 2000)

# touch different-alloc-result/999991
# touch different-alloc-result/911099
# for i in "${Alloc[@]}"
# do
#   ./test.py different-alloc/999991-${i}.txt ${i} >> different-alloc-result/999991
#   ./test.py different-alloc/911099-${i}.txt ${i} >> different-alloc-result/911099
# done