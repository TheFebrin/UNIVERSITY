import math
import time 

def perfect_im(n):
    res = []    
    for i in range(1,n):
        s = 0
        for j in range(1,i):
            if not i%j :
                s += j
        if s == i:
            res.append(i)
    return res

def perfect_lc(n):
    return [x for x in range(1, n) if x == sum([y for y in range(1,x) if not x % y])]

def is_perfect(n):
    return n == sum(list(filter(lambda x: not n % x, range(1,n))))

def perfect_fun(n):
    return list(filter(is_perfect, range(1, n)))

N = 10000
print(f"Czas dla wersji imperatywnej ", end = "")
t = time.time()
perfect_im(N)
t2 = time.time() - t
print(t2)

print(f"Czas dla wersji list składanych ", end = "")
t = time.time()
perfect_lc(N)
t2 = time.time() - t
print(t2)

print(f"Czas dla wersji funkcyjnej ", end = "")
t = time.time()
perfect_fun(N)
t2 = time.time() - t
print(t2)