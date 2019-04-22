def fill_those_with_one_number(PICTURE, R, C, rows, cols):
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


def count_blocks(no, type):
    '''
    counts number of consecutive blocks
    '''
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


def connect_blocks(PICTURE, R, C, rows, cols):
    for i in range(R):
        row = rows[i]
        num = len(row)
        blocks = count_blocks(i, 'row')


def deduct(rows, cols):
    PICTURE = [[' ' for _ in range(len(cols))] for _ in range(len(rows))]
    R, C = len(rows), len(cols)

    '''
    fill rows and columns with a single big number
    '''
    fill_those_with_one_number(PICTURE, R, C, rows, cols)
    fill_those_with_one_number(PICTURE, R, C, rows, cols)

    '''
    if we have one number and a few blocks we connect them
    '''

    for row in PICTURE:
        print(row)
