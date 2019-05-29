#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_csv("single-leaker-alloc-1-2.txt", sep=" ")
df["acc"] = 1 - df["acc"]
df.loc[df["acc"] < 0.00000001, "acc"] = 0.000000011
print(df.head())

fig = plt.figure()
fig.set_size_inches(4.8, 3.2)
ax = fig.add_subplot(111)

ax.plot(df.loc[df["unique"] == 0]["ratio"], df.loc[df["unique"] == 0]["acc"], 'r-', label='u = 0')
ax.plot(df.loc[df["unique"] == 100]["ratio"], df.loc[df["unique"] == 100]["acc"], 'b--', label='u = 100')
ax.plot(df.loc[df["unique"] == 300]["ratio"], df.loc[df["unique"] == 300]["acc"], 'g-.', label='u = 300')
ax.plot(df.loc[df["unique"] == 1000]["ratio"], df.loc[df["unique"] == 1000]["acc"], 'm:', label='u = 1000')
plt.yscale("log")
plt.ylim(top=1)
plt.ylim(bottom=0.00000001)
plt.xlim(left=0.01)
plt.xlim(right=0.1)
plt.xlabel("Leakage Ratio", fontsize=12)
plt.ylabel("Error Rate", fontsize=12)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.rcParams.update({'font.size': 12})
fig.savefig('single-leaker-alloc.png', dpi=100)

plt.show()