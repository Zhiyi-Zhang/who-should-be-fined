import sys
import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
import matplotlib.pyplot as plt
import random

def remove_index(file_name):
  data = pd.read_csv(file_name, index_col[0])
  data.to_csv(file_name, index=False)

def add_rows(file_name, expected_rows):
  data = pd.read_csv(file_name)
  s = data.xs(1)
  while data.shape[0] < expected_rows:
    if data.shape[0] % 1000 == 0:
      print("In progress: ", data.shape[0])
    data = data.append(s, ignore_index=True)
  data.to_csv(file_name, index=False)

def add_columns(file_name):
  data = pd.read_csv(file_name)
  data['ssn'] = np.random.randint(100000000, 999999999, data.shape[0])
  data['phone'] = np.random.randint(1000000000, 9999999999, data.shape[0])
  data.to_csv(file_name, index=False)

if __name__ == "__main__":
    file_name = 'heart.csv'
    expected_rows = 200000
    add_rows(file_name, expected_rows)
    add_columns(file_name)
