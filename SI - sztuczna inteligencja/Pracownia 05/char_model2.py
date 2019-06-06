from math import sin, cos, pi, floor

MAX_D = 16
MAX_V = 4
A = 1.0 / MAX_V

class State:
    def __init__(self, x, y, d=0, v=0):
        self.x = x
        self.y = y
        self.d = d
        self.v = v
        
    def update(self, action):
        if 'a' in action:
            self.v += 1
            if self.v > MAX_V:
                self.v = MAX_V
        if 'b' in action:
            self.v -= 1
            if self.v < 0:
                self.v = 0
        if 'l' in action:
            self.d = (self.d + 1) % MAX_D
        if 'r' in action:
            self.d = (self.d - 1) % MAX_D
        
        v = self.v
        direction = 1.0 * self.d / MAX_D * 2 * pi
        
        self.x += A * v * cos(direction)
        self.y += A * v * sin(direction)
        
    def abstract(self):
        x = floor(self.x)
        y = floor(self.y)
        
        return x,y,self.d,self.v
        
    def __str__(self):
        return 'St(x=%f, y=%f, d=%f, v=%f, ABS=%s)' % (self.x, self.y, self.d, self.v, str(self.abstract()))    
         
