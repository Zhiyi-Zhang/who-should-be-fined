#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_csv("sender-receiver-num.txt", sep=" ")
df["acc"] = 1 - df["acc"]
df.loc[df["acc"] < 0.00000001, "acc"] = 0.000000011
print(df.head())

fig = plt.figure()
fig.set_size_inches(4.8, 3.2)
ax = fig.add_subplot(111)

ax.plot(df.loc[df["receivers"] == 3]["ratio"], df.loc[df["receivers"] == 3]["acc"], 'r-', label='Total 3 Receiver')
ax.plot(df.loc[df["receivers"] == 6]["ratio"], df.loc[df["receivers"] == 6]["acc"], 'b--', label='Total 6 Receiver')
ax.plot(df.loc[df["receivers"] == 9]["ratio"], df.loc[df["receivers"] == 9]["acc"], 'g-.', label='Total 9 Receiver')
plt.yscale("log")
plt.ylim(top=1)
plt.ylim(bottom=0.00000001)
plt.xlim(left=0.01)
plt.xlim(right=1)
plt.xlabel("Leakage Ratio", fontsize=12)
plt.ylabel("Error Rate", fontsize=12)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.rcParams.update({'font.size': 12})
fig.savefig('receiver-num-sender.png', dpi=100)

plt.show()