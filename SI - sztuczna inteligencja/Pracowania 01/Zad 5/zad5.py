import subprocess
import random


def opt_dist_slow(s, D):
    p = subprocess.Popen(["g++", "zad4.cpp"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p = subprocess.Popen(["./a.out"], shell=True, stdout=subprocess.PIPE, stdin=subprocess.PIPE)

    val = s + '\n' + str(D) + '\n'
    val = bytes(val, 'UTF-8')
    p.stdin.write(val)
    p.stdin.flush()
    res = p.stdout.readline().strip()
    return int((chr(res[0])))


def opt_dist(s, D):
    n = len(s)
    pref = [0 for _ in range(n + 1)]
    if s[0] == 1:
        pref[0] = 1

    for i in range(1, n):
        pref[i] = pref[i - 1]
        if s[i] == 1:
            pref[i] += 1

    ans = 100
    p = 0
    while p + D - 1 < n:
        ones_before = 0
        if p > 0:
            ones_before = pref[p - 1]

        ones_after = pref[n - 1] - pref[p + D - 1]
        ones_in_range = pref[p + D - 1] - ones_before
        changes_need = ones_before + ones_after + D - ones_in_range
        ans = min(ans, changes_need)
        p += 1

    # print(s, D, ans)
    return ans


test1 = [
    ([7, 7, 7, 7, 7, 7, 7], [7, 7, 7, 7, 7, 7, 7]),
    ([2, 2, 7, 7, 2, 2, 2], [2, 2, 7, 7, 2, 2, 2]),
    ([2, 2, 7, 7, 2, 2, 2], [4, 4, 2, 2, 2, 5, 5]),
    ([7, 6, 5, 4, 3, 2, 1], [1, 2, 3, 4, 5, 6, 7]),
    ([7, 5, 3, 1, 1, 1, 1], [1, 2, 3, 7, 3, 2, 1])
]

OBRAZEK = [[0 for _ in range(7)] for _ in range(7)]


def good_rows(obr):
    for i in range(7):
        if opt_dist(OBRAZEK[i], obr[0][i]) > 0:
            return False

    print('ROWS ARE VALID!')
    return True


def repair(row_no, obr):

    row_blocks = obr[0][row_no]
    dist = opt_dist(OBRAZEK[row_no], row_blocks)

    # print('Blocks needed: ', row_blocks)
    # print('Blocks to change: ', dist)
    # print('Row: ', OBRAZEK[row_no])

    if dist == 0:
        return

    best_pixe = 0

    for j in range(7):

        og_column = []
        for x in range(7):
            og_column.append(OBRAZEK[x][j])

        og_change_row = opt_dist(OBRAZEK[row_no], row_blocks)
        og_change_column = opt_dist(og_column, obr[1][j])
        og_chages = og_change_column + og_change_row

        OBRAZEK[row_no][j] ^= 1

        new_column = []
        for x in range(7):
            new_column.append(OBRAZEK[x][j])

        new_change_row = opt_dist(OBRAZEK[row_no], row_blocks)
        new_change_column = opt_dist(new_column, obr[1][j])
        new_changes = new_change_row + new_change_column

        if new_changes < og_chages:
            best_pixe = j

        OBRAZEK[row_no][j] ^= 1

    OBRAZEK[row_no][best_pixe] ^= 1
    # print('Changed pixel: ', (row_no, best_pixe))


def solve(obr):
    R = 10000
    step = 0
    while step < R and not good_rows(obr):
        if step % 10 == 0:
            r_i = random.randint(0, 6)
            r_j = random.randint(0, 6)
            OBRAZEK[r_i][r_j] ^= 1

        random_row = random.randint(0, 6)
        # print('chosed row: ', random_row)
        print('Step: ', step)
        repair(random_row, obr)

        for line in OBRAZEK:
            line = ['#' if x == 1 else ' ' for x in line]
            print(*line)

        print('\n\n')
        step += 1


solve(test1[2])

'''
TEST 0
#######
#######
#######
#######
#######
#######
#######

TEST 1
..##...
..##...
#######
#######
..##...
..##...
..##...

TEST 2
##.....
##.....
#######
#######
.....##
.....##
.....##

TEST 3
#######
.######
..#####
...####
....###
.....##
......#

TEST 4
#######
.#####.
..###..
...#...
...#...
...#...
...#...

'''
