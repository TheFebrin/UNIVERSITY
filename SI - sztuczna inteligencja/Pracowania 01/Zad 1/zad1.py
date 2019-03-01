import tabulate
from collections import deque

figures = ('♔', '♖', '♚')


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


print_board('h4', 'a5', 'b8')


def pos_to_cords(pos):
    return(ord(pos[0]) - 96, int(pos[1]))


def find_mate_pos(w_k, b_k, first):
    w_k = pos_to_cords(w_k)
    b_k = pos_to_cords(b_k)

    Q = deque()
    if first == 'white':
        Q.append(w_k)
        Q.append(b_k)
    else:
        Q.append(b_k)
        Q.append(w_k)

    print(Q.popleft())


INPUT = 'black c4 c8 h3'


def solve(board):
    board = INPUT.split()
    first_move = board[0]
    w_king = board[1]
    w_rook = board[2]
    b_king = board[3]

    find_mate_pos(w_king, b_king, first_move)


print(solve(INPUT))
