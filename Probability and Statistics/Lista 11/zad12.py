import numpy as np
import matplotlib.pyplot as plt
import math

# https://surfstat.anu.edu.au/surfstat-home/tables/t.php

x = np.array([60, 65, 79, 55, 75, 60, 69, 108, 77, 88])
y = np.array([57, 60, 70, 60, 70, 65, 59, 101, 67, 86])


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
