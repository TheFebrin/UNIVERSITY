#lang racket

(define (histogram-list l)
  (foldl (lambda (n l) (list-update l n (lambda  (k) (+ k 1))))
         (build-list (+ (apply max l) 1)
                     (lambda (k) 0))
         l))

(define (histogram-vec l)
  (define v (make-vector (+ (apply max l) 1) 0))
  (for-each (lambda (n)
              (vector-set! v n (+ 1 (vector-ref v n))))
            l)
  v)


    