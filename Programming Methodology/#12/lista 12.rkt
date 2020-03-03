#lang racket


;;Zad 1

(define/contract (suffixes xs)
  (let ([a (new-∀/c 'a)])
    (-> (listof a) (listof (listof a))))
  (if (null? xs)
      null
      (cons xs (suffixes (cdr xs)))))

;;Zad 2

(define/contract (dist x y)
  (-> number? number? (lambda (x) (>= x 0)))
  (abs (- x y)))

(define/contract (average x y)
  (-> number? number? number?)
  (/ (+ x y) 2))

(define/contract (square x)
  (-> number? positive?)
  (* x x))

(define/contract (sqrt x)   ;;<--------------------------------------------
  (->i ([argument (>=/c 0)])
       [sqrt (argument) (and/c (>=/c 0)
                                 (if (<= 1 argument)
                                     (<=/c argument)
                                     (>=/c argument)))])
    
  ;; poprawienie przybliżenia pierwiastka z x
  (define (improve approx)
    (average (/ x approx) approx))
  
  ;; nazwy predykatów zwyczajowo kończymy znakiem zapytania
  (define (good-enough? approx)
    (< (dist x (square approx)) 0.0001))
  
  ;; główna procedura znajdująca rozwiązanie
  (define (iter approx)
    (cond
      [(good-enough? approx) approx]
      [else                  (iter (improve approx))]))
  
  (iter 1.0))

;;Zad 3

(define/contract (filter p xs)
  (let ([a (new-∀/c 'a)])
     (-> (-> a boolean?) (listof a) (listof a)))
  (if (null? xs)
      null
      (if (p (car xs))
          (cons (car xs) (filter p (cdr xs)))
          (filter p (cdr xs)))))


;;Zad 4

(define-signature  monoid^
  (( contracted
     [elem?    (-> any/c  boolean?)]
     [neutral  elem?]
     [oper     (-> elem? elem? elem?)])))

(define-unit monoid-list@
  (import)
  (export monoid^)

  (define (elem? e)
    (integer? e))

  (define neutral 0)

  (define (oper e1 e2)
    (+ e1 e2))

  )
(define-values/invoke-unit/infer monoid-list@)
(define m1 (oper 42 neutral))
(define m2 (elem? 20))
(define m3 neutral)

(require quickcheck)


(define/contract (append xs ys)
  (let ([a (new-∀/c 'a)])
    (-> (listof a) (listof a) (listof a)))
  (if (null? xs)
      ys
      (cons (car xs) (append (cdr xs) ys))))

(define/contract (map f xs)
  (let ([a (new-∀/c 'a)]
        [b (new-∀/c 'b)])
    (-> (-> a b) (listof a) (listof b)))
  (if (null? xs)
      null
      (cons (f (car xs))
            (map f (cdr xs)))))

;; funkcja map zachowuje długość
(quickcheck
 (property ([l (arbitrary-list arbitrary-symbol)]
            [p (arbitrary-procedure arbitrary-symbol arbitrary-symbol)])
           (eq? (length l) (length (map p l)))))

;; długość konkatenacji list to suma długości list wejściowych
(quickcheck
 (property ([l1 (arbitrary-list arbitrary-symbol)]
            [l2 (arbitrary-list arbitrary-symbol)])
           (eq? (length (append l1 l2)) (+ (length l1) (length l2)))))

;; rozdzielność append względem map
(quickcheck
 (property ([l1 (arbitrary-list arbitrary-symbol)]
            [l2 (arbitrary-list arbitrary-symbol)]
            [p (arbitrary-procedure arbitrary-symbol arbitrary-symbol)])
           (equal? (map p (append l1 l2)) (append (map p l1) (map p l2)))))



