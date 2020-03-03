#lang racket

(define (my-cons x y)
  (define (set-x! v) (set! x v))
  (define (set-y! v) (set! y v))
  (define (dispatch m)
    (cond [(eq? m 'car) x]
          [(eq? m 'cdr) y]
          [(eq? m 'set-car!) set-x!]
          [(eq? m 'ser-cdr!) set-y!]
          (else (error "dupa: " m))))
  dispatch)

(define (my-car z) (z 'car))
(define (my-cdr z) (z 'cdr))

(define (my-set-car! z new-val)
  ((z 'set-car!) new-val)
  z)

(define (my-set-cdr! z new-val)
  ((z 'set-cdr!) new-val)
  z)