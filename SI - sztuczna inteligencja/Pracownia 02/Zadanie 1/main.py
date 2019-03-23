R, C = 0, 0
rows, cols = [], []

with open('in.txt') as f:
    INPUT = []
    for line in f:
        INPUT.append(line.split())

    R, C = int(INPUT[0][0]), int(INPUT[0][1])

    for i in range(1, R + 1):
        rows.append(list(map(int, INPUT[i])))

    for i in range(R + 1, len(INPUT)):
        cols.append(list(map(int, INPUT[i])))


PICTURE = [['.' for _ in range(C)] for _ in range(R)]

# first lets fill biggest numbers in rows or ones for which we know the answer
for i in range(len(rows)):
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

# same thing for columns
for i in range(len(cols)):
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
            print(col)
            ptr = 0
            for n in col:
                for j in range(n):
                    PICTURE[j + ptr][i] = 'X'
                ptr += n + 1


for row in PICTURE:
    print(*row)
