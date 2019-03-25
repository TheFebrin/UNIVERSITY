MAZE = []
with open('maze1.txt') as f:
    for line in f:
        MAZE.append(list(line.strip()))

N, M = len(MAZE), len(MAZE[0])

for m in MAZE:
    print(*m)
