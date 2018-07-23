#lang racket




(define (lazy-cons x f)
  (cons x f))

(define (nats-from m)
    (lazy-cons
     m
     (lambda () (nats-from (+ m 1)))))

(define nats
  (nats-from 0))

(define (take n l)
  (cond [(null? l) null]
        [(= n 0) null]
        [else
         (cons (car l) (take (- n 1) ((cdr l))))]))

(define (filter p l)
  (cond [(null? l) null]
        [(p (car l)) (lazy-cons (car l)
                                (lambda () (filter p ((cdr l)))))]
        [else
         (filter p ((cdr l)))]))


(define (prime? n)
  (define (div-by m)
    (cond [(= m n) true]
          [(= (modulo n m) 0) false]
          [else
           (div-by (+ m 1))]))
  (if (< n 2)
      false
      (div-by 2)))


           