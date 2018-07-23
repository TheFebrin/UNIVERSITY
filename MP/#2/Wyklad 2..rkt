#lang racket
(define (inc i) (+ i 1))

(define (dist x y) (abs(- x y)))

(define (cube x) (* x x x))

(define (fact n) ;; silnia 1
  [if(= n 0) 1
     (* n (fact (- n 1)))])

(define (fact2 n) ;; silnia 2
(define (fact-iter n i p)
  [if(= n i)
     p
     (fact-iter n (inc i) (* p (inc i)))])
  (fact-iter n 0 1))

(define (fib n) ;; n-ty wyraz ciagu fibonaciego
  (cond [(= n 0) 0]
        [(= n 1) 1]
        [else (+ (fib(- n 1)) (fib(- n 2)))]))

(define (sum-ints s e) ;; slabnia
  [if(> s e)
  0
  (+ s (sum-ints (inc s) e))])

(define (sum-cubes s e)  ;; slabnia szescianow
  [if(> s e)
     0
     (+ (cube s) (sum-cubes (inc s) e))])

(define (sum-pi n e) 
  [if(> n e)
     0
     (+ (/ 1(* n (+ 2 n))) (sum-pi (+ n 4) e))])

(define (sum term next s e) ;; ogolna suma
  [if(> s e)
     0
     (+ (term s) (sum term next (next s) e))])

(define (sum-pi2 n e)
  (define (sum-pi-term s)
    (/ 1(* s (+ s n))))
    (sum sum-pi-term (lambda(s) (+ s 4)) n e))

(define kwadrat (lambda (x) (* x x)))
    


(define (close-enough? x y)
  (< (dist x y) 0.00001))


(define (fix-point f x0)
  (let ((x1 (f x0)))
  (if(close-enough? x0 x1)
     x0
     (fix-point f x1))))


(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2)))


(define (sqrt x)
  (fix-point (average-damp (lambda (y)
                             (/ x y))) 1.0))

(define (deriv f)
  (let ((dx 0.000001))
    (lambda (x) (/ (-(f (+ x dx)) (f x)) dx))))

(define (newton-transform f)
  (lambda (x)
    (- x
       (/ (f x)
          ((deriv f) x)))))

