#lang racket

;;***  ZAD 1. KURWY HETMANY ****************************************

(define (concatMap f xs)
  (if (null? xs)
      null
      (append (f (car xs)) (concatMap f (cdr xs)))))

(define (from-to s e)
  (if (= s e)
      (list s)
      (cons s (from-to (+ s 1) e))))


(define (queens board-size)
  ;; Return the representation of a board with 0 queens inserted
  
  (define (empty-board) '())
  ;; Return the representation of a board with a new queen at
  ;; (row, col) added to the partial representation `rest'
  (define (adjoin-position row col rest)
    (cons (cons col row) rest))
  
  (define (col queen-setup-pair) ;; column selector
    (car queen-setup-pair))
  
  (define (row queen-setup-pair) ;; row selector
    (cdr queen-setup-pair))
    
  ;; Return true if the queen in k-th column does not attack any of
  ;; the others
  
  (define (safe? k positions)
  
    (define (check? lista akt k)
      (cond [(null? lista) true]
            [(or
              (=  akt (cdar lista))
              (= (+ (cdar lista) (caar lista)) (+ k akt))
              (= (- (caar lista) (cdar lista)) (- k akt))
              )
             false]
            [else (check? (cdr lista) akt k)]))
  
    (check?  (cdr positions) (cdar positions) k))

      

  ;; Return a list of all possible solutions for k first columns

  (define (queen-cols k)
    (if (= k 0)
        (list (empty-board))
        (filter
         (lambda (positions) (safe? k positions))
         (concatMap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (from-to 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))

(define test1 (queens 4)) ;; wynik to 2
(define test2 (queens 5)) ;; wynik to 10
(define test3 (queens 6)) ;; 4
(define test4 (queens 8)) ;; 92

; https://pl.wikipedia.org/wiki/Problem_ośmiu_hetmanów ;



;;*** ZAD 3  **************************************************************

(define (btree? t)
  (or (eq? t 'leaf)
      (and (list? t)
           (= 4 (length t))
           (eq? (car t) 'node)
           (btree? (caddr t)))))

(define (leaf? t)
  (eq? t 'leaf))

(define leaf 'leaf)

(define (make-node val left right)
  (list 'node val left right))

(define (node-val t)
  (second t))

(define (node-left t)
  (third t))

(define (node-right t)
  (fourth t))

(define (mirror t)
  (if (leaf? t)
      'leaf
      (make-node
       (node-val t)
       (mirror (node-right t))
       (mirror (node-left t)))))


;;*** ZAD 4  **************************************************************


(define (flatten t)
  (define (tree-flatt acc t)
    (if (leaf? t)
        acc
        (tree-flatt
         (cons (node-val t) (tree-flatt acc (node-right t))) ;; <- new acc
         (node-left t))))
  (tree-flatt '() t))
           

;;*** ZAD 5  **************************************************************

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


(define (list->tree l)
  (define (create-tree t l)
    (if (null? l)
        t
        (create-tree (bst-insert (car l) t) (cdr l))))
  (create-tree 'leaf l))

(define (tree-sort l)  ;; <- sortowanie listy wrzucajac ja w drzewo
  (flatten (list->tree l)))

;;*** ZAD 6  **************************************************************

(define tree (list->tree '(8 3 1 4 10 14 13 20)))

(define (bst-find x t)    ;; szukanie jakiegos elementu w drzewie BST
  (cond [(leaf? t) false]
        [(= x (node-val t)) true]
        [(< x (node-val t)) (bst-find x (node-left t))]
        [(> x (node-val t)) (bst-find x (node-right t))]))

;; jest w notatkach u Karola xd

(define (square x) (* x x))

(define (tree-map f t)
  (if (leaf? t)
      'leaf
      (make-node (f (node-val t))
                 (tree-map f (node-left t))
                 (tree-map f (node-right t)))))
      