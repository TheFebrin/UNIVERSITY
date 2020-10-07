from os import system
import heapq
import find_path

MAP = []
ALL_STATES = set()
dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]

map1 = 'map1.txt'
validate = 'zad_input.txt'

with open(validate) as f:
    for line in f:
        MAP.append(list(line.strip()))

N, M = len(MAP), len(MAP[0])


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


def count_players_pos(x, y, direction, v):
    player_pos = (0, 0)

    if direction == 'down':
        player_pos = (x - v, y)

    if direction == 'up':
        player_pos = (x + v, y)

    if direction == 'right':
        player_pos = (x, y - v)

    if direction == 'left':
        player_pos = (x, y + v)

    return player_pos


def blocked_chest(x, y):
    cnt = 0
    for i in range(4):
        if MAP[x + dx[i]][y + dy[i]] == '#':
            cnt += 1

    return cnt >= 3


def good_move(x, y, chests, state, direction):

    # print('player on: ', count_players_pos(x, y, direction, 2), ' chest: ', x, y, direction)
    if tuple(chests) in ALL_STATES:
        return False

    # chest is moved out of boundry or into wall or chest position is occupied by another chest
    if not(0 <= x <= N) or not(0 <= y <= M) or MAP[x][y] == 'W' or (x, y) in state[1]:
        return False

    for chest in chests:
        if MAP[chest[0]][chest[1]] == '#' or blocked_chest(chest[0], chest[1]):
            return False

    # positon that is needed to push chest on (x,y)
    player_pos = count_players_pos(x, y, direction, 2)

    # if needed player position is blocked by chest or wall
    if player_pos in chests or MAP[player_pos[0]][player_pos[1]] == 'W':
        return False

    path_to_player_pos = find_path.find_path(print_map(state, True), state[0], player_pos)

    if path_to_player_pos == False:
        return False

    return path_to_player_pos[1]


def move_chest(k, x, y, chests, good_chests):
    if chests[k] in goals:
        good_chests[chests[k]] = False

    chests[k] = (x, y)
    if chests[k] in goals:
        good_chests[chests[k]] = True


def win(good_chests):
    for c in good_chests.items():
        if not c[1]:
            return False
    return True


def print_map(state, ret):
    # system('clear')
    '''
    @ret is True if we want to return map, False when print
    '''
    MAP2 = [[] for _ in range(N)]
    for i in range(N):
        MAP2[i] = MAP[i].copy()

    s_pos = state[0]
    chests = state[1]
    MAP2[s_pos[0]][s_pos[1]] = 'K'
    for c in chests:
        MAP2[c[0]][c[1]] = 'B'

    if ret:
        return MAP2
    else:
        for m in MAP2:
            print(*m)
        print()


def change(c):
    if c == 'down':
        return 'D'

    if c == 'up':
        return 'U'

    if c == 'left':
        return 'L'

    if c == 'right':
        return 'R'


def print_answer(state):
    answer = ''
    for c in state[3]:
        answer += change(c)

    print(answer)

    f = open('zad_output.txt', 'w')
    f.write(answer)
    f.close()


def manhattan_dist(A, B):
    return abs(A[0] - B[0]) + abs(A[1] - B[1])


def heuristic(state):
    # player_x, player_y = state[0][0], state[0][1]
    chests = state[1].copy()

    dist = 0
    for g in goals:
        if not chests:
            break

        distances = [(manhattan_dist(c, g), c) for c in chests]
        min_dist = min(distances)

        chests.remove(min_dist[1])
        dist += min_dist[0]

    return dist


# A*
Q = []  # priority queue
state = (sokoban_pos, chests, good_chests, [])
heapq.heappush(Q, (heuristic(state), state))
ALL_STATES.add(tuple(chests))

cnt = 0
while len(Q) > 0:
    act_state = heapq.heappop(Q)
    act_state = act_state[1]

    cnt += 1
    if cnt % 10000 == 0:
        print(cnt)
    # print(act_state[1])
    # print_map(act_state, False)

    if win(act_state[2]):
        # print('\nSOLUTION FOUND!!\n')
        # print_map(act_state, False)
        print_answer(act_state)
        break

    chests = act_state[1]
    for k in range(len(chests)):
        chest = chests[k]

        for i in range(4):
            new_x = chest[0] + dx[i]
            new_y = chest[1] + dy[i]

            chests, good_chests = act_state[1].copy(), act_state[2].copy()
            moves = act_state[3].copy()
            move_chest(k, new_x, new_y, chests, good_chests)

            can_move = good_move(new_x, new_y, chests, act_state, direction(i))
            if can_move != False:

                hs = tuple(chests)
                ALL_STATES.add(hs)

                can_move.append(direction(i))
                moves += can_move
                player_pos = count_players_pos(new_x, new_y, direction(i), 1)

                new_state = (player_pos, chests, good_chests, moves)
                heapq.heappush(Q, (heuristic(new_state), new_state))
