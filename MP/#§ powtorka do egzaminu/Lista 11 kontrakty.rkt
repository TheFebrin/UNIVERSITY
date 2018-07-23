#lang racket

(require racket/contract)

(define/contract foo number? 42)

(define/contract (dist x y)
  (-> number? number? number?)
  (abs (- x y)))

(define/contract (average x y)
  (-> number? number? number?)
  (/ (+ x y) 2))

(define/contract (square x)
  (-> number? number?)
  (* x x))


(define/contract (inc n)
  (-> integer? integer?)
  (+ n 1))

(define/contract (append xs ys)
  (let ([a (new-∀/c 'a)])
    (-> (listof a) (listof a) (listof a)))
  (if (null? xs)
      ys
      (cons (car xs) (append (cdr xs) ys))))


;;Zad 1

(define/contract (suffixes xs)
  (let ([a (new-∀/c 'a)])
    (-> (listof a) (listof (listof a))))
  (if (null? xs)
      (list null)
      (cons xs (suffixes (cdr xs)))))
   