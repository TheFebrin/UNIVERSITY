import math as m


def ct(r, q):
    pier = m.sqrt((q ** 3) + (r ** 2))
    return (r + pier) ** (1 / 3) + (r - pier) ** (1 / 3)


def ct2(r, q):
    pier_2 = m.sqrt(r * r + q ** 3)
    pier_3 = (r + pier_2) ** (1 / 3)
    return 2 * r * pier_3 ** 2 / (pier_3 ** 4 + pier_3 ** 2 + q * q)


print(ct(1e-10, 1e-10))
print(ct2(1e-10, 1e-10))
# dla 1,1 powinno byc 0,59
print()
print(ct(1e-20, 1e-20))
print(ct2(1e-20, 1e-20))
# dla 2,1 powinno byc 1
