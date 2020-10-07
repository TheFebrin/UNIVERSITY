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


def count_blocks(PICTURE, R, C, no, type):
    '''
    counts number of consecutive blocks
    '''
    ans = []
    act_no = 0

    if type == 'row':
        for j in range(C):
            if PICTURE[no][j] != 'X':
                if act_no > 0:
                    ans.append(act_no)
                    act_no = 0
            else:
                act_no += 1

    if type == 'column':
        for i in range(R):
            if PICTURE[i][no] != 'X':
                if act_no > 0:
                    ans.append(act_no)
                    act_no = 0
            else:
                act_no += 1

    if act_no > 0:
        ans.append(act_no)

    return ans


def connect_two_blocks(PICTURE, R, C, rows, cols):
    for i in range(R):
        row = rows[i]
        num = len(row)
        blocks = count_blocks(PICTURE, R, C, i, 'row')

        if num == 1 and len(blocks) > 1:
            beg = PICTURE[i].index('X')
            end = list(reversed(PICTURE[i])).index('X')
            end = C - end
            for k in range(beg, end):
                PICTURE[i][k] = 'X'

    for i in range(C):
        col = cols[i]
        num = len(col)
        blocks = count_blocks(PICTURE, R, C, i, 'column')

        if num == 1 and len(blocks) > 1:
            beg, end = 0, 0
            for k in range(R):
                if PICTURE[k][i] == 'X':
                    beg = k
                    break

            for k in reversed(range(R)):
                if PICTURE[k][i] == 'X':
                    end = k
                    break

            for k in range(beg, end + 1):
                PICTURE[k][i] = 'X'


def generate_and_match(PICTURE, R, C, rows, cols):

    answers = []

    def generate(row, ptr, act, length):
        '''
        generates all possibilities for a row
        '''
        if ptr == len(row):
            act += (length - len(act)) * [' ']
            if act not in answers:
                answers.append(act)
            return

        for i in range(length):
            new_list = act.copy()

            if i == 0 and len(act):
                new_list += [' ']

            new_list += [' '] * i
            new_list += ['X'] * row[ptr]

            if len(new_list) <= length:
                generate(row, ptr + 1, new_list, length)

    for i in range(R):
        row = rows[i]
        answers.clear()

        generate(row, 0, [], C)
        row_possibilities = answers.copy()

        '''
        if our possible row doesn't mark a cell that should be marked, we delete it
        '''
        for ans in answers:
            for k in range(len(ans)):
                if PICTURE[i][k] == 'X' and ans[k] != 'X':
                    row_possibilities.remove(ans)
                    break

        '''
        we look for intersection of row possibilities, and mark them
        '''
        for k in range(C):
            if all(rp[k] == 'X' for rp in row_possibilities):
                PICTURE[i][k] = 'X'

        # same thing for columns
        for i in range(C):
            col = cols[i]
            answers.clear()

            generate(col, 0, [], R)
            col_possibilities = answers.copy()

            for ans in answers:
                for k in range(len(ans)):
                    if PICTURE[k][i] == 'X' and ans[k] != 'X':
                        col_possibilities.remove(ans)
                        break

            for k in range(R):
                if all(cp[k] == 'X' for cp in col_possibilities):
                    PICTURE[k][i] = 'X'


def deduct(rows, cols):
    PICTURE = [[' ' for _ in range(len(cols))] for _ in range(len(rows))]
    R, C = len(rows), len(cols)

    '''
    fill rows and columns with a single big number
    '''
    fill_those_with_one_number(PICTURE, R, C, rows, cols)

    '''
    generate all possibilities for row and match good ones
    '''
    generate_and_match(PICTURE, R, C, rows, cols)

    return PICTURE
