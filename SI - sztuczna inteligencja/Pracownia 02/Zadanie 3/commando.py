from os import system
import random

from turtle import ht, pu, pd, fd, bk, rt, lt, fillcolor, begin_fill, end_fill, clear, update, tracer, goto

BOK = 20
tracer(0, 1)
SX = -280
SY = 20
ht()

color_table = {
    '#': 'black',
    ' ': 'white',
    'S': 'yellow',
    'G': 'green'
}


def square(x, y, color):
  y = -y
  fillcolor(color)
  pu()
  goto(SX + x * BOK, SY + y * BOK)
  pd()
  begin_fill()
  for i in range(4):
    fd(BOK)
    rt(90)
  end_fill()


def mark(x, y, color):
  y = -y
  D = 5
  fillcolor(color)
  pu()
  goto(SX + x * BOK + D, SY + y * BOK - D)
  pd()
  begin_fill()
  for i in range(4):
    fd(BOK - 2 * D)
    rt(90)
  end_fill()


def draw(T, marks):
  # system('clear')
  for y in range(len(T)):
    for x in range(len(T[y])):
      square(x, y, color_table[T[y][x]])
      if (x, y) in marks:
        mark(x, y, marks[x, y])

  update()


class Maze:
  _dirs = {'U': (0, -1), 'D': (0, 1), 'R': (1, 0), 'L': (-1, 0)}

  def __init__(self, maze_str):
    self.m = []
    self.goals = set()
    self.starts = set()
    self.states = set()

    for x in maze_str.split('\n'):
      x = x.strip()
      if x:
        self.m.append(list(x))

    for y in range(len(self.m)):
      raw = self.m[y]
      for x in range(len(raw)):
        if self.m[y][x] == 'S':
          self.start = (x, y)
          self.starts.add((x, y))
        if self.m[y][x] == 'G':
          self.goals.add((x, y))
        if self.m[y][x] == 'B':
          self.start = (x, y)
          self.starts.add((x, y))
          self.goals.add((x, y))
        if self.m[y][x] != '#':
          self.states.add((x, y))

  def do(self, state, action):
    dx, dy = Maze._dirs[action]
    x, y = state
    if self.m[y + dy][x + dx] != '#':
      return (x + dx, y + dy)
    else:
      return state

  def draw(self, colors):
    draw(self.m, colors)

  def draw_set(self, S, c):
    self.draw(dict((s, c) for s in S))

  def do_belief(self, states, action):
    return {self.do(s, action) for s in states}


maze_str = """
######################
# G   G              #
#    #       #S      #
#  S #       #       #
######### ############
#    G#           G  #
##   ##    ###########
#    #       S       #
# ## ###########     #
#    #            S  #
#S         ####      #
######################
"""

#LLUULLULLLLURRULUUUULLLLLLLLRRRRR

maze = Maze(maze_str)
states = maze.starts
while True:
  print("Type commands (UDLR Wn):")
  commands = input()

  if commands[0] == 'W':  # random walk
    n = int(commands[1:])
    commands = []
    for i in range(n):
      commands.append(random.choice('UDLR'))

  for c in commands:
    maze.draw_set(states, 'orange')
    states = maze.do_belief(states, c)
    maze.draw_set(states, 'orange')
