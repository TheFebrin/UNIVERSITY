#lang racket

(define (lcons x f)
  (cons x f))

(define (lhead l)
  (car l))

(define (ltail l)
  ((cdr l)))

(define (ltake n l)
  (if (or (null? n) (= n 0))
      null
      (cons (lhead l)
            (ltake (- n 1) (ltail l)))))

(define (lfilter p l)
  (cond [(null? l) null]
        [(p (lhead l))
         (lcons (lhead l)
                (lambda ()
                  (lfilter p (ltail l))))]
        (else (lfilter p (ltail l)))))

(define (lmap f . ls)
  (if (ormap null? ls)
      null
      (lcons (apply f (map lhead ls))
             (lambda ()
               (apply lmap (cons f (map ltail ls)))))))

(define (integers-from n)
  (lcons n (lambda () (integers-from (+ 1 n)))))

(define naturals (integers-from 0))

(define even-naturlas (lmap (lambda (x) (* x 2)) naturals))

(define (divisible? x y)
  (= (remainder x y) 0))

(define even-naturals2 (lfilter (lambda (x) (divisible? x 2)) naturals))

(define fib
         (lcons 0
                (lambda ()
                  (lcons 1
                         (lambda ()
                           (lmap + fib (ltail fib)))))))
