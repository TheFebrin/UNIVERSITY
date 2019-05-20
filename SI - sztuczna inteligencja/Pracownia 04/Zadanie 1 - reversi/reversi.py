import random
import sys
from collections import defaultdict as dd
from turtle import *
import copy

#####################################################
# turtle graphic
#####################################################


BOK = 50
SX = -100
SY = 0
M = 8

weights = (
    (200, -100, 100, 50, 50, 100, -100, 200),
    (-100, -200, -50, -50, -50, -50, -200, -100),
    (100, -50, 100, 0, 0, 100, -50, 100),
    (50, -50, 0, 0, 0, 0, -50, 50),
    (50, -50, 0, 0, 0, 0, -50, 50),
    (100, -50, 100, 0, 0, 100, -50, 100),
    (-100, -200, -50, -50, -50, -50, -200, -100),
    (200, -100, 100, 50, 50, 100, -100, 200))


def deepcopy(obj):
    res = Board(obj.debug)
    res.board = []
    for row in obj.board:
        res.board.append(row.copy())
    res.fields = obj.fields.copy()
    return res


def kwadrat(x, y, kolor):
    fillcolor(kolor)
    pu()
    goto(SX + x * BOK, SY + y * BOK)
    pd()
    begin_fill()
    for i in range(4):
        fd(BOK)
        rt(90)
    end_fill()


def kolko(x, y, kolor):
    fillcolor(kolor)

    pu()
    goto(SX + x * BOK + BOK / 2, SY + y * BOK - BOK)
    pd()
    begin_fill()
    circle(BOK / 2)
    end_fill()

#####################################################


def initial_board():
    B = [[None] * M for _ in range(M)]
    B[3][3] = 0
    B[4][4] = 0
    B[3][4] = 1
    B[4][3] = 1
    return B


class Board:
    dirs = [(0, 1), (1, 0), (-1, 0), (0, -1), (1, 1), (-1, -1), (1, -1), (-1, 1)]

    def __init__(self, debug):
        self.board = initial_board()
        self.fields = set()
        self.debug = debug
        # self.move_list = []
        # self.history = []
        for i in range(M):
            for j in range(M):
                if self.board[i][j] is None:
                    self.fields.add((j, i))

        if debug:
            tracer(0, 0)

    def draw(self):
        for i in range(M):
            res = []
            for j in range(M):
                b = self.board[i][j]
                if b is None:
                    res.append('.')
                elif b == 1:
                    res.append('#')
                else:
                    res.append('o')
            print(' '.join(res))
        print()

    def show(self):
        for i in range(M):
            for j in range(M):
                kwadrat(i, j, 'green')

        for i in range(M):
            for j in range(M):
                if self.board[i][j] == 1:
                    kolko(j, i, 'black')
                if self.board[i][j] == 0:
                    kolko(j, i, 'white')

    def moves(self, player):
        res = []
        for (x, y) in self.fields:
            if any(self.can_beat(x, y, direction, player) for direction in Board.dirs):
                res.append((x, y))
        if not res:
            return [None]
        return res

    def can_beat(self, x, y, d, player):
        dx, dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x, y) == 1 - player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x, y) == player

    def get(self, x, y):
        if 0 <= x < M and 0 <= y < M:
            return self.board[y][x]
        return None

    def do_move(self, move, player):
        # self.history.append([x[:] for x in self.board])
        # self.move_list.append(move)

        if move is None:
            return
        x, y = move
        x0, y0 = move
        self.board[y][x] = player
        self.fields -= set([move])
        for dx, dy in self.dirs:
            x, y = x0, y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x, y) == 1 - player:
                to_beat.append((x, y))
                x += dx
                y += dy
            if self.get(x, y) == player:
                for (nx, ny) in to_beat:
                    self.board[ny][nx] = player

    def result(self):
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]
                if b == 0:
                    res += 1
                elif b == 1:
                    res -= 1
        return res

    def heuristic(self):
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]
                if b == 0:
                    res += weights[y][x]
                elif b == 1:
                    res -= weights[y][x]
        return res

    def terminal(self):
        return self.moves(True) == [None] and self.moves(False) == [None]

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return [None]

    def find_best(self, depth, player):
        def alphabeta(state, depth, alpha, beta, maximizing_player):
            if depth == 0 or state.terminal() or state.moves(maximizing_player) == [None]:
                return state.heuristic()

            children = state.moves(maximizing_player)
            if maximizing_player:
                value = -1e9
                for move in children:
                    new_board = deepcopy(state)
                    new_board.do_move(move, player)
                    value = max(value, alphabeta(new_board, depth - 1, alpha, beta, False))
                    alpha = max(alpha, value)
                    if alpha >= beta:
                        break
                return value
            else:
                value = 1e9
                for move in children:
                    new_board = deepcopy(state)
                    new_board.do_move(move, player)
                    value = min(value, alphabeta(new_board, depth - 1, alpha, beta, True))
                    beta = min(beta, value)
                    if alpha >= beta:
                        break
                return value

        best_move = None
        best_score = -1e9
        for move in self.moves(player):
            new_board = deepcopy(self)
            new_board.do_move(move, player)

            val = alphabeta(new_board, depth, -1e9, 1e9, player)
            if val > best_score:
                best_move = move
                best_score = val

        return best_move

    def finish(self):
        done()
