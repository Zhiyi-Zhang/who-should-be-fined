#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_csv("910199+901199", sep=" ")
df["acc"] = 1 - df["acc"]
df.loc[df["acc"] < 0.00000001, "acc"] = 0.00000001
print(df.head(20))

fig = plt.figure()
fig.set_size_inches(4.8, 3.2)
ax = fig.add_subplot(111)

ax.plot(df.loc[df["ot"] == 0.5]["ratio"], df.loc[df["ot"] == 0.5]["acc"], 'r-', label='1-2 OT')
ax.plot(df.loc[df["ot"] == 0.67]["ratio"], df.loc[df["ot"] == 0.67]["acc"], 'b--', label='2-3 OT')
ax.plot(df.loc[df["ot"] == 0.75]["ratio"], df.loc[df["ot"] == 0.75]["acc"], 'g-.', label='3-4 OT')
plt.yscale("log")
plt.ylim(top=1)
plt.ylim(bottom=0.00000001)
plt.xlim(left=0.02)
plt.xlim(right=0.1)
plt.xlabel("Leakage Ratio", fontsize=12)
plt.ylabel("Error Rate", fontsize=12)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.rcParams.update({'font.size': 12})
fig.savefig('collusion-ot.png', dpi=100)

plt.show()