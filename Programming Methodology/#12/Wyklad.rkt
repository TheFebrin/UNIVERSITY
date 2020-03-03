#lang typed/racket

(: dist  (-> Real Real Real))
(define (dist x y)
  (abs (- x y)))

(: average (-> Real Real Real))
(define (average x y)
  (/ (+ x y) 2))

(: square (-> Real Real))
(define (square x)
  (* x x))

(: sqrt (-> Real Real))
(define (sqrt x)

  (: improve (-> Real Real))
  (define (improve approx)
    (average (/ x approx) approx))

  (: good-enough? (-> Real Boolean))
  (define (good-enough? approx)
    (< (dist x (square approx)) 0.0001))

  (: iter (-> Real Real))
  (define (iter approx)
    (cond [(good-enough? approx) approx]
          [else (iter (improve approx))]))
  (iter 1.0))



;;

(define-type Rat (Pairof Integer Integer))


;; drzewa


(define-type Leaf 'leaf)
(define-type (Node A) (List 'node A (Tree A) (Tree A)))
(define-type (Tree A) (U Leaf (Node A)))


(: leaf Leaf)
(define leaf 'leaf)

(: make-node (All (A) (-> A (Tree A) (Tree A) (Node A))))
(define (make-node v l r)
  (list 'node v l r))

(: node-left (All (A) (-> (Node A) (Tree A))))
(define (node-left t)
  (third t))

(: node-right (All (A) (-> (Node A) (Tree A))))
(define (node-right t)
  (fourth t))

(: node-val (All (A) (-> (Node A) A)))
(define (node-val t)
  (second t))

(define-predicate leaf? Leaf)
(define-predicate node? (Node Any))
(define-predicate tree? (Tree Any))

(: bst-find (-> Integer (Tree Integer) Boolean))
(define (bst-find x t)
  (cond [(leaf? t) false]
        [(= x (node-val t)) true]
        [(< x (node-val t)) (bst-find x (node-left t))]
        [else (bst-find x (node-right t))]))

