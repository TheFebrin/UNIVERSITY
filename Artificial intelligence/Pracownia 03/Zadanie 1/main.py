from collections import deque
from numpy import zeros
import deduction


def parse_input(no):
    print('SOLVING FOR: ', paintings[no])
    with open(paintings[no]) as f:
        INPUT, rows, cols = [], [], []
        for line in f:
            INPUT.append(line.split())

        R, C = int(INPUT[0][0]), int(INPUT[0][1])

        for i in range(1, R + 1):
            rows.append(list(map(int, INPUT[i])))

        for i in range(R + 1, len(INPUT)):
            cols.append(list(map(int, INPUT[i])))

    return (rows, cols)


def save_answer(image):
    file = open("zad_output.txt", "w")
    for row in image:
        print(*['#' if x else ' ' for x in row])
        for cell in row:
            if cell:
                file.write("#")
            else:
                file.write(".")

        file.write("\n")


def possiblle_settings(n, pattern):
    '''
    finds all possible blocks arrangements
    '''

    if n == 0:
        return [[]]
    if len(pattern) == 0:
        return [[0] * n]

    block_len = pattern[0]
    block = [1 for _ in range(block_len)]
    new_n = n - block_len

    if len(pattern[1:]) > 0:
        block += [0]
        new_n -= 1

    current_possibilities = [block + new_pattern for new_pattern in possiblle_settings(new_n, pattern[1:])]
    required_len = sum(pattern) + len(pattern) - 1

    if required_len < n:  # adjust size by filling beginning with zeros
        return current_possibilities + [
            [0] + new_pattern for new_pattern in possiblle_settings(n - 1, pattern)
        ]
    else:
        return current_possibilities


def find_answer(rows, columns, PICTURE):
    height, width = len(rows), len(columns)
    pr = [possiblle_settings(width, row) for row in rows]
    pc = [possiblle_settings(height, column) for column in columns]

    possible_rows = pr.copy()
    possible_columns = pc.copy()

    # we compare all possibilities with deduction output
    for i in range(len(pr)):
        act_row_poss = pr[i]
        for poss in act_row_poss:
            for k in range(len(poss)):
                if PICTURE[i][k] == 'X' and poss[k] != 1:
                    possible_rows[i].remove(poss)
                    break

    for i in range(len(pc)):
        act_col_poss = pc[i]
        for poss in act_col_poss:
            for k in range(len(poss)):
                if PICTURE[k][i] == 'X' and poss[k] != 1:
                    possible_columns[i].remove(poss)
                    break

    img = zeros((height, width))  # np matrix with zeros
    not_fixed = deque()  # what needs to be fixed

    def match_columns(y, x):
        cell = img[y][x]
        possible_columns[x] = [
            column for column in possible_columns[x] if column[y] == cell
        ]

    def match_rows(y, x):
        cell = img[y][x]
        possible_rows[y] = [
            row for row in possible_rows[y] if row[x] == cell
        ]

    def find_solution_for(y, x, current_rows):
        row_point = current_rows[0][x]

        if all(row[x] == row_point for row in current_rows):  # for all rows 'row_point' is the same
            img[y][x] = row_point  # we can be sure about this cell
            match_columns(y, x)  # we adjust columns

        else:  # same thing for columns

            # print()
            # print(x, y)
            # print(possible_columns[x])
            # print(possible_columns[x][0][y])
            column_point = possible_columns[x][0][y]

            if all(column[y] == column_point for column in possible_columns[x]):
                img[y][x] = column_point
                match_rows(y, x)
            else:

                not_fixed.append((y, x))  # we delay this cell

    for y in range(height):
        current_rows = possible_rows[y]

        for x in range(width):
            find_solution_for(y, x, current_rows)

    while len(not_fixed) > 0:
        y, x = not_fixed.popleft()
        current_rows = possible_rows[y]
        find_solution_for(y, x, current_rows)

    return img


def solve(picture_no):
    rows, cols = parse_input(picture_no)
    PICTURE = deduction.deduct(rows, cols)
    image = find_answer(rows, cols, PICTURE)
    save_answer(image)


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
    'zad_input.txt',  # VALIDATOR
]


picture_no = 11
solve(picture_no)
