import itertools
from collections import deque

MAZE = []
goals = []
dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]
visited = set()
DEBUG = False

with open('zad_input.txt') as f:
    for line in f:
        MAZE.append(list(line.strip()))

N, M = len(MAZE), len(MAZE[0])


def print_maze():
    for m in MAZE:
        print(*m)


def print_pos(positions):
    OUT = [[] for _ in range(N)]
    for i in range(N):
        for j in range(M):
            if MAZE[i][j] == '#' or MAZE[i][j] == 'B':
                OUT[i].append(MAZE[i][j])
            else:
                OUT[i].append(' ')

    for p in positions:
        OUT[p[0]][p[1]] = 'S'

    for o in OUT:
        print(*o)

    # for o in OUT:
    #     print(''.join(o))


def vec_to_pos(n):
    return ['R', 'L', 'D', 'U'][n]


# filling our goals
for i in range(N):
    for j in range(M):
        if MAZE[i][j] == 'B':
            goals.append((i, j))

# we take some sequence of moves and check if some commandos merge
# basically we want to merge as many as we can


def do_moves(moves):
    Q = []
    for i in range(N):
        for j in range(M):
            if MAZE[i][j] == 'S':
                Q.append((i, j))

    # print('Before: ', len(Q))
    for m in moves:
        dx, dy = 0, 0
        if m == 'U':
            dx = -1

        if m == 'D':
            dx = 1

        if m == 'R':
            dy = 1

        if m == 'L':
            dy = -1

        for i in range(len(Q)):
            new_x = Q[i][0]
            if new_x + dx >= 0 and new_x + dx < N:
                new_x += dx

            new_y = Q[i][1]
            if new_y + dy >= 0 and new_y + dy < M:
                new_y += dy

            if MAZE[new_x][new_y] != '#':
                Q[i] = (new_x, new_y)

    Q = list(set(Q))
    # print('After: ', len(Q))

    return (Q, len(Q))


def good_move(positions):
    h_s = tuple(positions)
    if h_s in visited:
        return False

    visited.add(h_s)
    return True


def make_new_pos(i, positions):
    ans = []
    # list(map(lambda x: (x[0] + dx[i], x[1] + dy[i]), positions))

    for p in positions:
        new_x = p[0] + dx[i]
        new_y = p[1] + dy[i]

        if 0 <= new_x < N and 0 <= new_y < M and MAZE[new_x][new_y] != '#':
            ans.append((new_x, new_y))
        else:
            ans.append(p)

    return ans


def mission_complete(state):
    for s in state:
        if not s in goals:
            return False
    return True


def can_merge(positions):
    pos = list(sorted(positions))
    ptr = 0
    while ptr < len(positions) - 1:
        if pos[ptr] == pos[ptr + 1]:
            if DEBUG:
                print(positions, '  ->  ', end=' ')
            positions.remove(pos[ptr])
            if DEBUG:
                print(positions)
            return True

        ptr += 1

    return False


def print_answer(answer):
    f = open('zad_output.txt', 'w')
    f.write(answer)
    f.close()


if DEBUG:
    print('INPUT MAZE')
    print_maze()

moves = ['U', 'D', 'L', 'R']
all_sequences = list(itertools.permutations(moves))
best_seq = ''
minimal_moves = 1e9
best_positions = []

for seq in all_sequences:
    no = 10
    act_seq = seq[0] * no + seq[1] * no + seq[2] * no + seq[3] * no

    after_seq = do_moves(act_seq)
    positions = after_seq[0]
    after_seq = after_seq[1]

    if after_seq < minimal_moves:
        minimal_moves = after_seq
        best_seq = act_seq
        best_positions = positions


Q = deque()
Q.append((best_positions, best_seq))
visited.add(tuple(best_positions))

if DEBUG:
    print('REDUCED MAZE')
    print_pos(best_positions)
    print('Starting positions: ')
    print(best_positions)
    print()
# print(best_seq)
cnt = 0


while len(Q) > 0:
    cnt += 1
    if cnt % 100000 == 0:
        print(cnt)

    act_state = Q.popleft()
    positions = act_state[0]
    moves = act_state[1]

    if can_merge(positions):
        if DEBUG:
            print('MERGED')
            print()
        visited.clear()
        Q.clear()

    if mission_complete(positions):
        print('FINISHED!')
        print(moves)
        print_answer(moves)
        break

    for i in range(4):
        new_positions = make_new_pos(i, positions)

        if good_move(new_positions):
            Q.append((new_positions, moves + vec_to_pos(i)))
