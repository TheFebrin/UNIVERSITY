#lang racket

;;*** PRZENUMEROWANIE LISCI W DRZEWIE ******************************

(define (node? t)
  (and (pair? t)
       (eq? (car t) 'node)))

(define (node-left t) (second t))
(define (node-right t) (third t))

(define (relabel t i)
  (if (not (node? t))
      (cons i (+ i 1))
      (let*
        ([l (relabel (node-left t)
                     i)]
         [r (relabel (node-right t)
                     (cdr l))])
        (cons (list 'node (car l) (car r))
              (cdr l)))))


;;*** LENIWE LISTY, (STRUMIENIE LICZB) ******************************S

(define (lcons x f)
  (cons x f))

(define (lhead l)
  (car l))

(define (ltail l)
  ((cdr l)))

(define (nats-from m)
  (lcons
   m
   (lambda () (nats-from (+ m 1)))))

(define nats
  (nats-from 0))

(define (take n l)
  (if (or (null? l) (= n 0))
      null
      (cons (lhead l)
            (take (- n 1) (ltail l)))))

(define (filter p l)
  (cond [(null? l) null]
        [(p (lhead l))
         (lcons (lhead l)
                (lambda ()
                  (filter p (ltail l))))]
        [else (filter p (ltail l))]))

(define (prime? n)
  (define (div-by m)
    (cond [(= m n) true]
          [(= (modulo n m) 0) false]
          [else (div-by (+ m 1))]))
  (if (< n 2)
      false
      (div-by 2)))


;;*** Zad 1 STRUMIEN FIBONACCIEGO ***********************************

(define (fibs-from m n)
  (lcons
   m
   (lambda () (fibs-from n (+ m n)))))

(define fibs
  (fibs-from 1 1))

;;STRUMIEN LICZB CALKOWITYCH

(define (ints-from m)
  (lcons
   m
   (if (>= m 0)
       (lambda () (ints-from (- (+ m 1))))
       (lambda () (ints-from (- m))))))

(define ints
  (ints-from 0))





