#!/usr/bin/env python3

import sys
import numpy as np
from scipy.stats import binom
from scipy.stats import binom_test


def get_filename():
    if len(sys.argv) < 2:
        print("Usage:", sys.argv[0], "file", file=sys.stderr)
        exit(-1)
    return sys.argv[1]

def get_outputparam():
    return sys.argv[2]


def main():
    with open(get_filename()) as f:
        num = int(f.readline().rstrip())
        nump2 = 2 ** num
        cnts = np.zeros(nump2, dtype=int)
        tots = np.zeros(nump2, dtype=int)
        for i in range(nump2):
            line = f.readline().split()
            cnts[i] = int(line[1])
            tots[i] = int(line[2])
    # print("Leaked:\t", cnts)
    # print("Total:\t", tots)

    # Hypothesis testing
    alpha = 0.05  # Significance level
    results = np.zeros(num, dtype=bool)
    presults = np.zeros(num, dtype=float)
    for i in range(num):
        # Null hypothesis: peer[i] is irrelevant
        coef = 1 << i
        # Check each
        for j in range(nump2):
            if (j & coef) > 0:
                continue
            bi_n = cnts[j] + cnts[j ^ coef]
            if bi_n == 0:
                continue
            bi_p = tots[j] / (tots[j] + tots[j ^ coef])

            # prob = binom.cdf(cnts[j], bi_n, bi_p)
            # if prob < (alpha / 2) or prob > (1.0 - alpha / 2):
            #     print("Reject", i, "set:", j, "prob:", prob)
            #     results[i] = True
            #     presults[i] = prob
            #     break

            prob = binom_test(cnts[j], bi_n, bi_p)
            if prob < alpha:
                print("Reject", i, "set:", j, "prob:", prob)
                results[i] = True
                presults[i] = prob
                break
    print("Results:\t", results)
    accuracy = 1
    allFalse = True
    for i in range(num):
        if results[i] == True:
            allFalse = False
            accuracy = accuracy * (1 - presults[i])
    if allFalse == True:
        accuracy = 0
    print(get_outputparam() + ",", accuracy)

if __name__ == "__main__":
    main()
