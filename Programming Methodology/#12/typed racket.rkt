#lang typed/racket

;;Zad 6

(: prefixes (All (A) (-> (Listof A) (Listof (Listof A)))))
(define (prefixes xs)
  (if (null? xs)
      '(())
      (cons  xs (prefixes (reverse (cdr (reverse xs)))))))


;; Zad 7

(: square (Integer -> Integer))
(define (square x) (* x x))