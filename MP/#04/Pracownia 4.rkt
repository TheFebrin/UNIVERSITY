#lang racket
; ∆ Dawid Dieu © ® ;


(define (inc n)
  (+ n 1))

;;; ordered elements
(define (make-elem pri val)
  (cons pri val))

(define (elem-priority x)
  (car x))

(define (elem-val x)
  (cdr x))

;;; leftist heaps (after Okasaki)

;; data representation
(define leaf 'leaf)

(define (leaf? h) (eq? 'leaf h))

(define (hnode? h)
  (and (list? h)
       (= 5 (length h))
       (eq? (car h) 'hnode)
       (natural? (caddr h))))

;; wierzcholek = (symbol, element, ranga, l syn, p syn)
;ranga lewego >= prawego

(define (make-node elem heap-a heap-b); ranga nowego to ranga prawego poddrzewa + 1
  (if (> (rank heap-b) (rank heap-a))
      (list 'hnode elem (inc (rank heap-b)) heap-b heap-a)
      (list 'hnode elem (inc (rank heap-a)) heap-a heap-b)))
         

(define (node-elem h)
  (second h))

(define (node-left h)
  (fourth h))

(define (node-right h)
  (fifth h))

(define (hord? p h)
  (or (leaf? h)
      (<= p (elem-priority (node-elem h)))))

(define (heap? h)
  (or (leaf? h)
      (and (hnode? h)
           (heap? (node-left h))
           (heap? (node-right h))
           (<= (rank (node-right h))
               (rank (node-left h)))
           (= (rank h) (inc (rank (node-right h))))
           (hord? (elem-priority (node-elem h))
                  (node-left h))
           (hord? (elem-priority (node-elem h))
                  (node-right h)))))

(define (rank h)
  (if (leaf? h)
      0
      (third h)))

;; operations

(define empty-heap leaf)

(define (heap-empty? h)
  (leaf? h))

(define (heap-insert elt heap)
  (heap-merge heap (make-node elt leaf leaf)))

(define (heap-min heap) ;; zwraca element z heap
  (node-elem heap))

(define (heap-pop heap)
  (heap-merge (node-left heap) (node-right heap)))

(define (heap-merge h1 h2)  ; <- uzupelnij
  (cond
   [(leaf? h1) h2]
   [(leaf? h2) h1]
   [else
    (let ([el (heap-min h1)]
          [er (heap-min h2)])
      (if (< (elem-priority el) (elem-priority er)) ; elem z h1 jest mniejszy
          (make-node el (node-left h1)
                     (heap-merge (node-right h1) h2))
        ; elem z h2 jest mniejszy
          (make-node er (node-left h2)
                     (heap-merge (node-right h2) h1))))]))
      
  
    


;;; heapsort. sorts a list of numbers.
(define (heapsort xs)
  (define (popAll h)
    (if (heap-empty? h)
        null
        (cons (elem-val (heap-min h)) (popAll (heap-pop h)))))
  (let ((h (foldl (lambda (x h)
                    (heap-insert (make-elem x x) h))
            empty-heap xs)))
    (popAll h)))

;;; check that a list is sorted (useful for longish lists)
(define (sorted? xs)
  (cond [(null? xs)              true]
        [(null? (cdr xs))        true]
        [(<= (car xs) (cadr xs)) (sorted? (cdr xs))]
        [else                    false]))

;;; generate a list of random numbers of a given length
(define (randlist len max)
  (define (aux len lst)
    (if (= len 0)
        lst
        (aux (- len 1) (cons (random max) lst))))
  (aux len null))


;;*** TESTY ***************************************

(define x0 (list 9 9 7))
(define x (randlist 10 200))
(define x2 (list 2 2 2 2 2 2 2 2 2 2))
(define x3 (randlist 10 500))

(display x0)(newline)
(sorted? x0)

(display x)(newline)
(heapsort x)
(sorted? (heapsort x))

(display x2)(newline)
(sorted? (heapsort x2))

(display x3)(newline)
(heapsort x3)
(sorted? (heapsort x3))

