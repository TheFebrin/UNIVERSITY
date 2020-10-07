from itertools import permutations
from turtle import *
import random
import time
import math
import numpy as np

tracer(0,1)

colors = [
   (1,0.3,0),
   (0.5, 1, 0.1),
   (1.0,0.9,0),
   (0, 0.3, 1.0),
   (1.0, 0.0, 0.9)
]

K = len(colors)

def circle_c(r):
    lt(90)
    #pu()
    bk(r/2)
    #pd()
    circle(r)
    #pu()
    fd(r/2)
    #pd()
    rt(90)

def draw_points(ps, col):
  pu()
  fillcolor(col)
  for p in ps:
    begin_fill()
    goto(*p)
    circle_c(10)
    end_fill()
  pd()


def draw_c(cs):
  pu()
  A = 0.7
  for i in range(len(colors)):
      r, g, b = colors[i]
      c = A * r, A * g,  A * b
      fillcolor(c)
      p = cs[i]
      begin_fill()
      goto(*p)
      circle_c(10)
      end_fill()
  pd()


def point_group(x, y, delta, M, N):
    res = []
    for i in range(N):
        x0, y0 = x, y
        for j in range(M):
            x0 += (2 * random.random() - 1) * delta
            y0 += (2 * random.random() - 1) * delta
        res.append( np.array([x0, y0]))
    return res

def take(points):
    points = points[:]
    random.shuffle(points)
    return points[:K]

def dist(p1, p2):
    d = p1 - p2
    return d.dot(d) ** 0.5

def best_class(p, cs):
    candidates = [ (dist(p, cs[i]), i) for i in range(len(cs))]
    return min(candidates)[1]

def initial_points():
    points = []
    for i in range(K):
        x = random.randint(-200, 200)
        y = random.randint(-200, 200)
        points += point_group(x, y, 6, 55, random.randint(10, 20))
    return points

points = initial_points()
draw_points(points, (0.8, 0.8, 0.8))




def check_command():
    command = input()
    if command in ['new', 'res', 'restart']:
        if command == 'new':
            points[:] = initial_points()
        clear()
        centroids[:] = take(points)
        draw_points(points, (0.8, 0.8, 0.8))
        draw_c(centroids)

centroids = take(points)

while True:
    draw_c(centroids)
    check_command()

    bc = []
    for p in points:
        bc.append(best_class(p, centroids))

    clear()

    for i in range(K):
        ps = [points[j] for j in range(len(points)) if bc[j] == i]
        draw_points(ps, colors[i])
    draw_c(centroids)

    #check_command()
    clear()

    for i in range(K):
        ps = [points[j] for j in range(len(points)) if bc[j] == i]
        draw_points(ps, colors[i])
        centroids[i] = sum(ps, np.array([0,0])) / len(ps)
    update()



input()
