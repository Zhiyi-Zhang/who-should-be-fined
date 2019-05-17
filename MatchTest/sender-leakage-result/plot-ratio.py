#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_csv("sender-ot.txt", sep=" ")
df["acc"] = 1 - df["acc"]
df.loc[df["acc"] < 0.00000001, "acc"] = 0.00000001
print(df.head(20))

fig = plt.figure()
fig.set_size_inches(4.8, 3.2)
ax = fig.add_subplot(111)

ax.plot(df.loc[df["ot"] == 0.5]["ratio"], df.loc[df["ot"] == 0.5]["acc"], 'r-')
plt.yscale("log")
plt.ylim(top=1)
plt.ylim(bottom=0.00000001)
plt.xlim(left=0.01)
plt.xlim(right=0.1)
plt.xlabel("Leakage Ratio")
plt.ylabel("Error Rate")
plt.grid(True)
plt.tight_layout()
fig.savefig('sender-ratio.png', dpi=100)

plt.show()