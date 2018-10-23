from math import sqrt


def metoda_szkolna(a, b, c):
    return (-b + sqrt(b * b - 4 * a * c)) / (2 * a), (-b + sqrt(b * b - 4 * a * c)) / (2 * a)


def test():
    print(metoda_szkolna(0.00000000042, -4200000000000, 0.00000000042))
    print(metoda_szkolna(0.000000777, 777, 1))
    print(metoda_szkolna(0.00000000042, 4200000000000, 0.00000000042))


test()
print()


def bezpieczny_algorytm(a, b, c):
    if b > 0:
        x_1 = -b - sqrt(b * b - (4 * a * c))
    else:
        x_1 = -b + sqrt(b * b - (4 * a * c))
    x_2 = c / (a * x_1)
    return x_1, x_2


def test2():
    print(bezpieczny_algorytm(0.00000000042, -4200000000000, 0.00000000042))
    print(bezpieczny_algorytm(0.000000777, 777, 1))
    print(bezpieczny_algorytm(0.00000000042, 4200000000000, 0.00000000042))


test2()
