import sys

Reward = 100
Board = []

Moves = [(0, 0), (1, 0), (-1, 0), (0, 1), (0, -1),
         (1, 1), (1, -1), (1, 1), (-1, 1), (-1, -1)]

'''
My policy { x, y, dx, dy } = {reward, (action) }
'''
MyPolicy = {}


def print_board():
    for b in Board:
        print(*b)


def Speeds():
    for vx in range(-3, 4):
        for vy in range(-3, 4):
            yield vx, vy


def readData(FileName):
    with open(FileName, 'r') as f:
        for x in f:
            Board.append([y for y in list(x) if y in
                          ['o', '#', '.', 'e', 's']])
    while Board[-1] == []:
        Board.pop()


def saveOtput(FileName):
    outFileName = FileName.split('/')[-1]
    with open("policies/policy_for_{}".format(outFileName), 'w') as f:
        for k, v in MyPolicy.items():
            string = "{} {} {} {} {} {}\n".format(
                k[1], k[0], k[3], k[2], v[1][1], v[1][0])
            f.write(string)


def reward(state):
    x, y, _, _ = state
    if not (0 <= x < len(Board) and 0 <= y < len(Board[0])):
        return -Reward
    if Board[x][y] == 'e':
        return Reward
    if Board[x][y] == '.':
        return -Reward
    return -1


def readPolicyValue(state):
    x, y, _, _ = state
    if not (0 <= x < len(Board) and 0 <= y < len(Board[0])):
        return -Reward
    if Board[x][y] == '.':
        return -Reward
    if Board[x][y] == 'e':
        return Reward
    return MyPolicy[state][0]


def nextStates(state, action):
    x, y, vx, vy = state
    res = set()
    '''
    If our car is on oil it can make every possible move,
    otherwise it's (0, 0) additional vector
    '''
    Moves_on_oil = [(0, 0)]
    if Board[x][y] == 'o':
        Moves_on_oil = Moves

    for oil_moves in Moves_on_oil:
        dvx, dvy = action
        rx, ry = oil_moves

        new_vx = vx + dvx + rx
        new_vy = vy + dvy + ry

        new_vx = min(3, new_vx)
        new_vy = min(3, new_vy)
        new_vx = max(new_vx, -3)
        new_vy = max(new_vy, -3)

        res.add((x + new_vx, y + new_vy, new_vx, new_vy))
    return res


def optPolicy(state, gamma):
    res = []
    for action in Moves:
        nss = nextStates(state, action)
        '''
        T - probability of taking action
        gamma - discount factor
        reward(ns) - reward of taking action from 'state' to 'ns'
        readPolicyValue(ns) - expected value from state ns using our policy
        '''
        T = 1 / len(nss)
        value = sum([
                    T * (reward(ns) + gamma * readPolicyValue(ns)) for ns in nss
                    ])
        res.append((value, action))
    return max(res)


if __name__ == '__main__':
    print('Give task path as sys.arg.\n')
    if len(sys.argv) != 2:
        print("Wrong input!")
        exit()

    readData(sys.argv[1])
    print_board()

    '''
    First let's create random policy PI_o
    '''
    for x in range(len(Board)):
        for y in range(len(Board[x])):
            if Board[x][y] == '.':
                continue
            for s in Speeds():
                if Board[x][y] == 'e':  # we give revard for finish cell
                    MyPolicy[(x, y) + s] = (Reward, (0, 0))
                else:
                    MyPolicy[(x, y) + s] = (0, (0, 0))

    gamma = 0.99
    delta = 0
    tempPolicy = {}
    number_of_iterations = 0
    while(delta != gamma * Reward):
        number_of_iterations += 1
        delta = 0
        for x in range(len(Board)):
            for y in range(len(Board[x])):
                if Board[x][y] == '.':
                    continue
                for s in Speeds():  # for each possible state in (x, y)
                    state = (x, y) + s
                    value = optPolicy(state, gamma)
                    delta = max(delta, (value[0] - readPolicyValue(state)))
                    MyPolicy[state] = value
        print(delta)
    print("Iterations: ", number_of_iterations)
    saveOtput(sys.argv[1])
