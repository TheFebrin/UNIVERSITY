#lang racket

;; definiujac dwie reprezentacje punktow na osi uzywamy unikalnych
; dla nich nazw, aby byly dla nas rozroznialne

(define (make-rect x y)
  (list'rect x y))

(define (make-circ d a)
  (list 'circ d a))

;; uwaga na tego cwaniaka

''4
(quote (quote 4))
'(quote 4)


;; piszemy se drzewo

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


(define t (make-node 4 (make-node 3 (make-node 1 leaf leaf) leaf) (make-node 7
                     leaf leaf)))

;; Kodowanko huffmana     -SKOPIOWAC KOD Z WYKLADU

(define (concat-map f cs)
  (apply append (map f cs)))


(define (ord key priority)
  (cons key priority))

(define (ord? val)
  (and (pair? val)
       (integer? (cdr val))))

(define (ord-priority val)
  (cdr val))

(define (ord-key val)
  (car val))

;; priority queues, aka heaps
;; trivial implementation using ordered lists

(define empty-heap null)

(define (heap-empty? h)
  (null? h))

(define (heap-insert elt h)
  (if [or (null? h)
          (< (ord-priority elt)
             (ord-priority (car h)))]
      (cons elt h)
      (cons (car h) (heap-insert elt (cdr h)))))

(define (heap-min h)
  (car h))

(define (heap-pop h)
  (cdr h))

;; reprezentacja drzewa kodowego

(define (htleaf c)
  (list 'htleaf c))

(define (htleaf-sym t)
  (cadr t))

(define (htleaf? t)
  (and (list? t)
       (= (length t) 2)
       (eq? (car t) 'htleaf)))

(define (htnode t1 t2)
  (list 'htnode t1 t2))

(define (htnode-left t)
  (cadr t))

(define (htnode-right t)
  (caddr t))

(define (htnode? t)
  (and (list? t)
       (= 3 (length t))
       (eq? (car t) 'htnode)))


(define plist '((a . 10) (b . 1) (c . 6) (d . 5) (e . 3) (f . 6)))

;;; lista par jako słownik

(define empty-dict null)

(define (dict-insert k v d)
  (cons (cons k v) d))

(define (dict-find k d)
  (cond [(null? d) false]
        [(eq? (caar d) k) (car d)]
        [else (dict-find k (cdr d))]))


;; tworzenie drzewa kodowego
;; xs -- lista par znak-częstość występowania
(define (make-code-tree xs)
  (define (convert-list xs h)
    (if (null? xs)
        h
        (let ((s (caar xs))
              (f (cdar xs)))
          (convert-list (cdr xs)
                        (heap-insert (ord (htleaf s) f) h)))))
  (define (merge-elems e1 e2)
    (let ((tr (htnode (ord-key e1) (ord-key e2)))
          (fr (+ (ord-priority e1) (ord-priority e2))))
      (ord tr fr)))
  (define (handle-pqueue h)
    (let ((e1 (heap-min h))
          (h1 (heap-pop h)))
      (if (heap-empty? h1)
          (ord-key e1)
          (let* ((e2 (heap-min h1))
                 (h2 (heap-pop h1))
                 (hr (heap-insert (merge-elems e1 e2) h2)))
            (handle-pqueue hr)))))
  (handle-pqueue (convert-list xs empty-heap)))

;;; słownik z drzewa kodowego Huffmana

(define (code-tree->dict t)
  (define (aux t rcpref d)
    (if (htleaf? t)
        (dict-insert (htleaf-sym t) (reverse rcpref) d)
        (aux (htnode-right t)
             (cons 1 rcpref)
             (aux (htnode-left t)
                  (cons 0 rcpref)
                  d))))
  (aux t null empty-dict))

;; kodowanie listy symboli

(define (encode symlist dict)
  (let ((code-sym
         (lambda (s)
           (let ((kv (dict-find s dict)))
             (if kv
                 (cdr kv)
                 (error "Unknown symbol" s))))))
    (concat-map code-sym symlist)))

;; dekodowanie

(define (decode bitlist tree)
  (define (dec-sym bitlist tree)
    (cond [(htleaf? tree)
           (cons (htleaf-sym tree) bitlist)]
          [(null? bitlist)
           (error "Stream terminated prematurely")]
          [(= 0 (car bitlist))
           (dec-sym (cdr bitlist) (htnode-left tree))]
          [(= 1 (car bitlist))
           (dec-sym (cdr bitlist) (htnode-right tree))]))
  (define (aux bitlist)
    (if (null? bitlist)
        null
        (let ((sb (dec-sym bitlist tree)))
          (cons (car sb) (aux (cdr sb))))))
  (aux bitlist))
          






          
     



