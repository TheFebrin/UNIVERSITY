import subprocess
import random


def opt_dist(s, D):
    p = subprocess.Popen(["g++", "zad4.cpp"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p = subprocess.Popen(["./a.out"], shell=True, stdout=subprocess.PIPE, stdin=subprocess.PIPE)

    val = s + '\n' + str(D) + '\n'
    val = bytes(val, 'UTF-8')
    p.stdin.write(val)
    p.stdin.flush()
    res = p.stdout.readline().strip()
    return (chr(res[0]))


opt_dist('0010001000', '5')

test1 = [
    ([7, 7, 7, 7, 7, 7, 7], [7, 7, 7, 7, 7, 7, 7]),
    ([2, 2, 7, 7, 2, 2, 2], [2, 2, 7, 7, 2, 2, 2]),
    ([2, 2, 7, 7, 2, 2, 2], [4, 4, 2, 2, 2, 5, 5]),
    ([7, 6, 5, 4, 3, 2, 1], [1, 2, 3, 4, 5, 6, 7]),
    ([7, 5, 3, 1, 1, 1, 1], [1, 2, 3, 7, 3, 2, 1])
]

OBRAZEK = [[0 for _ in range(7)] for _ in range(7)]


def is_good_row(row_no, obr):
    row = ''.join(str(x) for x in OBRAZEK[row_no])
    row_blocks = obr[0][row_no]
    return opt_dist(row, row_blocks)


def solve(obr):
    random_row = random.randint(0, 6)
    print(is_good_row(random_row, obr))


solve(test1[0])
