#lang racket

;; arithmetic expressions

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

(define (arith-expr? t)
  (or (const? t)
      (and (binop? t)
           (arith-expr? (binop-left  t))
           (arith-expr? (binop-right t)))))

;; calculator

(define (op->proc op)
  (cond [(eq? op '+) +]
        [(eq? op '*) *]
        [(eq? op '-) -]
        [(eq? op '/) /]))

(define (eval-arith e)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
            (eval-arith (binop-left  e))
            (eval-arith (binop-right e)))]))

;; let expressions

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

(define (arith/let-expr? t)
  (or (const? t)
      (and (binop? t)
           (arith/let-expr? (binop-left  t))
           (arith/let-expr? (binop-right t)))
      (and (let? t)
           (arith/let-expr? (let-expr t))
           (arith/let-expr? (let-def (let-def-expr t))))
      (var? t)))

;; evalation via substitution

(define (subst e x f)
  (cond [(const? e) e]
        [(binop? e)
         (binop-cons
           (binop-op e)
           (subst (binop-left  e) x f)
           (subst (binop-right e) x f))]
        [(let? e)
         (let-cons
           (let-def-cons
             (let-def-var (let-def e))
             (subst (let-def-expr (let-def e)) x f))
           (if (eq? x (let-def-var (let-def e)))
               (let-expr e)
               (subst (let-expr e) x f)))]
        [(var? e)
         (if (eq? x (var-var e))
             f
             (var-var e))]))

(define (eval-subst e)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
            (eval-subst (binop-left  e))
            (eval-subst (binop-right e)))]
        [(let? e)
         (eval-subst
           (subst
             (let-expr e)
             (let-def-var (let-def e))
             (eval-subst (let-def-expr (let-def e)))))]
        [(var? e)
         (error "undefined variable" (var-var e))]))

;; evaluation via environments

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

(define (eval-env e env)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
            (eval-env (binop-left  e) env)
            (eval-env (binop-right e) env))]
        [(let? e)
         (eval-env
           (let-expr e)
           (env-for-let (let-def e) env))]
        [(var? e) (find-in-env (var-var e) env)]))

(define (env-for-let def env)
  (add-to-env
    (let-def-var def)
    (eval-env (let-def-expr def) env)
    env))

(define (eval e)
  (eval-env e empty-env))

;;*** ZAD 1   ****************************************************

(define (Intersection l1 l2)
  (define (CzescWspolna l1 l2 acc)
    (cond[(or (null? l1) (null? l2)) acc]
         [(= (car l1) (car l2))
          (CzescWspolna (cdr l1) (cdr l2) (cons (car l1)acc) )]
         [(> (car l1) (car l2)) (CzescWspolna l1 (cdr l2) acc)]
         [(< (car l1) (car l2)) (CzescWspolna (cdr l1) l2 acc)]))
  (CzescWspolna (sort l1 <) (sort l2 <) '() ))


(define x '(1 2 3 4 5 6 7 8))
(define y '(2 4 6 8 10))

;;*** ZAD 1  ******* racket to ONP  *******************************************


(define (arith->rpn l)
  (define (ONP l acc)
    (cond [(const? l) (cons l acc)]
          [(binop? l) (ONP (binop-left l)
                           (ONP (binop-right l)
                                (cons (binop-op l) acc)))]
          [else acc]))
    (ONP l '()))
          
(define testONP (binop-cons '/
                            (binop-cons '+ 12 12)
                            (binop-cons '* 3 2)))
(define e
    (list '+
          (list '* 2 3)
          (list '- 10 4)))

;;*** ZAD 2 ***  STOS *******************************************
              
(define (stack? s)
  (list? s))

(define (push s x)
  (cons x s))

(define (pop s)
  (cons (car s) (cdr s)))

(define (pop->val p)
  (car p))

(define (pop->stack p)
  (cdr p))

(define empty-stack null)

;;*** ZAD 3  *** obliczanie ONP **********************************

(define ONP (arith->rpn testONP))

(define (eval-rpn l)
  (define (eval l acc)
    (cond [(null? l) (pop->val (pop acc))]
          [(const? (car l)) (eval (cdr l) (push acc (car l)))]
          [(symbol? (car l))
           (let* ((pop1 (pop->val (pop acc)))
                 (pop2 (pop->val (pop->stack (pop acc))))
                 (Stack (cddr acc))
                 (Newval ((op->proc (car l)) pop2 pop1)))
             (eval (cdr l) (push Stack Newval)))]))
  (eval l empty-stack))
                 
                 
           
           
          



                            