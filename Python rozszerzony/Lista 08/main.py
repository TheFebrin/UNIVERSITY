import numpy as np
import matplotlib.pyplot as plt
import os
import time


def play(width = 2, height = 2, steps=100):
    BOARD = np.random.choice([0, 1], width * height)
    BOARD = BOARD.reshape(height, width)

    dx = [1, -1, 0, 0, 1, 1, -1, -1]
    dy = [0, 0, 1, -1, 1, -1, 1, -1]

    def print_board(step):
        os.system('clear')
        print(step)
        for i in range(height):
            for j in range(width):
                # print(BOARD[i][j], end=' ')
                if BOARD[i][j]:
                    print('#', end=' ')
                else:
                    print('.', end=' ')
            print()
        time.sleep(0.5)

        # plt.imshow(BOARD)
        # plt.show()

    for no in range(steps):
        for i in range(height):
            for j in range(width):
                alive_n = 0
                for x in range(len(dx)):
                    new_x = i + dx[x]
                    new_y = j + dy[x]

                    if 0 <= new_x < height \
                        and 0 <= new_y < width \
                            and BOARD[new_x][new_y] == 1:
                        alive_n += 1


                if alive_n == 3 and BOARD[i][j] == 0:
                    BOARD[i][j] = 1

                if BOARD[i][j] == 1:
                    if alive_n != 2 and alive_n != 3:
                        BOARD[i][j] = 0
        print_board(no)
        




if __name__ == "__main__":
    # Better to use matplotlib.animation in print_board()
    play(10, 10, 100)