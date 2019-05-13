#!/usr/bin/env python3

import sys
import numpy as np

def get_filename():
    if len(sys.argv) < 5:
        print("Usage:", sys.argv[0], "totalusernum totalcommonobjects uniquenum ot\n", file=sys.stderr)
        exit(-1)
    return sys.argv[1]

def get_totalusernum():
    if len(sys.argv) >= 5:
        return sys.argv[1]

def get_totalobjectnum():
    if len(sys.argv) >= 5:
        return float(sys.argv[2].rstrip())

def get_uniquenum():
    if len(sys.argv) >= 5:
        return int(sys.argv[3].rstrip())
    else:
        return 0

def get_ot():
    if len(sys.argv) >= 5:
        return sys.argv[4].rstrip()
    else:
        return "1-2"

def main():
    usernum = int(get_totalusernum().rstrip())
    totalObjects = get_totalobjectnum()
    uniqueness = get_uniquenum()
    otType = get_ot()
    otK = 1.0
    otN = 2.0

    if otType == "1-2":
      otK = 1.0
      otN = 2.0
    elif otType == "2-3":
      otK = 2.0
      otN = 3.0
    elif otType == "3-4":
      otK = 3.0
      otN = 4.0

    rate = 1.0 / (uniqueness + (totalObjects - usernum*uniqueness)*otK/(otN ** usernum))
    print(otType + " " + str(usernum) + " " + str(rate) + " " + "1")

if __name__ == "__main__":
    main()
