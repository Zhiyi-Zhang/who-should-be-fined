#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

myFontSize = 15

df = pd.read_csv("sender-ot.txt", sep=" ")
df["acc"] = 1 - df["acc"]
df.loc[df["acc"] < 0.00000001, "acc"] = 0.000000011
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
plt.xlim(left=0.01)
plt.xlim(right=1)
plt.xlabel("Leakage Ratio", fontsize=myFontSize)
plt.ylabel("Error Rate", fontsize=myFontSize)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.tick_params(labelsize=myFontSize-1)
plt.rcParams.update({'font.size': myFontSize})
fig.savefig('sender-ot.pdf', format='pdf', dpi=1000)

plt.show()