import numpy as np
import matplotlib.pyplot as plt

x = np.array([54.3, 61.8, 72.4, 88.7, 118.6, 194])
y = np.array([61.2, 49.5, 37.6, 28.4, 19.2, 10.1])

z = np.polyfit(x, y, 1)
fit_poly = np.poly1d(z)
fit = fit_poly(x)


# print(z)
print(fit_poly)
print('V = 100: ', fit_poly(100))


plt.plot(x, y, 'ro')
plt.plot(x, fit)
plt.show()

log_x = np.log(x)
log_y = np.log(y)
z = np.polyfit(log_x, log_y, 1)
fit_poly = np.poly1d(z)
fit = fit_poly(log_x)

print('For ln..')
print(fit_poly)

plt.plot(log_x, log_y, 'ro')
plt.plot(log_x, fit)
plt.show()
