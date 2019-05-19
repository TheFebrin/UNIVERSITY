import reversi
import time


def PLAY_GAME(no, debug, game_mode, deep):
    '''
    # = black piece - random_player
    o = white piece - our bot
    Result is + for whites
    '''

    white_win, black_win = 0, 0
    for game_no in range(1, no + 1):
        player = True
        B = reversi.Board(debug)

        cnt = 1
        while True:
            # B.draw()
            if debug:
                print(f'Move: {cnt}')
                B.draw()
                B.show()

            if player:
                m = B.random_move(player)
                B.do_move(m, player)
            else:
                if game_mode == 1:
                    m = B.random_move(player)
                    B.do_move(m, player)
                if game_mode == 2:
                    best_move = B.find_best(deep, player)
                    B.do_move(best_move, player)
                    # print('Min max best = ', best_move)

            player = not player

            if debug:
                # time.sleep(0.01)
                input()

            if B.terminal():
                break
            cnt += 1

        if debug:
            print('End of game')
            B.draw()
            B.show()
            input()

        if B.result() > 0:
            white_win += 1

        if B.result() < 0:
            black_win += 1

        # B.draw()

        print(f'Game: {game_no}, result: {B.result()}')
        # B.finish()
    print('-' * 20)
    print(f'Whites won {white_win} / {no} games')
    print(f'It is : {white_win / (white_win + black_win) * 100}%')


if __name__ == "__main__":
    print('\nHow many games? ', end=' ')
    no = int(input())

    print('\n`Y` to debug mode, `Enter` to skip. ', end=' ')
    debug = False
    if input() == 'Y':
        debug = True

    print('\nPick strategy:')
    print('1. Random.')
    print('2. Alpha-Beta pruning')
    print('Your choise: ', end=' ')
    game_mode = int(input())

    depth = 0
    if game_mode == 2:
        print('\nSelect deepness of search: ', end=' ')
        depth = int(input())
    print('\n\n')

    start = time.time()
    PLAY_GAME(no, debug, game_mode, depth)
    print(f'\nTIME: {time.time() - start}')
