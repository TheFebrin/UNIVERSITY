from math import sin, cos, pi, floor

unit = 1.0/2**16
unit = unit * 10

A = 24 * unit
B = 36 * unit
T = 64 * unit
L = 20000 * unit 
F0,F1,F2 = 4 * unit, 12 * unit, 24 * unit

F2 = 50 * unit
T = 3*T

class State:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.v = 0.0
        self.d = pi/2
        
    def update(self, action):
        self.v -= F0 + F1 * self.v + F2 * self.v ** 2
        if self.v < 0:
            self.v = 0.0
        
        v = self.v
        
        if 'a' in action:
            self.v += A
        if 'b' in action:
            self.v -= B
            if self.v < 0:
                self.v = 0
        if 'l' in action:
            self.d -= T / (v*v + L)
        if 'r' in action:
            self.d += T / (v*v + L)
        
        self.x += v * cos(self.d)
        self.y += v * sin(self.d)
        
        
    def __str__(self):
        return 'St(x=%f, y=%f, d=%f, v=%f)' % (self.x, self.y, self.d, self.v)    
         
