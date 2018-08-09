#lang racket

(define (square x) (* x x))
(define (cube x) (* x x x))
 
{define (cube-root x) 
  {define (cube-root-iter x approx)

    (define (avg x y)
      (/ (+ (/ x (square y)) (* 2 y)) 3))
    
    (define (good? x approx)
      (< (abs(- (cube approx) x))0.0000001))

    [if(good? x approx)
       approx
       (cube-root-iter x (avg x approx))]}
  (cube-root-iter x 1.0)}

;; testy:

(define test1 (cube-root 0)) ;;0
(define test2 (cube-root (/ 1 8))) ;;ulamek +
(define test3 (cube-root (-(/ 1 8)))) ;;ulamek -
(define test4 (cube-root 9999999999)) ;;duza +
(define test5 (cube-root -9999999999)) ;;duza -
(define test6 (cube-root 1)) ;;1
(define test7 (cube-root 8)) ;;mala +
(define test8 (cube-root -8)) ;;mala -
