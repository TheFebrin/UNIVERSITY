import heapq

dx = [0, 0, 1, -1]
dy = [1, -1, 0, 0]


def find_path(MAP, start, goal):
    def heuristic(x, y, act):
        return abs(x - goal[0]) + abs(y - goal[1])

    def direction(x):
        return ['right', 'left', 'down', 'up'][x]

    MAZE = []
    for row in MAP:
        MAZE.append(row.copy())

    # print(start, ' -> ', goal)
    # for row in MAZE:
    #     print(row)
    # print()

    MAZE[goal[0]][goal[1]] = 'G'

    Q = []
    counter = 0
    visited = set()
    heapq.heappush(Q, (0, start, 0, []))
    while len(Q) > 0:
        counter += 1
        act = heapq.heappop(Q)
        cords = act[1]
        steps = act[2]
        sequence = act[3]

        MAZE[cords[0]][cords[1]] = '0'

        if cords == goal:
            return (steps, sequence)

        for i in range(4):
            new_x = cords[0] + dx[i]
            new_y = cords[1] + dy[i]

            if (new_x, new_y) in visited:
                continue

            if MAZE[new_x][new_y] == '.' or MAZE[new_x][new_y] == 'G':
                heapq.heappush(Q, (heuristic(new_x, new_y, steps), (new_x, new_y), steps + 1, sequence + [direction(i)]))
                visited.add((new_x, new_y))
                MAZE[new_x][new_y] = '0'

    return False
