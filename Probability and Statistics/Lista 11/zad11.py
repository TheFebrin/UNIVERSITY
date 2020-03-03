import numpy as np
import matplotlib.pyplot as plt
import math

x, y = [], []
with open('zad11.csv', 'r') as f:
    for line in f:
        line = line[:-1]
        line = line.split(';')

        x.append(float(line[0]))
        y.append(float(line[1]))


x = np.array(x)
y = np.array(y)
n = len(x)

z = x - y
print('x - y :', z)

x_bar = np.mean(z)
print('x bar =  ', x_bar)

sigma = sum(((z - x_bar) ** 2))
sigma /= (n - 1)
sigma = math.sqrt(sigma)

print('sigma: ', sigma)


z_val = x_bar / sigma
z_val *= math.sqrt(n)

print('z value: ', z_val)
