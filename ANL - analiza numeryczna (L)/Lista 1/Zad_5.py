import math


def sin(x, n):
    wynik = 0
    for i in range(n):
        wynik += (-1) ** i * (x ** (2 * i + 1)) / math.factorial(2 * i + 1)
    return wynik


for i in range(90):
    radians = i * math.pi / 180
    print('built in: {}\n my: {}\n'.format(math.sin(radians), sin(radians, 50)))


print(math.sin(math.pi), sin(math.pi, 50))
