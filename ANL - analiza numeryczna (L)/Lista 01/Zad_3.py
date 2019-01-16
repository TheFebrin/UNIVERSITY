import math


def suma_n(n):
    wynik = 0.0
    for i in range(n + 1):
        wynik += (-1) ** i / (2 * i + 1)
    return wynik * 4


def ile_iteracji():
    iter = 0
    wynik = 0.0
    while abs(4 * wynik - math.pi) > 1e-5:
        wynik += ((-1) ** iter) / (2 * iter + 1)
        iter += 1
        #print(4 * wynik, math.pi)
    return iter


print(ile_iteracji())
