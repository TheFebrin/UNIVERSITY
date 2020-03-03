#lang racket

(require compatibility/mlist)

(define l1 (mlist 1 2 3 4))

(define l2 (mlist 5 6 7 8))


;; Zadanie 2
(define (make-cycle l )
  (set-mcdr! (mlist-tail l 1)  l))


;; Zadanie 3 z liniową pamięcią
(define (has-cycle? x)
  (define (helper x acc)
    (cond
      ((null? x) #f)
      ((member (mcar x) acc) #t)
      (else (helper (mcdr x) (cons (mcar x) acc)))))
  (helper x null))



(define (make-counter)
  (let [(counter 0)]
    (cons
     (lambda ()(begin (set! counter (+ 1 counter)) counter))  ;;next
     (lambda () (set! counter -1))))) ;;reset

(define a (make-counter))

(define next (car a))