#lang racket

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

(define (node l r)
  (list 'node l r))

(define (node? n)
  (tagged-tuple? 'node 3 n))

(define (node-left n)
  (second n))

(define (node-right n)
  (third n))

(define (leaf? n)
  (or (symbol? n)
      (number? n)
      (null? n)))

;;

(define (res v s) ;;para wartosc i stan, do reprezentacji funkcji rename : t x st -> q x st
  (cons v s))

(define (res-val r) 
  (car r))

(define (res-state r)
  (cdr r))

;;

(define (rename t)
  (define (rename-st t i)
    (cond [(leaf? t) (res i (+ i 1))]
          [(node? t)
           (let* ([rl (rename-st (node-left t) i)]
                  [rr (rename-st (node-right t) (res-state rl))])
             (res (node (res-val rl) (res-val rr))
                  (res-state rr)))]))
  (res-val (rename-st t 0)))

;;

(define (st-app f x y)
  (lambda (st)
    (let* ([rx (x st)] ;; wywolujemy x na stanie poczatkowym dla obliczenia
           [ry (y (res-state rx))]) ;;wywolujemy y na stanie z wyniku poprzedniego, uruchamiamy y na nowym stanie
      (res (f (res-val rx) (res-val ry)) ;;tworzymy pare od ( wywolania f na wartosciach rx, ry . najnowszy stan z ry)
           (res-state ry))))) 

(define (st-app-args f . args)
  (lambda (st)
     (define (iter args vals last-state)
    (if (null? args)
        (res (apply f vals)
             last-state)
        (let* ([rx ((car args) last-state)])
          (iter (cdr args) (cons rx vals) (res-state rx)))))
    (iter args '() (res-state ((car args) st)))))
               
               


(define get-st
  (lambda (i)
    (res i i)))

(define (modify-st f)
  (lambda (i)
    (res null (f i))))

;;

(define (inc n)
  (+ n 1))

(define (rename2 t)
  (define (rename-st t)
    (cond [(leaf? t)
           (st-app-args (lambda (x y) x)
                   get-st
                   (modify-st inc))]
          [(node? t)
           (st-app-args node
                   (rename-st (node-left  t))
                   (rename-st (node-right t)))]))
  (res-val ((rename-st t) 0)))






