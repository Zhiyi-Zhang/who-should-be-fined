#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df1 = pd.read_csv("910199+901199", sep=" ")
df1["acc"] = 1 - df1["acc"]
df1.loc[df1["acc"] < 0.00000001, "acc"] = 0.00000001
print(df1.head())

df2 = pd.read_csv("111111", sep=" ")
df2["acc"] = 1 - df2["acc"]
df2.loc[df2["acc"] < 0.00000001, "acc"] = 0.00000001
print(df2.head())

df3 = pd.read_csv("999119", sep=" ")
df3["acc"] = 1 - df3["acc"]
df3.loc[df3["acc"] < 0.00000001, "acc"] = 0.00000001
print(df3.head())

fig = plt.figure()
fig.set_size_inches(4.8, 3.2)
ax = fig.add_subplot(111)

ax.plot(df1["ratio"], df1["acc"], 'r-', label='3 leakers out of 6')
ax.plot(df2["ratio"], df2["acc"], 'b--', label='6 leakers out of 6')
ax.plot(df3["ratio"], df3["acc"], 'g-.', label='2 leakers out of 6')
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
fig.savefig('collusion-ratio.png', dpi=100)

plt.show()