#!/usr/bin/env python3

import sys
import numpy as np
from scipy.stats import binom


def get_filename():
    if len(sys.argv) < 2:
        print("Usage:", sys.argv[0], "file", file=sys.stderr)
        exit(-1)
    return sys.argv[1]


def main():
    # Read data
    # File format
    # #peers
    # Set1 #leaked #total
    # Set2 #leaked #total
    # ...
    with open(get_filename()) as f:
        num = int(f.readline().rstrip())
        nump2 = 2 ** num
        cnts = np.zeros(nump2, dtype=int)
        tots = np.zeros(nump2, dtype=int)
        for i in range(nump2):
            line = f.readline().split()
            cnts[i] = int(line[1])
            tots[i] = int(line[2])
    print("Leaked:\t", cnts)
    print("Total:\t", tots)

    # Hypothesis testing
    alpha = 0.05  # Significance level
    results = np.zeros(num, dtype=bool)
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
            prob = binom.cdf(cnts[j], bi_n, bi_p)
            if prob < (alpha / 2) or prob > (1.0 - alpha / 2):
                print("Reject", i, "set:", j, "prob:", prob)
                results[i] = True
                break
    print("Results:\t", results)


if __name__ == "__main__":
    main()
