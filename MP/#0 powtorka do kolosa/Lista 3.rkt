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
  
         
  
#|


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

|#

;*** ZAD 3  **** wektor inaczej *********************************

(define (make-vect2 p d len) ;;Wektor
  (cons p (cons d (cons len null))))

(define (vect-point v)
  (car v))

(define (vect-deg v)
  (car (cdr v)))

(define (vect-len v)
  (car (cdr (cdr v))))

(define (vect-begin2 v)
  (car v))

(define (vect-end2 v)
  (make-point
   (* (vect-len v) (cos (vect-deg v)))
   (* (vect-len v) (sin (vect-deg v)))))

(define (vect-scale2 v k)
  (make-vect
   (vect-point v)
   (vect-deg v)
   (* (vect-len v) k)))


;;***  ZAD 4  ************************************************

(define (reverse l)
  (if (null? l)
      null
      (append (reverse (cdr l)) (list (car l)))))

(define (reverse-iter l)
  (define (iter l acc)
    (if (null? l)
        acc
        (iter (cdr l) (cons (car l) acc))))
  (iter l '() ))

;;***  ZAD 5  ************************************************

(define (insert xs n)
  (cond [(null? xs) (list n)]
         [(> (car xs) n) (cons n xs)]
         [else (cons (car xs) (insert (cdr xs) n))]))

(define (insert-aka-push-to-end n ys)
  (if (null? ys)
      (list (list n))
      (cons (cons n ys)
            (map (lambda (zs) (cons (car ys) zs))
                 (insert-aka-push-to-end n (cdr ys))))))

(define (insert-sort xs)
  (define (iter xs acc)
    (if (null? xs)
        acc
        (iter (cdr xs) (insert acc (car xs)))))
  (iter xs '() ))


;;*** ZAD 6 ************************************************

(define (concat l)
  (if (null? l)
      '()
      (append (car l) (concat (cdr l)))))

(define (permi l)
  (if (null? l)
      '(())
      (concat (map (lambda (zs) (insert-aka-push-to-end (car l) zs))
                   (permi (cdr l))))))


;;*** ZAD 9 ************************************************

(define (append x y)
  (if (null? x)
      y
      (cons (car x) (append (cdr x) y))))

(define (append-f-chuj . args)
  (define (iter args)
     (if (null? args)
      '()
      (append (car args) (iter (cdr args)))))
  (iter args))

      
  



