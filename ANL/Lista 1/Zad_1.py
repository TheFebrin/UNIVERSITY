import math
print('f(x) = ax^2 + bx + c \n')
print('Podaj a: ')
a = float(input())

print('Podaj b: ')
b = float(input())

print('Podaj c: ')
c = float(input())

delta = b * b - 4 * a * c

x1 = (-b - math.sqrt(delta)) / (2 * a)
x2 = (-b + math.sqrt(delta)) / (2 * a)

print('delta: {}'.format(delta))
print('x1: {} \nx2: {} '.format(x1, x2))
print('f(x1): {:.8}'.format(a * x1 * x1 + b * x1 + c))
print('f(x2): {:.8}'.format(a * x2 * x2 + b * x2 + c))

# TESTY
# 1 -12 9
# 1 12 3
# -duzo 1 1
