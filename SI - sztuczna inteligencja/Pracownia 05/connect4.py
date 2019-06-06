import random
import sys

D = 7
H = 6

def four(x, y, dx, dy):
    return [ (x + i * dx, y + i * dy) for i in range(4)]
     
verticals   = [four(x, y, 0, 1) for x in range(D) for y in range(H - 4)]
horizontals = [four(x, y, 1, 0) for x in range(D - 4) for y in range(H)]
diagonals   = [four(x, y, 1, 1) for x in range(D - 4) for y in range(H - 4)]
diagonals  += [four(x, y, 1, -1) for x in range(D - 4) for y in range(4,H)]
all_fours = verticals + horizontals + diagonals

def is_winning(S):
    return S == ['o', 'o', 'o', 'o'] or S == ['#', '#', '#', '#']
    
class Board:
    def __init__(self):
        self.board = [['.'] * D for i in range(H+1)]
        self.cnt = 0
    
    def height(self, x):        
        return min(y for y in range(H+1) if self.board[y][x] == '.')
        
    def moves(self, player):
        hs = [(self.height(x), x) for x in range(D)]
        return [(player, x) for (h,x) in hs if h < H]

    def draw(self):
        bs = self.board[:-1]
        for raw in bs[::-1]:
            print (''.join(raw))
        print ('')
    
    def random_move(self, player):
        return player, random.choice(self.moves(player))[1]
        
    def do_move(self, m):
        player, x = m
        if player == 0:
            c = 'o'
        else:
            c = '#'
        self.board[self.height(x)][x] = c
        self.cnt += 1
    
    def undo_move(self, m):
        player, x = m    
        self.board[self.height(x)-1][x] = '.' 
        self.cnt -= 1
                       
    def get_fields(self, fs):
        res = []
        for x,y in fs:
            res.append( self.board[y][x])
        return res
        
    def end_of_game(self):
        if self.cnt == D * H:
            return True
        return self.victory()
        
    def victory(self):
        return any(is_winning(self.get_fields(fs)) for fs in all_fours)
    
player = 0
board = Board()

while(True):
    m = board.random_move(player)
    board.do_move(m)  
    board.draw()
    if board.victory():
        print ('The winner is: Player', player)        
        break
    if board.end_of_game():
        print ('Draw game')        
        break
            
    input()                      
    player = 1 - player


