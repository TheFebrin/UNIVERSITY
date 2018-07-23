#lang racket
;*** PROCEDURKI  ***********************************

(define (square x) (* x x))

(define l1 (list 1 2 3 4))
(define l2 (list 4 8 12 16))

(define (append l1 l2)
  (if(null? l1)
     l2
     (cons (car l1) (append (cdr l1) l2))))

(define (map f l)
  (if (null? l)
      '()
      (cons (f (car l)) (map f (cdr l)))))
      
(define (concat l)
  (if (null? l)
      '()
      (append (car l) (concat (cdr l)))))


;*** ZAD 3  **** wektor inaczej *********************************

(define (make-point a b)  ;; PUNKT
  (cons a b))

(define (point? p)
  (pair? p))

(define (point-x p)
  (car p))

(define (point-y p)
  (cdr p))
;--------------------------------
(define (make-vect p d len) ;;Wektor
  (cons p (cons d (cons len null))))

(define (vect-point v)
  (car v))

(define (vect-deg v)
  (car (cdr v)))

(define (vect-len v)
  (car (cdr (cdr v))))

(define (vect-begin v)
  (car v))

(define (vect-end v)
  (make-point
   (* (vect-len v) (cos (vect-deg v)))
   (* (vect-len v) (sin (vect-deg v)))))

(define (vect-scale v k)
  (make-vect
   (vect-point v)
   (vect-deg v)
   (* (vect-len v) k)))
                    
#|
(define V (make-vect (make-point 1 1) (/ pi 2) 10))
(display "Vector: ")(display V)(newline)
(display "Vect-point: ")(vect-point V)
(display "Vect-deg: ")(vect-deg V)
(display "Vect-len: ")(vect-len V)

(display "Vect-begin: ")(vect-begin V)
(display "Vect-end: ")(newline)(vect-end V)
(display "Vect-scale x5: ")(vect-scale V 5)
|#

;***  ZAD 4 ******** procedura reverse ******************************

(define (reverse l)
  (if(null? l)
     null
     (append (reverse (cdr l)) (list(car l)))))

(define (reverse-iter l)
  (define (iter l l2)
    (if (null? l)
        l2
        (iter (cdr l) (cons (car l) l2))))
  (iter l null))
        

   
;***  ZAD 5 ******** procedura insert ******************************

(define (insert n xs)
  (cond [(null? xs) (append xs (cons n '()))]
        [(< n (car xs)) (cons n xs)]
        [else  (cons (car xs) (insert n (cdr xs)))]))
 
;∆∆∆∆∆ INSERT SORT ∆∆∆∆∆∆
(define p '( 13 11 7 5 3 2))

(define (insert-sort xs)
    (define (sort xs ys)
      (if (null? xs)
          ys
          (sort (cdr xs) (insert (car xs) ys))))
  (sort xs '()))

;*** ZAD 6 **** permutacje listy **********************************

(define (permi l)
  (if (null? l)
      '(())
      (concat (map (lambda (zs) (insert (car l) zs))
                   (permi (cdr l))))))
      

  
 
      
  
