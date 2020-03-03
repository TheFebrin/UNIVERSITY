import random
import os
import time
import copy

N, M = 15, 30
PLANSZA = [[random.randint(0, 1) \
           for i in range(M)]
           for j in range(N)]

def wypisz():
    os.system('clear')
    for row in PLANSZA:
        for x in row:
            print(['.', '#'][x],end=' ')
        print()

def ewolucja():
    global PLANSZA
    dx = [1, -1, 0, 0, 1, -1, -1, 1]
    dy = [0, 0, 1, -1, 1, 1, -1, -1]
    PLANSZA2 = copy.deepcopy(PLANSZA)
    for x in range(N):
        for y in range(M):
            alive = 0
            for k in range(len(dx)): # patrzymy na 8 sasiadow
                new_x = x + dx[k]
                new_y = y + dy[k]
                if 0 <= new_x < N and 0 <= new_y < M: # jak jest w planszy
                    if PLANSZA[new_x][new_y] == 1: # i jest zywy
                        alive += 1

            if PLANSZA[x][y] == 0: # martwa
                if alive == 3: # jesli ma 3 zywych sasiadow
                    PLANSZA2[x][y] = 1
            else: # zywa
                if alive not in [2, 3]: # liczba zywych inna niz 2 lub 3
                    PLANSZA2[x][y] = 0

    PLANSZA = PLANSZA2

if __name__ == '__main__':
    '''
    GLOWNA FUNKCJA
    '''

    for _ in range(1000):
        wypisz()
        ewolucja()
        time.sleep(0.5)
