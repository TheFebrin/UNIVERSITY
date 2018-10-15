#lang racket

;;*** PRZENUMEROWANIE LISCI W DRZEWIE ******************************

(define (node? t)
  (and (pair? t)
       (eq? (car t) 'node)))

(define (node-left t) (second t))
(define (node-right t) (third t))

(define (relabel t i)
  (if (not (node? t))
      (cons i (+ i 1))
      (let*
        ([l (relabel (node-left t)
                     i)]
         [r (relabel (node-right t)
                     (cdr l))])
        (cons (list 'node (car l) (car r))
              (cdr l)))))


;;*** round 2

(define a '(1 2 3))
(define b '(4 5 6))
(define c '(7 8 9))

(define (inf-append . args)
  (define (app-iter args acc)
     (if (null? args)
      acc
      (app-iter (cdr args) (append (car args) acc))))
  (app-iter args null))

(inf-append '(1 3 4) '(5 6 8) '(0 0 0) '( 0 0 7 2))
(inf-append a b c)