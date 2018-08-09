#lang racket


(define (square x) (* x x))
(define (SquarePlus x y) (+ (square x) (square y) ) )
(define (two-greatest x y z)
  (cond [(>= x y z) (SquarePlus x y)]
        [(>= y x z) (SquarePlus x y)]
        [(>= x z y) (SquarePlus x z)]
        [(>= z x y) (SquarePlus x z)]
        [(>= y z x) (SquarePlus y z)]
        [(>= z y x) (SquarePlus y z)]
        )
  )


(define (a-plus-abs-b a b)
  (  (if (> b 0) + -) a b)
  )

(define (greater a b) (if (> a b) a b))

(define (test x y)
  (if (= x 0) 0 y)
  )

(define (power-to-close b n) (define (powerC b n e)  (if(> (expt b e) n)
                                   e (powerC b n (+ 1 e))
                           )
  )
  (powerC b n 0)
  )



  


#| (/ (+ 5 (+ 4 (- 2 (- 3(+ 6 4/5)))))
     (* 3 (- 6 2) (- 2 7)))
|#