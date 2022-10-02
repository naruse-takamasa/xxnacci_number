import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

csv_input = pd.read_csv(filepath_or_buffer="./output.txt", encoding="ms932", sep=",")

print(len(csv_input))

m = 30

n = 300

assert((n - 2) * (m - 1) == len(csv_input))

fig = plt.figure(figsize=(16, 9), dpi=120)

for i in range(1, m):
    x = []
    normal_y = []
    neon_y = []
    for j in range(200, n):
        idx = (n - 2) * (i - 1) + j - 2
        assert(j == csv_input.values[idx, 0])
        x.append(csv_input.values[idx, 0])
        neon_y.append(csv_input.values[idx, 2])
        normal_y.append(csv_input.values[idx, 3])
    # fig = plt.plot(x, normal_y, linestyle="dotted")
    fig = plt.plot(x, neon_y)

fig = plt.grid(True)
fig = plt.savefig("fig.png")
# fig = plt.show()

log = plt.figure(figsize=(16, 9), dpi=120)

x = []
normal_y = []
neon_y = []
for i in range(1, m):
    for j in range(299, n):
        idx = (n - 2) * (i - 1) + j - 2
        assert(j == csv_input.values[idx, 0])
        x.append(csv_input.values[idx, 1])
        neon_y.append(csv_input.values[idx, 2])
        normal_y.append(csv_input.values[idx, 3])

log = plt.plot(x, normal_y, linestyle="dotted")
log = plt.plot(x, neon_y)

log = plt.grid(True)
log = plt.savefig("log.png")
plt.show()
