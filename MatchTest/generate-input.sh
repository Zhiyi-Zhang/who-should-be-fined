#!/bin/bash

# 3 total node, single node leaker
./input-gen.py non-collusion/919-0.5.txt 3 20000 919 0.5
./input-gen.py non-collusion/919-0.2.txt 3 20000 919 0.2
./input-gen.py non-collusion/919-0.1.txt 3 20000 919 0.1
./input-gen.py non-collusion/919-0.05.txt 3 20000 919 0.05
./input-gen.py non-collusion/919-0.01.txt 3 20000 919 0.01

# 6 total node, 3 node collusion
./input-gen.py collusion/911909+900919-0.5.txt 6 20000 911909+900919 0.5
./input-gen.py collusion/911909+900919-0.2.txt 6 20000 911909+900919 0.2
./input-gen.py collusion/911909+900919-0.1.txt 6 20000 911909+900919 0.1
./input-gen.py collusion/911909+900919-0.05.txt 6 20000 911909+900919 0.05
./input-gen.py collusion/911909+900919-0.01.txt 6 20000 911909+900919 0.01

./input-gen.py collusion/911099-0.5.txt 6 20000 911099 0.5
./input-gen.py collusion/911099-0.2.txt 6 20000 911099 0.2
./input-gen.py collusion/911099-0.1.txt 6 20000 911099 0.1
./input-gen.py collusion/911099-0.05.txt 6 20000 911099 0.05
./input-gen.py collusion/911099-0.01.txt 6 20000 911099 0.01

./input-gen.py collusion/910199+901199-0.5.txt 6 20000 910199+901199 0.5
./input-gen.py collusion/910199+901199-0.2.txt 6 20000 910199+901199 0.2
./input-gen.py collusion/910199+901199-0.1.txt 6 20000 910199+901199 0.1
./input-gen.py collusion/910199+901199-0.05.txt 6 20000 910199+901199 0.05
./input-gen.py collusion/910199+901199-0.01.txt 6 20000 910199+901199 0.01

./input-gen.py collusion/999110-0.5.txt 6 20000 999110 0.5
./input-gen.py collusion/999110-0.2.txt 6 20000 999110 0.2
./input-gen.py collusion/999110-0.1.txt 6 20000 999110 0.1
./input-gen.py collusion/999110-0.05.txt 6 20000 999110 0.05
./input-gen.py collusion/999110-0.01.txt 6 20000 999110 0.01
