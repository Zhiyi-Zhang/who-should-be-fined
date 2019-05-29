#!/usr/bin/env python3

import sys
import numpy as np
from scipy.special import comb

rate = 1.0

def get_filename():
    if len(sys.argv) < 6:
        print("Usage:", sys.argv[0], "totalusernum totalcommonobjects uniquenum ot rate\n", file=sys.stderr)
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

def get_rate():
    global rate
    if len(sys.argv) >= 6:
        rate = float(sys.argv[5].rstrip())

def main():
    usernum = int(get_totalusernum().rstrip())
    totalObjects = get_totalobjectnum()
    uniqueness = get_uniquenum()
    otType = get_ot()
    get_rate()
    otK = 1.0
    otN = 2.0
    otOutput = ""

    if otType == "1-2":
      otK = 1.0
      otN = 2.0
      otOutput = "0.5"
    elif otType == "2-3":
      otK = 2.0
      otN = 3.0
      otOutput = "0.67"
    elif otType == "3-4":
      otK = 3.0
      otN = 4.0
      otOutput = "0.75"

    uniqueObjects = int((totalObjects - usernum * uniqueness) * otK / (otN ** usernum) + uniqueness)
    #print("unique objects: ", uniqueObjects)
    totalReceivedObjects = int((totalObjects - usernum * uniqueness) * otK / otN + uniqueness)
    #print("total Received Objects: ", totalReceivedObjects)
    totalLeakedObjects = int(totalReceivedObjects * rate)
    #print("total leaked Objects: ", totalLeakedObjects)
    prob = 1 - ((totalReceivedObjects - uniqueObjects)/totalReceivedObjects) ** totalLeakedObjects
    # comb(totalReceivedObjects - uniqueObjects, totalLeakedObjects) / comb(totalReceivedObjects, totalLeakedObjects)
    print(otOutput + " " + str(usernum) + " " + str(uniqueness) + " " + str(rate) + " " + str(prob))

if __name__ == "__main__":
    main()
