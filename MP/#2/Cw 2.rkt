#lang racket
(define (identity x) x)  ;;identycznosc
(define (inc x) (+ 1 x)) ;;ikrementacja
(define (dec x) (- x 1)) ;;dekrementacja
(define (square x) (* x x)) ;;square
(define (cube x) (* x x x)) ;;cube
(define (average x y) (/ (+ x y) 2)) ;;sr. arytm.

(define (average-damp f)
  (lambda (x) (average x (f x))))

(define (compose f g)
  (lambda (x) (f (g x))))

;**************   ZAD 3    ***************************************


(define (repeated p n) 
  [if(= n 0)
     identity
     (compose p (repeated p (- n 1)))])

;*************   SUMA CIAGU   **************************************

(define (sum term next s e)
  [if(> s e)
     0
     (+ (term s) (sum term next (next s) e))])

;**************    ZAD 4 REKURENCJA    *******************************************

(define (product term next a b) ;; ZAD 4 rekurencyjnie
  [if(> a b)
     1
     (* (term a) (product term next (next a) b))])

;*************   ZAD 4 ITERACYJNIE   ****************************************

(define (pro-iter term next a b)
  (define (product-iter a wynik)
    [if(> a b)
       wynik
       (product-iter (next a) (* wynik (term a)))])
  (product-iter a 1))

;*****************   PRZYBLIZONE PI    **************************************

(define (cpi b)
  (define (next2 x) (+ 2 x))
  (* 2.0 b
     (square(/
            (product identity next2 2 (- b 1))
            (product identity next2 3 b)))))

;***************    ZAD 5   *****************************************

(define (accumulate combiner null-value term next a b)
  [if(> a b)
     null-value
     (combiner (term a)
               (accumulate combiner null-value term next (next a) b))])

;*************    ZAD 6   ********************************************

(define (cont-frac num den k)
  (define (cont i)
    [if(> i k)
       0
       (/ (num i) (+ (den i) (cont (inc i))))])
  (cont 1))

(define (cont-frac-iter num den k)
  (define (cont i wynik)
    [if(> i k)
       wynik
       (cont (inc i) (/ (num i) (+ (den i) wynik)))])
  (cont 1 0))

;************    ZAD 7    *******************************************

(define (frac-pi k)  ;;trzeba zmienic inc na (+ i 2) w cont-frac
  (+ 3 (cont-frac square (lambda (x) 6.0) k)))

;************    ZAD 8    *******************************************

(define (arctg x k) ;;to nie dziala, ale prosto mozna sobie zrobic
  (/ x
     (+ 1
        (cont-frac square (lambda (x) 1.0) k))))

;************    ZAD 9    *******************************************

(define (build n d b) (/ n (+ d b)))


;***



     


 
  
  
  
  





     
     





