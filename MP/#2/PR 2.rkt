#lang racket
;;Dawid Dieu

;;***  BASIC FUNCTIONS   ************************************

(define (square x) (* x x x))
(define (average x y) (/ (+ x y) 2))
(define (dec x) (- x 1))

;;***  FIXED POINT  *****************************************

(define (fixed-point f x0)

  (define (close-enough? a b)
    (< (abs(- a b)) 0.00001))
  
  (let ((x1 (f x0)))
    (if(close-enough? x0 x1)
       x0
       (fixed-point f x1))))

;;***  AVERAGE DAMP  ****************************************

(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2)))

;;***  REPEATED  ********************************************

(define (compose f g)
  (lambda (x) (f (g x))))

(define (repeated p n) 
  [if(= n 0)
     (identity p)
     (compose p (repeated p (- n 1)))])



;;*** ZAD 11 ************************************************


;;Najpierw sprawdzmy tlumienia

(define (ile-tlumien n x T)
  
  (define (usrednienie y) (/ x (expt y (dec n))))
  
  [fixed-point
   ((repeated average-damp (dec T))usrednienie )
   1.0])

;;sprawdzamy ile potrzeba nam tlumien
(display "SPRAWDZAMY TLUMIENIA\n\n")
(ile-tlumien 2 4 1)
(ile-tlumien 3 8 1)
(ile-tlumien 4 16 2);;trzeba zwiekszyc tlumienie
(ile-tlumien 5 32 2)
(ile-tlumien 6 64 2)
(ile-tlumien 7 128 2)
(ile-tlumien 8 256 3);;trzeba zwiekszyc
(ile-tlumien 9 512 3)
(ile-tlumien 10 1024 3)
(ile-tlumien 11 2048 3)
(ile-tlumien 12 4096 3)
(ile-tlumien 13 8192 3)
(ile-tlumien 14 16384 3)
(ile-tlumien 15 32768 3)
(ile-tlumien 16 65536 4);;itd...

#|
WNIOSEK
Tlumienie nalezy zwiekszyc dla kazdego testu o numerze
postaci 2^n.
Zatem dla pierwiastka stopnia  n
potrzebujemy podloga(log(n)) tlumien.
|#


(define (nth-root n x)
  
  (define tlumienia (dec (truncate (log n 2))))
  (define (usrednienie y) (/ x (expt y (dec n))))
  
  [fixed-point
   ((repeated average-damp tlumienia) usrednienie)
   1.0])

;;*** TESTY   ***********************************************
(display "\n\nTEST WLASCIWY\n\n")
(display "2nd root 1\n")(nth-root 2 1)
(display "2nd root 10\n")(nth-root 2 10)
(display "3rd root 8\n")(nth-root 3 8)
(display "3rd root 1000000000000\n") (nth-root 3 1000000000000)
(display "4th root 6561\n") (nth-root 4 6561)
(display "5th root 9^5\n")(nth-root 5 (expt 9 5))
(display "6th root 9^6\n")(nth-root 6 (expt 9 6))
(display "10th root 9^10\n")(nth-root 10 (expt 9 10))
(display "15th root 9^15\n")(nth-root 15 (expt 9 15))
(display "20th root 9^20\n")(nth-root 20 (expt 9 20))
(display "30th root 9^30\n")(nth-root 30 (expt 9 30))
(display "50th root 9^50\n")(nth-root 50 (expt 9 50))


  
  


       