#lang racket

(require racklog)

;; predykat unarny %male reprezentuje zbiór mężczyzn
(define %male
  (%rel ()
        [('adam)]
        [('john)]
        [('joshua)]
        [('mark)]
        [('david)]))

;; predykat unarny %female reprezentuje zbiór kobiet
(define %female
  (%rel ()
        [('eve)]
        [('helen)]
        [('ivonne)]
        [('anna)]))

;; predykat binarny %parent reprezentuje relację bycia rodzicem
(define %parent
  (%rel ()
        [('adam 'helen)]
        [('adam 'ivonne)]
        [('adam 'anna)]
        [('eve 'helen)]
        [('eve 'ivonne)]
        [('eve 'anna)]
        [('john 'joshua)]
        [('helen 'joshua)]
        [('ivonne 'david)]
        [('mark 'david)]))

;; predykat binarny %sibling reprezentuje relację bycia rodzeństwem
(define %sibling
  (%rel (a b c)
        [(a b)
         (%parent c a)
         (%parent c b)
         (%male c)]))

;; predykat binarny %sister reprezentuje relację bycia siostrą
(define %sister
  (%rel (a b)
        [(a b)
         (%sibling a b)
         (%female a)]))

;; predykat binarny %ancestor reprezentuje relację bycia przodkiem
(define %ancestor
  (%rel (a b c)
        [(a b)
         (%parent a b)]
        [(a b)
         (%parent a c)
         (%ancestor c b)]))

;; predykat binarny %grandson reprezentuje relację bycia prawnuczkiem
(define %grandson
  (%rel (a b c)
        [(a c)
         (%parent a b)
         (%parent b c)
         (%male a)]))

;; predykat binarny %cousin reprezentuje relację bycia kuzynem
(define %cousin
  (%rel (a b c d)
        [(a d)
         (%parent b a)
         (%sibling c b)
         (%parent c d)]))

;;Zad 3

(define %my-append
  (%rel (x xs ys zs)
        [(null ys ys)]
        [((cons x xs) ys (cons x zs))
         (%my-append xs ys zs)]))


;; Dalszy kod z wykladu

(define %my-member
  (%rel (x xs y)
        [(x (cons x xs))]
        [(y (cons x xs))
         (%my-member y xs)]))

(define %select
  (%rel (x xs y ys)
        [(x (cons x xs) xs)]
        [(y (cons x xs) (cons x ys))
         (%select y xs ys)]))

;; prosta rekurencyjna definicja
(define %simple-length
  (%rel (x xs n m)
        [(null 0)]
        [((cons x xs) n)
         (%simple-length xs m)
         (%is n (+ m 1))]))

;; test w trybie +- (działa)
(%find-all (a) (%simple-length (list 1 2) a))
;; test w trybie ++ (działa)
(%find-all () (%simple-length (list 1 2) 2))
;; test w trybie -+ (1 odpowiedź, pętli się)
(%which (xs) (%simple-length xs 2))
;; test w trybie -- (nieskończona liczba odpowiedzi)
(%which (xs a) (%simple-length xs a))

;; definicja zakładająca, że długość jest znana
(define %gen-length
  (%rel (x xs n m)
        [(null 0) !]
        [((cons x xs) n)
         (%is m (- n 1))
         (%gen-length xs m)]))
;; test w trybie ++ (działa)
(%find-all () (%gen-length (list 1 2) 2))
;; test w trybie -+ (działa)
(%find-all (xs) (%gen-length xs 2))
