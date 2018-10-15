#lang racket

(define (node? t)
  (and (pair? t)
       (eq? (car t) 'node)))

(define (make-node v l p)
  (list 'node v l p))

(define leaf 'leaf)

(define t (make-node 11
                     (make-node 25
                                (make-node 43 leaf leaf)
                                (make-node 4 leaf leaf))
                     (make-node 584
                                (make-node 36 leaf leaf)
                                (make-node 71 leaf leaf))))

(define t2 (make-node 5
                      (make-node 7
                                 (make-node 1
                                            (make-node 9 leaf leaf)
                                            leaf)
                                 leaf)
                      (make-node 0 leaf leaf)))
                                
(define (leaf? t)
  (eq? t leaf))

(define (node-left t) (third t))
(define (node-right t) (fourth t))
(define (node-val t) (second t))

(define (DFS t)
  (if (leaf? t)
      0
      (+ 1 (DFS (node-left t)) (DFS (node-right t)))))

(define (relabel t i) ;;na lisciach
  (if (leaf? t)
      (cons i (+ i 1))
      (let*
        ([l (relabel (node-left t)  i)]
         [r (relabel (node-right t) (cdr l))])
        (cons (make-node (+ 1 i) (car l) (car r))
              (+ 1 (cdr l))))))


(define (flatten t)
  (define (flatt-app t list)
    (if (leaf? t)
        list
        (flatt-app (node-left t)
                   (cons (node-val t) (flatt-app (node-right t) list)))))
  (flatt-app t null))

        