#lang racket

(define (square x) (* x x))

(define (avg x y)
  (/ (+ x y) 2))
 
{define (sqrt x) 
  {define (sqrt-iter x approx)
    
    (define (good? x approx)
      (<(abs(- (square approx) x))0.001))

    (define (improve x approx)
      (avg approx (/ x approx)))

    [if(good? x approx)
       approx
       (sqrt-iter x (improve x approx))]}
  (sqrt-iter x 1.0)}

