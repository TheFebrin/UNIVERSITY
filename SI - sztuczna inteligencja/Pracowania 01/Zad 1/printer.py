import tabulate

figures = ('♚', '♖', '♔')


def pos_to_char(x, y, z):
    return [chr(x[0] + 96) + str(x[1]), chr(y[0] + 96) + str(y[1]), chr(z[0] + 96) + str(z[1])]


def pos2d(s):
    """
        s - position on the board, for example 'a3' or 'h8'
    """
    column = ord(s[0]) - ord('a')
    row = ord(s[1]) - ord('1')
    return column, row


def print_board(wk, wt, bk):
    """
        wk - position of the white king
        wt - position of the white tower
        bk - position of the black king
    """
    board = [[' ' for i in range(8)] for j in range(8)]
    c, r = pos2d(wk)
    board[r][c] = figures[0]

    c, r = pos2d(wt)
    board[r][c] = figures[1]

    c, r = pos2d(bk)
    board[r][c] = figures[2]

    board = [([chr(j + 49)] + board[j]) for j in range(8)] + [[' '] + [chr(j + 97) for j in range(8)]]

    print((tabulate.tabulate(board)))
    print()
