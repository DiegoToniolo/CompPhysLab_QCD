import numpy as npy
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from scipy.stats import chi2
import sys

input_conf = open(sys.argv[1], "r")

lines = input_conf.readlines()

def f(x, q, m):
    return q + m*x

def g(x, a, b, c):
    return a + b * x + c * x**1.50

def Chi2f(f, par, x, y, err_y):
    sum = 0.0
    for i in range(0, len(x)):
        sum += ((f(x[i], par[0], par[1]) - y[i])/err_y[i])**2.0
    return sum

def Chi2g(g, par, x, y, err_y):
    sum = 0.0
    for i in range(0, len(x)):
        sum += ((g(x[i], par[0], par[1], par[2]) - y[i])/err_y[i])**2.0
    return sum

for line in lines:
    tokens = line.split()
    if len(tokens) == 0:
        continue
    if tokens[0] == "output":
        input_data = open(tokens[1].replace("\n", ""), "r")
    if tokens[0] == "n_t0":
        n_t0 = int(tokens[1]) + 1
    if tokens[0] == "np":
        np = int(tokens[1])
    if tokens[0] == "dir":
        directory = tokens[1]
    if tokens[0] == "t0_ts":
        t0_ts = []
        for i in range(1, n_t0):
            t0_ts += [float(tokens[i])]

lines = input_data.readlines()

x = []
y = []
err = []

for i in range(0, np):
    tokens = lines[i * n_t0].split()
    x += [float(tokens[0])]
    y += [float(tokens[1])]
    err += [float(tokens[2])]

x_model = npy.linspace(0, max(x) + 0.05, 1000)
par, par_err = curve_fit(f, x, y, sigma=err, absolute_sigma=True)
chi2_comp = Chi2f(f, par, x, y, err)
prob = 100 * (1-chi2.cdf(chi2_comp, len(x) - 2))
print("Fit: Chi2 = {:.6f}; Prob = {:.2f}".format(chi2_comp, prob))
print("q = {:.10} +- {:.10f}; m = {:.10f} +- {:.10f}".format(par[0], npy.sqrt(par_err[0][0]), par[1], npy.sqrt(par_err[1][1])))
plt.xlim(0, max(x) + 0.05)
y_model = []
for j in x_model:
    y_model += [f(j, par[0], par[1])]
plt.xlabel("$a^2/t_0$")
plt.ylabel("$ \chi $")
plt.plot(x_model, y_model, 'r')
plt.errorbar(x, y, err, fmt = 'none', capsize=2)
plt.plot(x, y, "bo", label = "data")
plt.savefig(directory + "Chi.png")
plt.close()

m = ["o", "s", "v", "^"]

for j in range(0, n_t0 - 1):
    x = []
    y = []
    err = []
    for i in range(0, np):
        tokens = lines[i * n_t0 + j + 1].split()
        x += [float(tokens[0])]
        y += [float(tokens[1])]
        err += [float(tokens[2])]

    x_model = npy.linspace(0, max(x) + 0.05, 1000)
    par, par_err = curve_fit(g, x, y, sigma=err, absolute_sigma=True)
    chi2_comp = Chi2g(g, par, x, y, err)
    prob = 100 * (1-chi2.cdf(chi2_comp, len(x) - 3))
    print("Fit: Chi2 = {:.6f}; Prob = {:.2f}".format(chi2_comp, prob))
    print("a = {:.10} +- {:.10f}; b = {:.10f} +- {:.10f}; c = {:.10f} +- {:.10f}".format(par[0], npy.sqrt(par_err[0][0]), par[1], npy.sqrt(par_err[1][1]), par[2], npy.sqrt(par_err[2][2])))
    plt.xlim(0, max(x) + 0.05)
    y_model = []
    for i in x_model:
        y_model += [g(i, par[0], par[1], par[2])]
    plt.xlabel("$a^2/t_0$")
    plt.ylabel("$\chi^{t} / \chi$")
    plt.plot(x_model, y_model, 'r')
    plt.errorbar(x, y, err, fmt = 'none', capsize=2)
    plt.plot(x, y, m[j], label = "{:.2f}".format(t0_ts[j]) + "$t_0$")
    plt.legend(loc = "lower left")
    plt.savefig(directory + "ratio.png")
        
