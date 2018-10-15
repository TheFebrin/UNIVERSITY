#lang racket
;;W zrozumieniu kodu, oraz pokazaniu ogolnej idei zadania pomagal na KSI Mateusz Kacala


;;functions
(define (inc x)
  (+ 1 x))

;; expressions

(define (const? t)
  (number? t))

(define (op? t)
  (and (list? t)
       (member (car t) '(+ - * /))))

(define (op-op e)
  (car e))

(define (op-args e)
  (cdr e))

(define (op-cons op args)
  (cons op args))

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

(define (arith/let-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith/let-expr? (op-args t)))
      (and (let? t)
           (arith/let-expr? (let-expr t))
           (arith/let-expr? (let-def-expr (let-def t))))
      (var? t)))

;; let-lifted expressions

(define (arith-expr? t)
  (or (const? t)
      (and (op? t)
           (andmap arith-expr? (op-args t)))
      (var? t)))

(define (let-lifted-expr? t)
  (or (and (let? t)
           (let-lifted-expr? (let-expr t))
           (arith-expr? (let-def-expr (let-def t))))
      (arith-expr? t)))

;; generating a symbol using a counter

(define (number->symbol i)
  (string->symbol (string-append "x" (number->string i))))

;; environments (could be useful for something)

(define empty-env
  null)

(define (add-to-env x v env)
  (cons (list x v) env))

(define (find-in-env x env)
  (cond [(null? env) (error "undefined variable" x)]
        [(eq? x (caar env)) (cadar env)]
        [else (find-in-env x (cdr env))]))



;;Tworze liste definicji jako pary: '( (stara nazwa . nowa nazwa) ... )
                      
(define (rename expr iter env) ;;procedura do nadawania nowych nazw zmiennym, zwraca liste 2-elementowa, w postaci (wyrazenie , ilosc zmiennych)
  (cond [(var? expr) (list (find-in-env expr env) iter)]
        [(const? expr) (list expr iter)] 
        [(op? expr)
         
         (define (rename-in-op env iter args) ;;procedura zamieniajaca gdy trafie na wyrazenie
  (cond [(null? args) (list null iter)] ;;wyrazenie jest lista '(e1 e2 e3 ...)
        [else (let* ([first-renamed (rename (car args) iter env)] ;;odpalam rename na pierwszym wyrazeniu
                     [new-iter (second first-renamed)];;nowy iterator, czyli ilosc zmiennych wystepujacych 
                     [elem (first first-renamed)] ;;elementy
                     [rest (rename-in-op env new-iter (cdr args))]
                     [rest-fst (first rest)]
                     [last-iter (second rest)])
                (list (cons elem rest-fst) last-iter))]))

         (let* ([first-renamed (rename-in-op env iter (op-args expr))]
                [args (first first-renamed)]
                [n_iter (second first-renamed)])
           (list (op-cons (op-op expr) args) n_iter))]
        
        [(let? expr)
         (let* ([first-renamed (rename (let-def-expr (let-def expr)) iter env)] 
                [new-let-def-expr (first first-renamed)] ;;wyrazenie z let'ami
                [new-iter (second first-renamed)] ;;ilosc zmiennych
                [new-def-var (number->symbol new-iter)] ;;nowa zmienna
                [new-env (add-to-env (let-def-var (let-def expr)) new-def-var env)] ;;dodajemy nowa zmienna do srodowiska         
                [new-renamed (rename (let-expr expr) (inc new-iter) new-env)] ;;wywoluje rename z nowym srodowiskiem i wieksza iloscia zmiennych
                [new-let-expr (first new-renamed)] ;;nowe lety
                [latest-iter (second new-renamed)]) ;;nowa ilosc zmiennych
           (list (let-cons (let-def-cons new-def-var new-let-def-expr)
                           new-let-expr)
                 latest-iter))]))

(define rename-test (rename '(let (x 2) (+ 1 x)) 0 empty-env))
(define rename-test2 (rename '(let (x (- 2 (let (z 3) z))) (+ x 2)) 0 empty-env))



;;Procedura decompose ma bardzo podobna strukture i zasade dzialania jak rename

(define (decompose expr env) ;;zwraca liste dwuelementowa, (wyrazenie bez letow , wyciagniete definicje zmiennych z letow (srodowisko) )
  (cond [(const? expr) (list expr env)]
        [(var? expr) (list expr env)]
        [(op? expr)

         (define (decompose-op args env) ;;procedura decompose dla wyrazenia
           (cond [(null? args) (list '() env)]
                 [else
                  (let* ([first-decomposed (decompose (car args) env)];;wywoluje decompose na pierwszym argumencie
                         [elem (first first-decomposed)] ;;biore elementy, czyli pierwszy element z listy dwuelementowej
                         [new-env (second first-decomposed)] ;;biore drugi element tej listy, czyli nowe srodowisko ze zmiennymi
                         [rest (decompose-op (cdr args) new-env)]
                         [rest-fst (first rest)]
                         [snd-env (second rest)])
                    (list (cons elem rest-fst) snd-env))]))
         
         (let* ([first-arg (decompose-op (op-args expr) env)]
                [new-args (first first-arg)]
                [new-env (second first-arg)])
           (list (op-cons (op-op expr) new-args) new-env))]
        
        [(let? expr) 
         (let* ([first-decomposed (decompose (let-def-expr (let-def expr)) env)]
                [new-def-expr (first first-decomposed)]
                [new-env (second first-decomposed)]
                [rest (decompose (let-expr expr) new-env)]
                [new-expr (first rest)]
                [latest-env (second rest)]
                [var (let-def-var (let-def expr))]
                [final-env (add-to-env var new-def-expr latest-env)])
           (list new-expr final-env))]))

(define decompose-test (decompose '(+ 4 (let (x 2) (+ 6 x))) empty-env))
(define decompose-test2 (decompose '(+
                                     (+
                                      (let (x 0) (+ x (let (x 8) (+ 22 x))))
                                      (let (x 6) (+ x (let (x 4) (+ 22 x)))))
                                     (+ (let (x 6) (+ x (let (x 44) (+ 22 x))))
                                        (let (x 6) (+ x (let (x 44) (+ 22 x)))))) empty-env))



(define (sort-env env) ;;sortowanie zmiennych w srodowisku rosnaco po pierwszym elemencie pary: (zmienna . wartosc)
  (sort env #:key car (lambda (x y) (symbol<? x y))))


(define (make-lifted-let env expr) ;;aplikuje posortowane srodowisko do wyrazenia, tworzac duze let wyrazenie
  (cond [(null? env) expr]
        [else
         (let-cons (car env) (make-lifted-let (cdr env) expr))]))
                

;; the let-lift procedure

(define (let-lift e)
  (let* ([renamed-e (car (rename e 0 empty-env))] ;;wyrazenie ze zmienionymi nazwami zmiennych
         [decomposed-e (decompose renamed-e empty-env)] ;;para wyrazenie . srodowisko
         [sorted-env (sort-env (second decomposed-e))]) ;;posortowane srodowisko
    (make-lifted-let sorted-env (first decomposed-e))))
         
  
;;TESTY

(display "Wyrazenie1: \n")(newline)
'(+ 10 (* (let (x 7) (+ x 2)) 2))
(newline)
(let-lift '(+ 10 (* (let (x 7) (+ x 2)) 2)))

(display "\n\nWyrazenie2: \n")(newline)
'(let (x (- 2 (let (z 3) z))) (+ x 2))
(newline)
(let-lift '(let (x (- 2 (let (z 3) z))) (+ x 2)))
  
(display "\n\nWyrazenie3: \n")(newline)
'(+
  (+
   (let (x 0) (+ x (let (x 8) (+ 22 x))))
   (let (x 6) (+ x (let (x 4) (+ 22 x)))))
  (+ (let (x 6) (+ x (let (x 44) (+ 22 x))))
     (let (x 6) (+ x (let (x 44) (+ 22 x))))))
(newline)
(let-lift '(+
            (+
             (let (x 0) (+ x (let (x 8) (+ 22 x))))
             (let (x 6) (+ x (let (x 4) (+ 22 x)))))
            (+ (let (x 6) (+ x (let (x 44) (+ 22 x))))
               (let (x 6) (+ x (let (x 44) (+ 22 x)))))))
           



#| proba zrobienia globalnego iteratora

         (define zmienna 0)

         (define (nowa)
           (begin (set! zmienna (+ zmienna 1)) zmienna))

         (define (nowa-zmienna)
           (number->symbol (nowa)))

|#
