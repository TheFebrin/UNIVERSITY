#lang racket

#|
Implementacja liczb wymiernych i operacji na nich

Scheme dostarcza wbudowanych procedur (do zrobienia liczb wymiernych):

(cons x y) - tworzy pare zbudowana z x i y
(car p) - pierwszy element pary
(cdr p) - drugi element pary
(pair? p) - predykat sprawdzajacy czy jest para

(car (cons x y)) == x //zawsze
(analogicznie z cdr i y)
(pair? (cons x y) == true //zawsze
(pair? x) == false //zawsze



|#
(define (make-rat n d);;robimy sobie liczbe wymierna / <- KONSTRUKTOR
  (let ((c (gcd n d)))
    (cons (/ n c) (/ d c))));;dodatkowo normalizacja, dzielenie przez nwd
  
(define (rat-numer l) ;;zwraca nam licznik    / <- SELEKTOR
  (car l))

(define (rat-denum l) ;;zwraca nam mianownik / -||-
  (cdr l))

(define (rat? l) ;; sprawdza czy l jest liczba wymierna czy nie / <-PREDYKAT
  (and(pair? l) ;;jest para
      (not (= (rat-denum l) 0)) ;;licznik != 0
      (= 1 (gcd (rat-numer l) (rat-denum l))))) ;; nieskracalny

(define (mul-frac l1 l2) ;;mnozenie
  (let ((n (* (rat-numer l1) (rat-numer l2)))
        (d (* (rat-denum l1) (rat-denum l2))))
    (make-rat n d)))

;;reszte da sie latwo zrobic

(define (zero? l) ;;sprawdzamy czy nasza liczba wymierna  jest 0
  (= 0 (rat-numer l)))

;;Fifi wlecial na flow, drop the kreda i wgl

;;pakiet dla uzytkownika

(define (integer->rational n) ;;robimy wymierna z calkowitej
  (make-rat n 1))

(define (div-rat l1 l2)
  (let ((n (* (rat-numer l1) (rat-denum l2)))
        (d (* (rat-denum l1) (rat-numer l2))))
    (make-rat n d)))

#|
Zaczynamy implementowac listy
Tworzymy pare, pierwszy element pary to pierwszy element ciagu, a drugi
element to reszta ciagu
|#


;; (null? null) == true / zawsze

(define (list? x) ;;chcemy wiedziec kiedy x jest lista
  (or (null? x)
      (and (pair? x)
           (list? (cdr x)))))

(define (length xs) ;; obliczmy dlugosc listy
  (if (null? xs)
      0
      (+ 1 (length (cdr xs)))))

(define (append xs ys) ;; laczymy dwie listy
  (if(null? xs)
     ys
     (cons (car xs) (append (cdr xs) ys))))

;; dowod na to ze listy dzialaja czy cos, ale ja wierze na slowo
(define (square x) (* x x))

(define (gen-sequence start next end) ;; generujemy ciag
  [if(> start end)
     null
     (cons start (gen-sequence (next start) next end))])

(define (square-list xs) ;; ciag kwadratow
  [if(null? xs)
     null
     (cons (square (car xs)) (square-list (cdr xs)))])

(define (map f xs) ;;ogolny ciag dla jakiegos f
  [if(null? xs)
     null
     (cons (f (car xs))
           (map f (cdr xs)))])


;;uzywajac map podajac za f square mozna zrobic latwiejszy ciag kwadratow

(define (sumlist xs) ;;suma wyrazow w liscie
  (if(null? xs)
     0
     (+ (car xs) (sumlist (cdr xs)))))


(define (fold_right op nval xs) ;;
  [if(null? xs)
     nval
     (op (car xs)
         (fold_right op nval (cdr xs)))])
