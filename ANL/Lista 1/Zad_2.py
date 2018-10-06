def Szereg(n):
    x0 = 1
    x1 = - 1 / 7

    if n == 0:
        return x0

    if n == 1:
        return x1

    return (13 * Szereg(n - 1) + 2 * Szereg(n - 2)) / 7


def Wzor(n):
    return (-1)**n * 1 / 7**n


for n in range(10):
    s = float(Szereg(n))
    w = float(Wzor(n))
    r = abs(s - w)
    print('dla n = {},\nrekurencyjnie = {:.16}, wzorem = {:.16}\nroznica: {} \n'.format(n, s, w, r))
