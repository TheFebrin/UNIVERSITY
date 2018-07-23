#lang racket
;;Dawid Dieu

;;***  BASIC FUNCTIONS   ************************************

(define (square x) (* x x))
(define (average x y) (/ (+ x y) 2))
(define (dec x) (- x 1))
(define (inc x) (+ x 1))

;;***  ZAD 10   *********************************************

(define (cont-frac num den)
  (define (iter a0 a1 b0 b1 f k)
    
      (define (close-enough? a b) 
    (< (abs(- a b)) 0.000001))

    (define Ak (+ (* (den k) a1) (* (num k) a0))) 
    (define Bk (+ (* (den k) b1) (* (num k) b0)))
    (define Fk (/ Ak Bk))
    
    (if (close-enough? f Fk)
        f
        (iter a1 Ak b1 Bk Fk (inc k))))
  (iter 1 0 0 1 0 1))


(define (arctg x)  ;;definiuje arc tg za pomoca cont-frac
  (/ x
     (+ 1
        (cont-frac (lambda (i) (square(* i x)))
                   (lambda (i) (inc(* 2.0 i)))))))

;; testujemy porownujac wbudowany arc tan i moj

(display "Test 1: dla x = -10 \n")
(display "Moja: ")(arctg -10)
(display "Wbudowana: ")(atan -10)
(display "\n")

(display "Test 2: dla x = -2 \n")
(display "Moja: ")(arctg -2)
(display "Wbudowana: ")(atan -2)
(display "\n")

(display "Test 3: dla x = 2 \n")
(display "Moja: ")(arctg 2)
(display "Wbudowana: ")(atan 2)
(display "\n")

(display "Test 4: dla x = 10 \n")
(display "Moja: ")(arctg 10)
(display "Wbudowana: ")(atan 10)
(display "\n")



        
   

