from collections import deque
import random
import heapq

MAZE = []
goals = []
dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]
visited = set()
DEBUG = True
COMMANDOS = []
DISTANCE = {}

with open('zad_input.txt') as f:
    for line in f:
        MAZE.append(list(line.strip()))

N, M = len(MAZE), len(MAZE[0])


def print_maze():
    # printing act position of all commandos
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


def good_move(positions):
    '''
    checks if we can make this move
    '''
    h_s = tuple(positions)
    if h_s in visited:
        return False

    visited.add(h_s)
    return True


def make_new_pos(i, positions):
    '''
    move all commandos along a vector
    '''
    ans = []
    # list(map(lambda x: (x[0] + dx[i], x[1] + dy[i]), positions))

    for p in positions:
        new_x = p[0] + dx[i]
        new_y = p[1] + dy[i]

        if MAZE[new_x][new_y] != '#':
            ans.append((new_x, new_y))
        else:
            ans.append(p)

    return list(set(ans))


def mission_complete(state):
    for s in state:
        if not s in goals:
            return False
    return True


def merge(positions):
    '''
    if we can merge 2 commandos we do it!
    '''
    return list(set(positions))


def heuristic(positions, moves):
    distances = [DISTANCE[pos] for pos in positions]
    return max(distances) + moves


def print_answer(answer):
    f = open('zad_output.txt', 'w')
    f.write(answer)
    f.close()


def BFS(pos):
    DISTANCE[pos] = 1e9
    QQ = deque()
    visited = {}
    visited[pos] = True
    QQ.append((pos, 0))

    while QQ:
        act = QQ.popleft()
        dist = act[1]
        act = act[0]

        if act in goals:
            DISTANCE[pos] = min(DISTANCE[pos], dist)

        for i in range(4):
            new_x = act[0] + dx[i]
            new_y = act[1] + dy[i]

            if not (new_x, new_y) in visited and MAZE[new_x][new_y] != '#':
                visited[(new_x, new_y)] = True
                QQ.append(((new_x, new_y), dist + 1))


def all_shortest_paths(positions):
    for i in range(N):
        for j in range(M):
            pos = (i, j)
            if MAZE[i][j] != '#':
                BFS(pos)



#------------- START ----------------------------------------------------------
if DEBUG:
    print('INPUT MAZE')
    print_maze()


# filling our goals
for i in range(N):
    for j in range(M):
        if MAZE[i][j] == 'G':
            goals.append((i, j))

        if MAZE[i][j] == 'S':
            COMMANDOS.append((i, j))

        if MAZE[i][j] == 'B':
            goals.append((i, j))

all_shortest_paths(COMMANDOS)
Q = []
heapq.heappush(Q, (heuristic(COMMANDOS, 0), COMMANDOS, ''))
visited.add(tuple(COMMANDOS))
cnt = 0


while Q:
    cnt += 1
    if cnt % 100000 == 0:
        print(cnt)

    if cnt > 1000000:
        break

    act_state = heapq.heappop(Q)
    positions = act_state[1]
    moves = act_state[2]

    if mission_complete(positions):
        print('\nANSWER')
        print(moves, len(moves))
        print_answer(moves)
        break

    for i in range(4):
        new_positions = make_new_pos(i, positions)

        if good_move(new_positions):
            heapq.heappush(Q, (heuristic(new_positions, len(moves) + 1), new_positions, moves + vec_to_pos(i)))
            # print(act_state, ' - > ', new_positions, heuristic(new_positions, len(moves) + 1))
