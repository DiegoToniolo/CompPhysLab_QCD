import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import sys

input_conf = open(sys.argv[1], "r")
eps = float(sys.argv[2]);

lines = input_conf.readlines()
wt = []

for line in lines:
    tokens = line.split()
    if len(tokens) == 0:
        continue
    if tokens[0] == "out":
        input_data = open(tokens[1].replace("\n", ""), "r")
    if tokens[0] == "nwt":
        nwt = int(tokens[1])
    if tokens[0] == "wt":
        for i in range(1, nwt + 1):
            wt += [int(tokens[i])]
    if tokens[0] == "nc":
        n_conf = int(tokens[1])
    if tokens[0] == "out_graphs":
        out_name = tokens[1]
    if tokens[0] == "bin":
        bin_num = int(tokens[1])

for conf in wt:
    data = []
    for i in range(0, n_conf):
        data += [float(input_data.readline())]

    extr = abs(min(data))
    if extr < abs(max(data)):
        extr = abs(max(data))

    bins_hist = []
    for i in range(0, bin_num + 1):
        bins_hist += [-extr + (2*i/bin_num)*extr]

    plt.xlabel('Q at wilson time {}'.format(conf * eps))
    plt.hist(data, bins = bins_hist, alpha = 1.0, label = "data")
    plt.savefig(out_name + '{}.png'.format(conf))
    plt.close()
