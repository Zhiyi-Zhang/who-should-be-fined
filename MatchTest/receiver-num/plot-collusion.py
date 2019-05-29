#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df1 = pd.read_csv("collusion-result/3.txt", sep=" ")
df1["acc"] = 1 - df1["acc"]
df1.loc[df1["acc"] < 0.00000001, "acc"] = 0.000000011
print(df1.head())

df2 = pd.read_csv("collusion-result/6.txt", sep=" ")
df2["acc"] = 1 - df2["acc"]
df2.loc[df2["acc"] < 0.00000001, "acc"] = 0.000000011
print(df2.head())

df3 = pd.read_csv("collusion-result/9.txt", sep=" ")
df3["acc"] = 1 - df3["acc"]
df3.loc[df3["acc"] < 0.00000001, "acc"] = 0.000000011
print(df3.head())

fig = plt.figure()
fig.set_size_inches(4.8, 3.2)
ax = fig.add_subplot(111)

ax.plot(df1["ratio"], df1["acc"], 'r-', label='Total 3 Receivers')
ax.plot(df2["ratio"], df2["acc"], 'b--', label='Total 6 Receivers')
ax.plot(df3["ratio"], df3["acc"], 'g-.', label='Total 9 Receivers')
plt.yscale("log")
plt.ylim(top=1.05)
plt.ylim(bottom=0.00000001)
plt.xlim(left=0.01)
plt.xlim(right=1)
plt.xlabel("Leakage Ratio", fontsize=12)
plt.ylabel("Error Rate", fontsize=12)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.rcParams.update({'font.size': 12})
fig.savefig('receiver-num-collusion.png', dpi=100)

plt.show()