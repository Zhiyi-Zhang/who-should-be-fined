#!/usr/bin/env python3

import sys
import numpy as np

patternhelp = "A pattern is like: DCBA. For each slot, 1 means having, 0 means not having, 9 is a wildcar. E.g., 991 indicates the leaked data is from A. Another example is 911, which means A B collude and leak A&B\nA combination of pattern is also allowed, like: 911+119, which indicates leaked data is from A&B + B&C."
rate = 1.0
patterns = None

def get_filename():
    if len(sys.argv) < 6:
        print("Usage:", sys.argv[0], "file totalusernum totalcommonobjects pattern leakrate otType\n", file=sys.stderr)
        print(patternhelp, file=sys.stderr)
        exit(-1)
    return sys.argv[1]

def get_totalusernum():
    if len(sys.argv) >= 6:
        return sys.argv[2]

def get_totalobjectnum():
    if len(sys.argv) >= 6:
        return int(sys.argv[3].rstrip())

def get_pattern():
    global patterns
    if len(sys.argv) >= 6:
        patterns = sys.argv[4].rstrip().split("+")

def get_rate():
    global rate
    if len(sys.argv) >= 6:
        rate = float(sys.argv[5].rstrip())

def get_otType():
    if len(sys.argv) >= 7:
        return sys.argv[6].rstrip()
    else:
        return "1-2"

def countSetBits(n):
    count = 0
    while (n):
        count += n & 1
        n >>= 1
    return count

def match_pattern(case):
    if patterns is None:
        get_pattern()
    match = False
    for pattern in patterns:
        singlematch = True
        for j in range(len(pattern)):
            if j > len(case) - 1:
                if int(pattern[len(pattern) - j - 1]) == 1:
                    singlematch = False
                    break
                else:
                    continue
            if int(pattern[len(pattern) - j - 1]) == int(case[len(case) - j - 1]) or int(pattern[len(pattern) - j - 1]) == 9:
                # good
                continue
            else:
                singlematch = False
                break
        if singlematch == True:
            match = True
            break
    return match

def main():
    usernum = int(get_totalusernum().rstrip())
    usernump2 = 2 ** usernum
    otType = get_otType()
    print(otType)

    tots = np.zeros(usernump2, dtype=int)
    totalObjects = get_totalobjectnum()
    cnts = np.zeros(usernump2, dtype=int)
    get_rate()
    if otType == "1-2":
        totsvalue = totalObjects / usernump2
        for i in range(len(tots)):
            tots[i] = totsvalue
            if match_pattern(bin(i)[2:]) == True:
                cnts[i] = totsvalue * rate
    elif otType == "2-3":
        dnom = 3 ** usernum
        for i in range(len(tots)):
            setbits = countSetBits(i)
            tots[i] = totalObjects * (2 ** setbits) / dnom
            if match_pattern(bin(i)[2:]) == True:
                cnts[i] = tots[i] * rate
    elif otType == "3-4":
        dnom = 4 ** usernum
        for i in range(len(tots)):
            setbits = countSetBits(i)
            tots[i] = totalObjects * (3 ** setbits) / dnom
            if match_pattern(bin(i)[2:]) == True:
                cnts[i] = tots[i] * rate
    else:
        print("cannot recognize ot type")

    with open(get_filename(), 'w+') as f:
        f.write(get_totalusernum())
        f.write("\n")
        for i in range(usernump2):
            f.write(bin(i)[2:])
            f.write(" %i %i\n" % (cnts[i], tots[i]))

if __name__ == "__main__":
    main()
