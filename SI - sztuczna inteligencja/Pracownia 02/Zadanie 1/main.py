import random

R, C = 0, 0
rows, cols = [], []

paintings = [
    'square.txt',  # 0
    'cat.txt',  # 1
    'duck.txt',  # 2
    'man.txt',  # 3
    'rocket.txt',  # 4
    'heart.txt',  # 5
    'anchor.txt',  # 6
    'car.txt',  # 7
    'mushroom.txt',  # 8
    'flower.txt',  # 9
    'triangle_man.txt',  # 10
]
with open(paintings[1]) as f:
    INPUT = []
    for line in f:
        INPUT.append(line.split())

    R, C = int(INPUT[0][0]), int(INPUT[0][1])

    for i in range(1, R + 1):
        rows.append(list(map(int, INPUT[i])))

    for i in range(R + 1, len(INPUT)):
        cols.append(list(map(int, INPUT[i])))

PICTURE = [['.' for _ in range(C)] for _ in range(R)]


def count_blocks(no, type):
    # counts number of consecutive blocks
    ans = []
    act_no = 0

    if type == 'row':
        for j in range(C):
            if PICTURE[no][j] == '.':
                if act_no > 0:
                    ans.append(act_no)
                    act_no = 0
            else:
                act_no += 1

    if type == 'column':
        for i in range(R):
            if PICTURE[i][no] == '.':
                if act_no > 0:
                    ans.append(act_no)
                    act_no = 0
            else:
                act_no += 1

    if act_no > 0:
        ans.append(act_no)
    return ans


def good_one(nums, no, type):
    # tells if ether row or column is valid
    return nums == count_blocks(no, type)


def good_rows():
    for i in range(R):
        if not good_one(rows[i], i, 'row'):
            return False
    return True


def fill_good():
    for i in range(R):
        if good_one(rows[i], i, 'row'):
            for j in range(C):
                if PICTURE[i][j] != 'X':
                    PICTURE[i][j] = 'O'

    for i in range(C):
        if good_one(cols[i], i, 'column'):
            for j in range(R):
                if PICTURE[j][i] != 'X':
                    PICTURE[j][i] = 'O'


# fill cells in ROWS for which we are sure about the answer
for i in range(R):
    row = rows[i]
    num = len(row)
    if num == 1 and row[0] >= C // 2 + 1:
        block_len = 2 * row[0] - C
        if C % 2 == 0:
            for j in range(C // 2, C // 2 + block_len // 2):
                PICTURE[i][j] = 'X'
            for j in range(C // 2 - block_len // 2, C // 2):
                PICTURE[i][j] = 'X'
        else:
            for j in range(C // 2, C // 2 + block_len // 2 + 1):
                PICTURE[i][j] = 'X'
            for j in range(C // 2 - block_len // 2, C // 2):
                PICTURE[i][j] = 'X'
    else:
        if sum(row) == C - num + 1:
            ptr = 0
            for n in row:
                for j in range(n):
                    PICTURE[i][j + ptr] = 'X'
                ptr += n + 1

# same thing for COLUMNS
for i in range(C):
    col = cols[i]
    num = len(col)
    if num == 1 and col[0] >= R // 2 + 1:
        block_len = 2 * col[0] - R
        if C % 2 == 0:
            for j in range(R // 2, R // 2 + block_len // 2):
                PICTURE[j][i] = 'X'
            for j in range(R // 2 - block_len // 2, R // 2):
                PICTURE[j][i] = 'X'
        else:
            for j in range(R // 2, R // 2 + block_len // 2 + 1):
                PICTURE[j][i] = 'X'
            for j in range(R // 2 - block_len // 2, R // 2):
                PICTURE[j][i] = 'X'
    else:
        if sum(col) == R - num + 1:
            ptr = 0
            for n in col:
                for j in range(n):
                    PICTURE[j + ptr][i] = 'X'
                ptr += n + 1

# lets try to fill some cells in ROWS
for i in range(len(rows)):
    for i in range(R):
        blocks = count_blocks(i, 'row')
        if len(rows[i]) == 1 and len(blocks) > 1:
            first_b, last_b = 0, 0
            for j in range(C):
                if PICTURE[i][j] == 'X':
                    first_b = j
                    break

            for j in reversed(range(C)):
                if PICTURE[i][j] == 'X':
                    last_b = j
                    break

            for j in range(first_b, last_b):
                PICTURE[i][j] = 'X'


# lets try to fill some cells in COLUMNS
for i in range(len(rows)):
    for i in range(C):
        blocks = count_blocks(i, 'column')
        if len(cols[i]) == 1 and len(blocks) > 1:
            first_b, last_b = 0, 0
            for j in range(C):
                if PICTURE[j][i] == 'X':
                    first_b = j
                    break

            for j in reversed(range(C)):
                if PICTURE[j][i] == 'X':
                    last_b = j
                    break

            for j in range(first_b, last_b):
                PICTURE[i][j] = 'X'


def count_transformation_cost(beg, goal, length):
    seg_length = sum(goal) + len(goal) - 1
    p, min_cost = 0, 1e9
    pref = 0

    while p + seg_length <= length:
        if p - 1 >= 0 and (beg[p - 1] == 'X' or beg[p - 1] == '#'):
            pref += 1

        act_cost = pref
        ptr = 0

        for n in goal:
            for i in range(n):
                if beg[p + ptr] == '.':
                    act_cost += 1
                ptr += 1

            if p + ptr < length and (beg[p + ptr] == 'X' or beg[p + ptr] == '#'):
                act_cost += 1

            ptr += 1

        while p + ptr < length:
            if beg[p + ptr] == 'X' or beg[p + ptr] == '#':
                act_cost += 1
            ptr += 1

        min_cost = min(min_cost, act_cost)
        p += 1

    if min_cost == 1e9:
        min_cost = 0

    return min_cost


def opt_dist(no, type):
    l1, l2 = [], []
    length = 0
    if type == 'row':
        l2 = rows[no]
        length = C
        for j in range(C):
            l1.append(PICTURE[no][j])

    if type == 'column':
        l2 = cols[no]
        length = R
        for j in range(R):
            l1.append(PICTURE[j][no])

    return count_transformation_cost(l1, l2, length)


def change_cell(i, j):
    if PICTURE[i][j] == '#':
        PICTURE[i][j] = '.'

    elif PICTURE[i][j] == '.':
        PICTURE[i][j] = '#'


def print_picture():
    for row in PICTURE:
        row = ['.' if (x == '.' or x == 'O') else '#' for x in row]
        print(*row)
    print()


def solve():
    i = random.randint(0, R - 1)
    row = rows[i]

    if good_one(row, i, 'row'):
        return

    opt_row = opt_dist(i, 'row')
    best_cell_to_change = -1

    for j in range(C):
        col = cols[j]
        opt_col = opt_dist(j, 'column')

        if PICTURE[i][j] == 'O' or PICTURE[i][j] == 'X':
            continue

        change_cell(i, j)

        new_opt_row = opt_dist(i, 'row')
        new_opt_col = opt_dist(j, 'column')

        if new_opt_col + new_opt_row < opt_row + opt_col:
            best_cell_to_change = j

        change_cell(i, j)

    # we are changing the pixel that maximizes smth
    if best_cell_to_change != -1:
        change_cell(i, best_cell_to_change)

        print_picture()


n = 0
while not good_rows():
    if n % 10 == 0:
        r_i = random.randint(0, R - 1)
        r_j = random.randint(0, C - 1)
        if PICTURE[r_i][r_j] == '#' or PICTURE[r_i][r_j] == '.':
            change_cell(r_i, r_j)
        print('Step: ', n)
    solve()
    n += 1

print_picture()
print()
