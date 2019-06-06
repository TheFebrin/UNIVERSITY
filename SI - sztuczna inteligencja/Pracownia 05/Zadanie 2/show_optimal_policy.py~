from collections import defaultdict as dd
import random

from turtle import *
import sys
GAMMA = 0.99

#####################################################
# turtle graphic
#####################################################
tracer(0,1)
ht()

BOK = 14
SX = -400
SY = 0
M = 8
MOVE_COST = 1.0

def sgoto(x,y):
    goto(SX+BOK*x + BOK/2, SY+BOK*y + BOK/2)

def kwadrat(x, y, kolor):
  fillcolor(kolor)
  pu()
  goto(SX + x * BOK, SY + y * BOK)
  pd()
  begin_fill()
  x += 1
  goto(SX + x * BOK, SY + y * BOK)
  y += 1
  goto(SX + x * BOK, SY + y * BOK)
  x -= 1
  goto(SX + x * BOK, SY + y * BOK)
  y -= 1
  goto(SX + x * BOK, SY + y * BOK)
  end_fill() 


def kolko(x, y, kolor):
  fillcolor(kolor)

  pu()
  goto(SX + x * BOK + BOK/2, SY + y * BOK + BOK/2)
  pd()
  begin_fill()
  circle(BOK/4)
  end_fill() 


#####################################################
DD = [-3,-2,-1,0,1,2,3]

B = []
task_file = sys.argv[1] 

for x in open(task_file):
    L = list(x.strip())
    B.append(L)


F = dd(lambda : '.')

states = []
oils = set()
start = None
ends = set()

for y in range(len(B)):
    for x in range(len(B[y])):
        f = B[y][x]
        F[x,y] = f
        s = (x,y)
        
        if f != '.':
            if f == 'o':
                oils.add(s)
            if f == 's':
                start = s
            if f == 'e':
                ends.add(s)
            states += [(s[0], s[1], vx, vy) for vx in DD for vy in DD]    

def show_track(B):
    for y in range(len(B)):
        for x in range(len(B[y])):
            if B[y][x] == '#':
                kwadrat(x,y,'gray')
            elif B[y][x] == 'e':
                kwadrat(x,y,'orange')
            elif B[y][x] == 's':
                kwadrat(x,y,'magenta')
            elif B[y][x] == 'o':
                kwadrat(x,y,'yellow')        
            else:
                kwadrat(x,y,'green')

                        
def show_path(positions, color):
    #tracer(1,1)
    sx,sy = positions[0]
    pu()
    sgoto(sx,sy)
    kolko(sx,sy, color)
    pd()
    
    for x,y in positions[1:]:        
        sgoto(x,y)
        kolko(x,y, color)

                    
#####################################################

DD = [-3,-2,-1,0,1,2,3]

policy = dd(lambda: (0,0))

policy_file = 'policy_for_' + task_file

for x in open(policy_file):
    L = x.split()
    x,y,d,v, dvx, dvy = map(int, L[:6])
    policy[x,y,d,v] = (dvx,dvy)
    
###################################################################

should_be = {
   'task1.txt' : 78.0,
   'task2.txt' : 33.79,
   'task3.txt' : 92.1,
   'task6.txt' : 30.0,
   'task8.txt' : 62.0,
   'task9.txt' : 61.0,
   'task10.txt': 74.5,
   'task11.txt': 60
}

show_track(B)

R = 20
U = []
for runs in range(R):
    x,y = start
    dx,dy = 0,0

    path = [(x,y)]
    cnt = 0
    t = 0
    utility = 0.0
    while t < 1000:
        if y < 0 or y >= len(B) or x < 0 or x >= len(B[y]) or B[y][x] == ".":
            utility -= 100 * GAMMA ** t
            break
        if  B[y][x] == "e":
            utility += 100 * GAMMA ** t
            break

        ddx,ddy = policy[x,y,dx,dy]
        if (x,y) in oils:
            ddx += random.choice([-1,0,1])
            ddy += random.choice([-1,0,1])
          
        dy += ddy
        dx += ddx

        if dx > 3: dx = 3
        if dy > 3: dy = 3
        if dx < -3: dx = -3
        if dy < -3: dy = -3         
        
        x += dx
        y += dy
        
        path.append( (x,y) )
        utility -= MOVE_COST * GAMMA ** t 

        t += 1
    
    print 'Path utility=', utility
    U.append(utility)
    show_path(path, (0.5 + 0.5 * random.random(), random.random(), random.random()))

expected_utility = sum(U) / len(U)
    
print 'Expected utility', expected_utility
if should_be[task_file] < expected_utility:
    print 'RESULT',task_file, '[OK]'
else:
    print 'RESULT', task_file, '[WARNING] EXPECTED UTILITY SHOULD BE GREATER THAN', should_be[task_file]
raw_input()    
