from os import system
import heapq

MAP = []
ALL_STATES = set()
dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]

maps = [
    'map1.txt',  # 0 - ans: 33
    'map2.txt',  # 1 - ans: 16
    'map3.txt',  # 2 - ans: 41
    'map4.txt',  # 3 - ans: 23
    'map5.txt',  # 4 - ans: 107
    'map6.txt',  # 5 - ans: 97
    'map7.txt',  # 6 - ans: 30
    'map8.txt',  # 7 - ans: 89
    'map9.txt',  # 8 - ans: 78
    'map10.txt',  # 9 - ans: 50
]
with open(maps[0]) as f:
    for line in f:
        MAP.append(list(line.strip()))

N, M = len(MAP), len(MAP[0])

print('START!')
for m in MAP:
    print(*m)

# extract all positions
# K - player's position
# B - chest's position
# G - goal's position
# * - chest laying on goal

sokoban_pos = (0, 0)
chests, goals, good_chests = [], [], {}
for i in range(N):
    for j in range(M):
        if MAP[i][j] == 'K':
            sokoban_pos = (i, j)
        if MAP[i][j] == 'B':
            chests.append((i, j))
        if MAP[i][j] == 'G':
            good_chests[(i, j)] = False
            goals.append((i, j))
        if MAP[i][j] == '*':
            good_chests[(i, j)] = True
            chests.append((i, j))
            goals.append((i, j))

        if MAP[i][j] != 'W':
            MAP[i][j] = '.'


def direction(x):
    return ['right', 'left', 'down', 'up'][x]


def hash_state(x, y, state):
    chests = tuple(state[1])
    return ((x, y), chests)


def hash_all(state):
    pos = state[0]
    chests = tuple(state[1])
    good = tuple(state[2].items())
    return (pos, chests, good)


def is_there_a_chest(x, y, chests):
    for c in chests:
        if c == (x, y):
            return True
    return False


def good_move(x, y, state, direction):
    if not(0 <= x <= N) or not(0 <= y <= M) or MAP[x][y] == 'W':
        return False

    hs = hash_state(x, y, state)

    chests = state[1]
    if is_there_a_chest(x, y, chests):
        if direction == 'down' and x + 1 < N and (is_there_a_chest(x + 1, y, chests) or MAP[x + 1][y] == 'W'):
            return False

        if direction == 'up' and x - 1 >= 0 and (is_there_a_chest(x - 1, y, chests) or MAP[x - 1][y] == 'W'):
            return False

        if direction == 'right' and y + 1 < M and (is_there_a_chest(x, y + 1, chests) or MAP[x][y + 1] == 'W'):
            return False

        if direction == 'left' and y - 1 >= 0 and (is_there_a_chest(x, y - 1, chests) or MAP[x][y - 1] == 'W'):
            return False
    else:
        if hs in ALL_STATES:
            return False

    ALL_STATES.add(hs)
    return True


def move_chest(x, y, direction, chests, good_chests):
    vector = (dx[direction], dy[direction])

    for i in range(len(chests)):
        c_x = chests[i][0]
        c_y = chests[i][1]
        if c_x == x and c_y == y:
            if chests[i] in goals:
                good_chests[chests[i]] = False
            chests[i] = (c_x + vector[0], c_y + vector[1])
            if chests[i] in goals:
                good_chests[chests[i]] = True


def win(good_chests):
    for c in good_chests.items():
        if not c[1]:
            return False
    return True


def print_map(state):
    # system('clear')
    MAP2 = [[] for _ in range(N)]
    for i in range(N):
        MAP2[i] = MAP[i].copy()

    s_pos = state[0]
    chests = state[1]
    MAP2[s_pos[0]][s_pos[1]] = 'K'
    for c in chests:
        MAP2[c[0]][c[1]] = 'B'

    for m in MAP2:
        print(*m)

    print()


def print_answer(state):
    print('Number of steps: ', len(state[3]))
    print()
    print([direction(i) for i in state[3]])


def heuristic(state):
    min_dist = 1e9
    player_x, player_y = state[0][0], state[0][1]
    chests = state[1]
    for c in chests:
        for g in goals:
            act_dist = abs(player_x - c[0]) + abs(player_y - c[1])
            act_dist += abs(c[0] - g[0]) + abs(c[1] - g[1])
            min_dist = min(min_dist, act_dist)

    return min_dist + len(state[3])


# A*
Q = []  # priority queue
state = (sokoban_pos, chests, good_chests, [])
heapq.heappush(Q, (heuristic(state), state))
ALL_STATES.add(hash_state(sokoban_pos[0], sokoban_pos[1], state))

while len(Q) > 0:
    act_state = heapq.heappop(Q)
    # print(act_state[0], act_state[1][0], act_state[1][1])
    act_state = act_state[1]
    # print_map(act_state)

    if win(act_state[2]):
        print('\nSOLUTION FOUND!!\n')
        print_map(act_state)
        print_answer(act_state)
        break

    s_pos = act_state[0]
    for i in range(4):
        new_x = s_pos[0] + dx[i]
        new_y = s_pos[1] + dy[i]
        chests, good_chests = act_state[1].copy(), act_state[2].copy()
        moves = act_state[3].copy()
        # print(s_pos, ' ---> ', (new_x, new_y), direction(i))

        if good_move(new_x, new_y, act_state, direction(i)):
            if is_there_a_chest(new_x, new_y, act_state[1]):
                move_chest(new_x, new_y, i, chests, good_chests)

            moves.append(i)
            new_state = ((new_x, new_y), chests, good_chests, moves)
            heapq.heappush(Q, (heuristic(new_state), new_state))
