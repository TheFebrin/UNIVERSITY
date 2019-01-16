import matplotlib.pyplot as plt
from PIL import Image
from PIL import ImageDraw

xs = [0.0, 3.5, 25, 25, -5, -5, 15, -0.5, 19.5, 7, 1.5]
ys = [0.0, 36, 25, 1.5, 3, 33, 11, 35, 15.5, 0, 10.5]
W = [1, 6, 4, 2, 3, 4, 2, 1, 5, 4, 1]
ts = [i / 100 for i in range(101)]
out_xs, out_ys = [], []


def binomialCoefficient(n, k):
    if k < 0 or k > n:
        return 0
    if k == 0 or k == n:
        return 1
    k = min(k, n - k)
    c = 1
    for i in range(k):
        c = c * (n - i) / (i + 1)
    return c


def Bernstein(t, n, k):
    binom = binomialCoefficient(n, k)
    ans = binom * (t ** k) * ((1 - t) ** (n - k))

    return ans


def P(n, r):

    for t in [x / (r - 1) for x in range(0, r)]:
        num_x = 0
        for i in range(n + 1):
            num_x += xs[i] * W[i] * Bernstein(t, n, i)

        num_y = 0
        for i in range(n + 1):
            num_y += ys[i] * W[i] * Bernstein(t, n, i)

        den = 0
        for i in range(n + 1):
            den += W[i] * Bernstein(t, n, i)

        out_xs.append(num_x / den)
        out_ys.append(num_y / den)


n = 10
R = 501
P(n, R)

for i in range(len(xs)):
    plt.scatter(xs[i], ys[i], s=50)

# plt.plot(xs, ys, 'b.-')

for i in range(len(out_xs)):
    plt.scatter(out_xs[i], out_ys[i], s=5)

plt.show()
