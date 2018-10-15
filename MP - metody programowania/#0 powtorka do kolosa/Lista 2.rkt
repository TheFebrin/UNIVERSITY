#lang racket

;;Dejwo to ziomal ®©

(define (square x)
  (* x x))

(define (inc x)
  (+ 1 x))

(define (identity x) x)

;;*** ZAD 2 ****************************************************************

(define (compose f g)
  (lambda (x) (f (g x))))

;;*** ZAD 3 ****************************************************************

(define (repeated p n)
  (if (= 0 n)
      identity
      (compose p (repeated p (- n 1)))))

;;*** ZAD 4 ****************************************************************

(define (product-rec term next a b)
  (if (> a b)
      1
      (* (term a) (product-rec term next (next a) b))))

(define (product-iter term next a b)
  (define (iter acc a b)
    (if (> a b)
        acc
        (iter (* acc (term a)) (next a) b)))
  (iter 1 a b))


(define (count-pi n)
  (* 2.0 n (square
          (/ (product-rec identity (lambda (x) (+ x 2)) 2 (- n 1))
             (product-rec identity (lambda (x) (+ x 2)) 3 n)))))

;;*** ZAD 5 ****************************************************************

(define (accumulate combiner null-value term a next b)
  (if (> a b)
      null-value
      (combiner (term a) (accumulate combiner null-value term (next a) next b))))

;;*** ZAD 6 ****************************************************************

(define (cont-frac num dem k)
  (define (iter i)
     (if (> i k)
      0
      (/ (num i) (+ (dem i) (iter (+ i 1))))))
  (iter 1))

;;*** ZAD 7 ****************************************************************


(define (count-pi-frac k)
  (+ 3
     (cont-frac (lambda (i) (square (- (* 2 i) 1))) (lambda (i) 6.0) k)))
        


;;*** ZAD 8 ****************************************************************

(define (count-tan x k)
  (/ x
     (+ 1.0
        (cont-frac (lambda (i) (square (* i x))) (lambda (i) (+ i 2))k))))

;;*** ZAD 9 ****************************************************************

(define (build n d b)
  (/ n (+ d b)))


(define (compose3 f g)
  (lambda (a b c) (f a b (g a b c))))

(define (repeated3 p n)
  (if (= n 1)
      p
      (compose3 p (repeated3 p (- n 1)))))

(define (repeated-build k n d b)
  ((repeated3 build k) n d b))
  



             
  
  

