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
        while cnt:
            # B.draw()
            if cnt % 16 == 0:
                print(f'{cnt / 64 * 100}%')
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
            B.draw()
            B.show()
            input()

        if B.result() > 0:
            white_win += 1

        if B.result() < 0:
            black_win += 1

        print(f'Game: {game_no}, result: {B.result()}')

    print(f'Overall whites won: {white_win / (white_win + black_win) * 100}%')


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

    print('\nSelect deepness of search: ', end=' ')
    deep = int(input())
    print('\n\n')

    PLAY_GAME(no, debug, game_mode, deep)
