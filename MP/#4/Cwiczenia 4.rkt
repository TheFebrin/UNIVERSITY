#lang racket

(define (leaf? x) ;;sprawdzamy czy jest lisciem
  (eq? x 'leaf))

(define leaf 'leaf) ;;zakladamy ze lisc jest nullem

(define (node? x) ;;sprawdzamy czy jest wierzcholkiem
  (= (length x) 4)
  (eq? (car x) 'node))

(define (node-val x) ;; wartosc wierzcholka
  (second x))

(define (node-left x) ;;lewy syn
  (third x))

(define (node-right x) ;;prawy syn
  (fourth x))

(define (make-node v l r) ;;konstruktor listy
  (list 'node v l r))

(define (tree? x)  ;;sprawdzamy czy x jest drzewem
  (or (leaf? x)   
      (and (node? x)  
           (number? (node-val x))
           (tree? (node-left x))
           (tree? (node-right x)))))

;;Drzewo BST

(define (bst-find x t)    ;; szukanie jakiegos elementu w drzewie BST
  (cond [(leaf? t) false]
        [(= x (node-val t)) true]
        [(< x (node-val t)) (bst-find (node-left t))]
        [(> x (node-val t)) (bst-find (node-right t))]))

(define (bst-insert x t) ;; wrzucanie elementu do drzewa
  (cond [(leaf? t) (make-node x leaf leaf)]
         [(< x (node-val t))
          (make-node (node-val t)
                     (bst-insert x (node-left t))
                     (node-right t))]
         [else
            (make-node (node-val t)
                     (node-left t)
                     (bst-insert x (node-right t)))]))


(define t (make-node 4
                     (make-node 2
                                (make-node 1 leaf leaf) (make-node 3 leaf leaf))
                     (make-node 5 leaf leaf)))

;;*** ZAD 4  ******************************************************************

(define (flatten-app t) ;; to jest slabe bo z appendem
  (if (leaf? t)
      '()
      (append (flatten-app (node-left t))
      (cons (node-val t) (flatten (node-right t))))))

(define (flatten t)   ;;ten lepszy
  (define (walk t acc)
    (if (leaf? t)
        acc
        (walk (node-left t) (cons (node-val t) (walk (node-right t) acc)))))
  (walk t '()))
