#lang racket

(define (const? t)
  (number? t))

(define (binop? t)
  (and (list? t)
       (= (length t) 3)
       (member (car t) '(+ - * /))))

(define (binop-op e)
  (car e))

(define (binop-left e)
  (cadr e))

(define (binop-right e)
  (caddr e))

(define (binop-cons op l r)
  (list op l r))

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (let-def? t)
  (and (list? t)
       (= (length t) 2)
       (symbol? (car t))))

(define (let-def-var e)
  (car e))

(define (let-def-expr e)
  (cadr e))

(define (let-def-cons x e)
  (list x e))

(define (let? t)
  (and (list? t)
       (= (length t) 3)
       (eq? (car t) 'let)
       (let-def? (cadr t))))

(define (let-def e)
  (cadr e))

(define (let-expr e)
  (caddr e))

(define (let-cons def e)
  (list 'let def e))

(define (var? t)
  (symbol? t))

(define (var-var e)
  e)

(define (var-cons x)
  x)

(define (hole? t)
  (eq? t 'hole))

(define (arith/let/holes? t)
  (or (hole? t)
      (const? t)
      (and (binop? t)
           (arith/let/holes? (binop-left  t))
           (arith/let/holes? (binop-right t)))
      (and (let? t)
           (arith/let/holes? (let-expr t))
           (arith/let/holes? (let-def-expr (let-def t))))
      (var? t)))

(define (num-of-holes t)
  (cond [(hole? t) 1]
        [(const? t) 0]
        [(binop? t)
         (+ (num-of-holes (binop-left  t))
            (num-of-holes (binop-right t)))]
        [(let? t)
         (+ (num-of-holes (let-expr t))
            (num-of-holes (let-def-expr (let-def t))))]
        [(var? t) 0]))

(define (arith/let/hole-expr? t)
  (and (arith/let/holes? t)
       (= (num-of-holes t) 1)))

(define (hole-context e)
  (define (hole-iter e context)
    (cond[(hole? e) (remove-duplicates context)] ;;0. znalazlem dziure

         [(let? e) ;;1. wyrazenie jest let'em
          (let* ([def (let-def e)]
                 [expr (let-expr e)]
                 [def-expr (let-def-expr def)]
                 [def-var (let-def-var def)])
            (cond [(arith/let/hole-expr? expr) (hole-iter expr (cons def-var context))] ;;w expr jest dziura
                  [else (hole-iter def-expr context)]))] ;;nie znalazlem dziury w expr

         [(binop? e) ;;2. wyrazenie jest typu binop
          (let ([left (binop-left e)]
                [right (binop-right e)])
            (cond [(arith/let/hole-expr? left) (hole-iter left context)]  ;;dziura w lewym podwyrazeniu
                  [(arith/let/hole-expr? right) (hole-iter right context)]))] ;;dziura w prawym podwyrazeniu

         [(not (arith/let/hole-expr? e)) ;;3. zabezpieczenie przed blednym inputem
          (error "Wrong number of holes!\n")]))
  (hole-iter e '() ))
         
        
(define (test)
  (let ([test1 (sort (hole-context '(- 42 hole)) symbol<?)]
        [wynik1 '()]
        
        [test2 (sort (hole-context '(let (x 3) (let (y 7) (+ x hole)))) symbol<?)]
        [wynik2 '(x y)]

        [test3 (sort (hole-context '(let (Igor 1) (let (Kacper 7) (let (Dawid 8) (let (Igor 9) (let (Karol 5) hole)))))) symbol<?)]
        [wynik3 '(Dawid Igor Kacper Karol)]

        [test4 (sort (hole-context '(+ (let (x 4) 2) hole)) symbol<?)]
        [wynik4 '()]

        [test5 (sort (hole-context '(+ (let(w (let (z 1) hole)) 2) 3)) symbol<?)]
        [wynik5 '(z)])
    (and (equal? test1 wynik1)
         (equal? test2 wynik2)
         (equal? test3 wynik3)
         (equal? test4 wynik4)
         (equal? test5 wynik5))))

(test) ;;odpalam test


