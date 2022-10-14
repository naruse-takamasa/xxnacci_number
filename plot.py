from statistics import stdev
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

csv_input = pd.read_csv(filepath_or_buffer="./output.txt", encoding="ms932", sep=",")

print(len(csv_input))

m = 30

n = 300

test_num = 30

assert((n - 2) * (m - 1) * 30 == len(csv_input))

def plot_figure(start_matrix_size, plot_naive_time):
    assert(start_matrix_size >= 2)

    name = "start_" + str(start_matrix_size)
    if plot_naive_time == 0:
        name = name + "_neon_time_only"
    txt_name = name + ".txt"
    fig_name = name + ".png"
    fig = plt.figure(figsize=(16, 9), dpi=120)
    f = open(txt_name, 'w')

    for i in range(1, m):
        x = []
        normal_y = []
        neon_y = []
        for j in range(start_matrix_size, n):
            idx = (n - 2) * (i - 1) * test_num + (j - 2) * test_num
            x.append(csv_input.values[idx, 0])
            neon_time = []
            naive_time = []
            for k in range(0, test_num):
                assert(j == csv_input.values[idx, 0])
                neon_time.append(csv_input.values[idx, 2])
                naive_time.append(csv_input.values[idx, 3])
                idx += 1
            neon_time.sort()
            naive_time.sort()
            neon_y.append(neon_time[(int)(test_num / 2)])
            normal_y.append(naive_time[(int)(test_num / 2)])
            print("neon: ", i, ", ", j, file=f)
            print("mid: ", neon_time[(int)(test_num / 2)], "max: ", neon_time[0], "min: ", neon_time[test_num - 1], "stddev: ", stdev(neon_time), file=f)
            print("naive: ", i, ", ", j, file=f)
            print("mid: ", naive_time[(int)(test_num / 2)], "max: ", naive_time[0], "min: ", naive_time[test_num - 1], "stddev: ", stdev(naive_time), file=f)
        if plot_naive_time:
            fig = plt.plot(x, normal_y, linestyle="dotted")
        fig = plt.plot(x, neon_y)

    fig = plt.grid(True)
    fig = plt.xlabel("matrix size")
    fig = plt.ylabel("elapse time[micro sec]")
    fig = plt.savefig(fig_name)
    fig = plt.show()

    f.close()

plot_figure(2, 0)
plot_figure(2, 1)
plot_figure(200, 0)
plot_figure(200, 1)
