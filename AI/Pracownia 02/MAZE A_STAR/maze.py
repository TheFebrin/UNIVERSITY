import heapq
from os import system
from time import sleep
import crayons

MAZE = []
dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]

with open('in.txt') as f:
    for line in f:
        MAZE.append(list(line.strip()))

N, M = len(MAZE), len(MAZE[0])


def print_maze():
    system('cls')
    for m in MAZE:
        out = ''.join(m)
        for c in out:
            if c != '#':
                print(crayons.red(c, bold=True), end='')
            else:
                print(crayons.white('#'), end='')
        print()

    # sleep(0.015)


start, goal = (0, 0), (0, 0)
for i in range(N):
    for j in range(M):
        if MAZE[i][j] == 'S':
            start = (i, j)
        if MAZE[i][j] == 'G':
            goal = (i, j)


print(start, ' --> ', goal)


def heuristic(x, y, act):
    return abs(x - goal[0]) + abs(y - goal[1])


Q = []
counter = 0
visited = set()
heapq.heappush(Q, (0, start, 0)) # dodaje do kolejki Q (0, start, 0)
'''
Teraz zamiast par (x, y)
Trzymamy tupla (odl_od_mety, (x,y), liczba_krokow)
'''
while len(Q) > 0:
    counter += 1
    act = heapq.heappop(Q) # <-- zwraca tupla o minimalnej odl od mety
    cords = act[1]
    steps = act[2]

    print_maze()

    if cords == goal:
        break

    for i in range(4):
        new_x = cords[0] + dx[i]
        new_y = cords[1] + dy[i]

        if (new_x, new_y) in visited:
            continue

        if MAZE[new_x][new_y] in [' ', 'G']:
            heapq.heappush(Q, (heuristic(new_x, new_y, steps), (new_x, new_y), steps + 1))
            visited.add((new_x, new_y))
            MAZE[new_x][new_y] = str(steps % 10)
