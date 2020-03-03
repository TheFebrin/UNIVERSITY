;_; Dejwo to ziomal ;_; 
#lang racket

;***  ĆWICZENIE 1  ****** wymierna jako lista 2-elementowa ***********

(define (make-rat n d) ;; <-- konstruktor
  (let ((c (gcd n d)))
    (cons (/ n c) (cons (/ d c) null))))

(define (rat-num w);; <-- selektor licznika
  (car w))

(define (rat-den w) ;; <- selektor mianownika
  (car (cdr w)))

(define (rat? w) ;; <-- predykat
    (and(pair? w) ;;jest para
      (not (= (rat-den w) 0)))) ;;licznik != 0

#|
(define half(make-rat 4 8))
(display half)(newline)
(rat-num half)
(rat-den half)  |# 

;***  ĆWICZENIE 2  ********  reprezentacja wektorow  *****************

(define (make-point a b)  ;; PUNKT
  (cons a b))

(define (point? p)
  (pair? p))

(define (point-x p)
  (car p))

(define (point-y p)
  (cdr p))
;---------------------------------------
(define (make-vect a b) ;; WEKTOR
  (cons a b))

(define (vect? v)
  (pair? v))

(define (vect-begin v)
  (car v))

(define (vect-end v)
  (cdr v))
;-------------------------------------

(define (display-point p)
  (display "(")
  (display (point-x p))
  (display " , ")
  (display (point-y p))
  (display ")"))

(define (display-vect v)
  (display "[")
  (display-point (vect-begin v))
  (display " , ")
  (display-point (vect-end v))
  (display "]"))

;--------------------------------------
(define (square x) (* x x))

(define (vect-length v) 
  (let ((x (- [point-x (vect-end v)]
              [point-x (vect-begin v)]))
        (y (- [point-y (vect-end v)]
              [point-y (vect-begin v)])))
    (sqrt (+ [square x] [square y]))))
        

(define (vect-scale v k)
  (let ((x (- [point-x (vect-end v)]
              [point-x (vect-begin v)]))
        (y (- [point-y (vect-end v)]
              [point-y (vect-begin v)])))
    (make-vect (vect-begin v) (make-point (* k x)(* k y)))))


(define (vect-translate v p)
  (make-vect p
             (make-point
              (+ (point-x p) (- (point-x (vect-end v))
                                (point-x (vect-begin v))))
              (+ (point-y p) (- (point-y (vect-end v))
                                (point-y (vect-begin v)))))))
  
         

  



(define p1 (make-point 1 2))
(define p2 (make-point 4 8))
(display-point p1)
(display-point p2)
(define V (make-vect p1 p2))
(newline)
(display-vect V)
(newline)(newline)
(display "V length: ")(vect-length V)
(display "V scaled 5x: ")(display-vect (vect-scale V 5))
(newline)
(display "V new length: ")(vect-length (vect-scale V 5))




  






