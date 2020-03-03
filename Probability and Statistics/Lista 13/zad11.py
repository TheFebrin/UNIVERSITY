from matplotlib import pyplot as plt
from scipy.special import binom
import numpy as np
from math import *
from scipy.stats import binom
from scipy.stats import norm

p = 0.4
q = 0.6

n = 50


def foo_bernoulli(x, n):
    return binom.cdf(x, n, p)
    # return norm.pdf(x)


def foo_normal(x, n):
    return (1 + erf((x - n * p) / n * p * q * sqrt(2))) / 2
    # return (x - n * p) / sqrt(n * p * q)


x = np.arange(n + 1)
y_b = [foo_bernoulli(a, n) for a in x]
y_n = [foo_normal(a, n) for a in x]


diff = [abs(a - b) for a, b in zip(y_b, y_n)]
print(diff)
print('Maximum absolute error: ', max(diff))
# print('Maximum relative error: ', max([a / b for a, b in zip(diff, y_b)]))


plt.scatter(x, y_b)
plt.scatter(x, y_n)

plt.show()
