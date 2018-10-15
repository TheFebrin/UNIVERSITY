#lang racket

;;Dawid Dieu ®©

;; pomocnicza funkcja dla list tagowanych o określonej długości

(define (tagged-tuple? tag len p)
  (and (list? p)
       (= (length p) len)
       (eq? (car p) tag)))

(define (tagged-list? tag p)
  (and (pair? p)
       (eq? (car p) tag)
       (list? (cdr p))))

;;
;; WHILE
;;

; memory

(define empty-mem
  null)

(define (set-mem x v m)
  (cond [(null? m)
         (list (cons x v))]
        [(eq? x (caar m))
         (cons (cons x v) (cdr m))]
        [else
         (cons (car m) (set-mem x v (cdr m)))]))

(define (get-mem x m)
  (cond [(null? m) 0]
        [(eq? x (caar m)) (cdar m)]
        [else (get-mem x (cdr m))]))

; arith and bool expressions: syntax and semantics

(define (const? t)
  (number? t))

(define (true? t)
  (eq? t 'true))

(define (false? t)
  (eq? t 'false))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * / = > >= < <= not and or mod rand expt))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]
        [(eq? op '=) =]
        [(eq? op '>) >]
        [(eq? op '>=) >=]
        [(eq? op '<)  <]
        [(eq? op '<=) <=]
        [(eq? op 'not) not]
        [(eq? op 'and) (lambda x (andmap identity x))]
        [(eq? op 'or) (lambda x (ormap identity x))]
        [(eq? op 'mod) modulo]
        [(eq? op 'rand) (lambda (max) (min max 4))]
        [(eq? op 'expt) expt]))

                        
(define (var? t)
  (symbol? t))

(define (eval-arith e m)
  (cond [(true? e) true]
        [(false? e) false]
        [(var? e) (get-mem e m)]
        [(op? e)
         (apply
          (op->proc (op-op e))
          (map (lambda (x) (eval-arith x m))
               (op-args e)))]
        [(const? e) e]))

;; syntax of commands

(define (assign? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (second t) ':=)))

(define (assign-var e)
  (first e))

(define (assign-expr e)
  (third e))

(define (if? t)
  (tagged-tuple? 'if 4 t))

(define (if-cond e)
  (second e))

(define (if-then e)
  (third e))

(define (if-else e)
  (fourth e))

(define (while? t)
  (tagged-tuple? 'while 3 t))

(define (while-cond t)
  (second t))

(define (while-expr t)
  (third t))

(define (block? t)
  (list? t))

;; state

(define (res v s)
  (cons v s))

(define (res-val r)
  (car r))

(define (res-state r)
  (cdr r))

;; psedo-random generator

(define initial-seed
  123456789)

(define (rand max)
  (lambda (i)
    (let ([v (modulo (+ (* 1103515245 i) 12345) (expt 2 32))])
      (res (modulo v max) v))))

;; WHILE interpreter

(define (old-eval e m)
  (cond [(assign? e)
         (set-mem
          (assign-var e)
          (eval-arith (assign-expr e) m)
          m)]
        [(if? e)
         (if (eval-arith (if-cond e) m)
             (old-eval (if-then e) m)
             (old-eval (if-else e) m))]
        [(while? e)
         (if (eval-arith (while-cond e) m)
             (old-eval e (old-eval (while-expr e) m))
             m)]
        [(block? e)
         (if (null? e)
             m
             (old-eval (cdr e) (old-eval (car e) m)))]))

(define (eval e m seed)
  ;; TODO : ZAD B: Zaimplementuj procedurę eval tak, by
  ;;        działała sensownie dla wyrażeń używających
  ;;        konstrukcji "rand".
  (old-eval e m))

(define (run e)
  (eval e empty-mem initial-seed))

;;

(define fermat-test
      ;; TODO : ZAD A: Zdefiniuj reprezentację programu w jęzku
      ;;        WHILE, który wykonuje test Fermata, zgodnie z
      ;;        treścią zadania. Program powinien zakładać, że
      ;;        uruchamiany jest w pamięci, w której zmiennej
      ;;        n przypisana jest liczba, którą testujemy, a
      ;;        zmiennej k przypisana jest liczba iteracji do
      ;;        wykonania. Wynik powinien być zapisany w
      ;;        zmiennej comopsite. Wartość true oznacza, że
      ;;        liczba jest złożona, a wartość false, że jest
      ;;        ona prawdopodobnie pierwsza.

  '(
    (composite := true) ;;zakladamy ze jest zlozona
    {while (> k 0)
           [
            (k := (- k 1))
            (a := (+ 2 (rand (- n 4)))) ;;Wybierz losowo wartość a z zakresu 2 . . . (n - 2)

             (if (not (= (mod (expt a (- n 1)) n) 1))   ;;Jeśli a ^ (n-1) !≡ 1 (mod n), to zakończ algorytm z odpowiedzią „złożona”.
                 (k := 0) ;;jest zlozona, czyli koncze algorytm ustawiajac k na 0
                 (composite := false)) ;;jest pierwsza z pewnym prawdopodobienstwem
            ]
     }))

(define (probably-prime? n k) ; check if a number n is prime using
                              ; k iterations of Fermat's primality
                              ; test
  (let ([memory (set-mem 'k k
                (set-mem 'n n empty-mem))])
    (not (get-mem
           'composite
           (eval fermat-test memory initial-seed)))))


;;*** TESTY ***************************************************************

(define k 100) ;; liczba iteracji


;;liczby pierwsze:
(display "Czy 5 jest pierwsze? ")
(probably-prime? 5 k)

(display "Czy 13 jest pierwsze? ")
(probably-prime? 13 k)

(display "Czy 47 jest pierwsze? ")
(probably-prime? 47 k)

(display "Czy 97 jest pierwsze? ")
(probably-prime? 97 k)

(display "Czy 271 jest pierwsze? ")
(probably-prime? 271 k)

(newline) ;;liczby zlozone ponizej

(display "Czy 111 jest pierwsze? ")
(probably-prime? 111 k)

(display "Czy 292 jest pierwsze? ")
(probably-prime? 292 k)

(display "Czy 5466 jest pierwsze? ")
(probably-prime? 5466 k)

(display "Czy 12345678 jest pierwsze? ")
(probably-prime? 123456 k)