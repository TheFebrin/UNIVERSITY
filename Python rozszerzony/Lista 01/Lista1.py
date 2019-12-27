def wydaj(n):
    nominaly = [1, 2, 5, 10, 20]
    d = {}
    for x in reversed(nominaly):
        d[x] = n // x
        n %= x

    return d

def romb(n):
    r = [ [' '] * (n - i) + ['*'] * (2 * i + 1) for i in range(n)]

    for x in r:
        print(*x)

    for i in range(2 * n + 1):
        print('*', end=' ')
    print()

    for x in reversed(r):
        print(*x)



def rozklad(n):
    x = 2
    d = {}
    while n > 1:
        while n % x == 0:
            if x in d:
                d[x] += 1
            else:
                d[x] = 1
            n /= x
        x += 1

    return d


if __name__ == '__main__':

    '''
        Zadanie 2
        print(wydaj(123))
    '''
    print(wydaj(123))

    '''
        Zadanie 3
        romb(4)
    '''
    romb(4)

    '''
        Zadanie 5
        print(rozklad(756))
    '''
    print(rozklad(756))
