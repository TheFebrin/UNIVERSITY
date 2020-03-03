#lang racket

;; arithmetic expressions

(define (const? t)
  (number? t))

(define (binop? t)
  (and (list? t)
       (= (length t) 3)
       (member (car t) '(+ - * /))))

(define (op? t)
  (member t '(+ - / *)))

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

(define (let-defs? t)  ;;<- do zad 7
   (= (length t)
     (length (filter let-def? t))))

(define (new-let? t)
  (and (list? t)
       (= (length t) 3)
       (let-defs? (let-def t))))

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
       (let-def? (let-def t))))

(define (if-zero? t)
  (and (list? t)
       (= (length t) 4)
       (eq? (car t) 'if-zero)))

(define (if-zero-def e)
  (cadr e))

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
  (cond [(null? env) x]
        [(const? x) x] 
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))

(define (eval-env e env)
  (cond [(const? e) e]
        [(binop? e)
         ((op->proc (binop-op e))
          (eval-env (binop-left  e) env)
          (eval-env (binop-right e) env))]
        [(if-zero? e) ;;<- if zero
         (if (= (eval (if-zero-def e)) 0)
             (eval (third e))
             (eval (fourth e)))]
        [(and (list? e) ;;<-- eval dla listy z operatorem o nieokreslonej dlugosci
              (op? (car e)))
         (let ([eval-list (find-symbols-in-env e env)])
         (apply (op->proc (car eval-list)) (cdr eval-list)))]
        [(let? e)
         (eval-env
          (let-expr e)
          (env-for-let (let-def e) env))]
        [(new-let? e)   ;;<- new let
         (eval-env
          (let-expr e)
          (env-for-lets (let-def e) env))] ;;trzeba dodac liste zmiennych do srodowiska
          
        [(var? e) (find-in-env (var-var e) env)]))

(define (env-for-let def env)
  (add-to-env
   (let-def-var def)
   (eval-env (let-def-expr def) env)
   env))

(define (env-for-lets def env) ;;env dla leta z wieloma rzeczami
  (if (null? def)
      env
      (env-for-lets (cdr def)
                    (add-to-env
                     (let-def-var (car def))
                     (eval-env (let-def-expr (car def)) env)
                     env))))

(define (find-symbols-in-env symbols-list env)  ;;bierze liste symboli i szuka ich w srodowisku zwracajac juz liste liczb
  (cond [(null? symbols-list)  null]
        [(op? (car symbols-list)) (cons (car symbols-list)
                                         (find-symbols-in-env (cdr symbols-list) env))]
        [else
         (cons (find-in-env (car symbols-list) env)
            (find-symbols-in-env (cdr symbols-list) env))]))

(define (eval e)
  (eval-env e empty-env))


;_______________________________________Zad 1__________________________________________________________

(define e
  (list '+
        (list '* 2 3)
        (list '- 10 4)))

(define e2 (binop-cons '/
                       (binop-cons '+ 12 12)
                       (binop-cons '* 3 2)))

(define (arith->rpn e)
  (define (ONP e onp-list)
    (cond [(const? e) (cons e onp-list)]
          [(binop? e) (ONP (binop-left e)
                           (ONP (binop-right e) (cons (binop-op e) onp-list)))]
          [else onp-list]))
  (ONP e null))

;_______________________________________Zad 2__________________________________________________________

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
        

;_______________________________________Zad 3__________________________________________________________

(define (eval-rpn e)
  (define (onp-eval e stack)
    
    (display stack)(newline) ;;<-- stan stacka
    
    (cond [(null? e) (pop->val stack)]
          [(const? (car e)) (onp-eval (cdr e) (push stack (car e)))] ;;push liczby
          [else
           
           (display (car e))(newline);;<-- dzialanie
           
           (let* ([op (op->proc (car e))]  ;;biore operator
                  [first (pop->val stack)]   ;;1 ze stosu
                  [second (pop->val (pop->stack stack))]  ;;2
                  [new-expr (op second first)]
                  [new-stack (push  (pop->stack (pop->stack stack)) new-expr)])
            
             (onp-eval (cdr e) new-stack))]))
  (onp-eval e empty-stack))
            
(define onp-expr (arith->rpn e))
(define onp-expr2 (arith->rpn e2))

;_______________________________________Zad 5__________________________________________________________

(define Zad5 (eval '(if-zero (let (x 3) x) 7 (+ 1 2))))
(define Zad52 (eval '(if-zero (- 2 2) 7 9)))

;_______________________________________Zad 6__________________________________________________________

;niby fajnie jaby mogly dostawac tez wyrazenia jako argumenty, ale za duzo roboty
(define Zad6 (eval '(+ 1 2 3 4 5)))
(define Zad62 (eval '(* 1 2 3 4 5)))

;_______________________________________Zad 7__________________________________________________________

(define Zad7 (eval '(let ((x 3) (y 5) (z 10)) (+ x y z))))

;Dalej useless zadanka
