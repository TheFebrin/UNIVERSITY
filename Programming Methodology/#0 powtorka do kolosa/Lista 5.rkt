#lang racket

;;Dejwo to ziomal ®©

(define (var? t)
  (symbol? t))

(define (neg? t)
  (and (list? t)
       (= 2 (length t))
       (eq? 'neg (car t))))

(define (conj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'conj (car t))))

(define (disj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'disj (car t))))

(define (prop? f)
  (or (var? f)
      (and (neg? f)
           (prop? (neg-subf f)))
      (and (disj? f)
           (prop? (disj-left f))
           (prop? (disj-right f)))
      (and (conj? f)
           (prop? (conj-left f))
           (prop? (conj-right f)))))

(define (var x) x)

(define (neg p) 
  (list 'neg p))

(define (conj p q)
  (list 'conj p q))

(define (disj p q)
  (list 'disj p q))

(define (neg-subf f)
  (cadr f))
 
(define (disj-left f)
  (cadr f))
 
(define (disj-right f)
  (caddr f))
 
(define (conj-left f)
  (cadr f))
 
(define (conj-right f)
  (caddr f))


;;***  ZAD 2  ********************************************************************

(define (free-vars formula)
  (cond [(var? formula) (list (var formula))]
        [(neg? formula) (free-vars (neg-subf formula))]
        [(conj? formula) (remove-duplicates
                          (append
                         (free-vars (conj-left formula))
                         (free-vars (conj-right formula))))]
        [(disj? formula) (remove-duplicates
                          (append
                          (free-vars (disj-left formula))
                          (free-vars (disj-right formula))))]
        [else (display "The ting went wrong")]))


(define f (disj
           (neg
            (conj 'a 'b))
           (disj
            'c (conj 'a 'd))))

(define f2 (conj
            (disj 'p 'q)
            (disj 'r 's)))

;;*** ZAD 3   ********************************************************************


(define (gen-vals xs) ;zbior wszystkich wartosciowan
  (if (null? xs)
      '(())
      (let*
          ((vss (gen-vals (cdr xs)))
           (x (car xs))
           (vst (map (lambda (vs) (cons (list x true) vs)) vss))
           (vsf (map (lambda (vs) (cons (list x false) vs)) vss)))
        (append vst vsf))))

(define env '((a  #t) (b  #t) (c  #f) (d  #f)))
(define env2 '((p . #t) (q . #t) (r . #f) (s . #f)))

(define (find x env)
  (cond [(null? env) (display "Variable not found!")]
        [(eq? x (caar env)) (cadar env)]
        [else (find x (cdr env))]))
  

(define (eval-formula formula vals)
  (cond [(var? formula) (find (var formula) vals)]
        [(neg? formula) (not (eval-formula (neg-subf formula) vals))]
        [(conj? formula) (and (eval-formula (conj-left formula) vals)
                              (eval-formula (conj-right formula) vals))]
        [(disj? formula) (or (eval-formula (disj-left formula) vals)
                              (eval-formula (disj-right formula) vals))]
                       
        [else (display "Someting went wrong bruv")]))


(define (falsifiable-eval? formula)
  (define (false-iter all-vals)
    (cond [(null? all-vals) false]

          [(eval-formula formula (car all-vals))
           (false-iter (cdr all-vals))]
          
          [else (car all-vals)]))
  (false-iter (gen-vals (free-vars formula))))
    

;;*** ZAD 4  ********************************************************************


(define (literal? f)  ;;predykat dla literału
  (or 
   (var? f) ;;moze byc zmienna 
   (and (neg? f) (var? (neg-subf f)))))  ;;albo negacja zmiennej


(define (nnf? formula)
  (cond [(disj? formula) (and (nnf? (conj-left formula)) (nnf? (conj-right formula)))]
        [(conj? formula) (and (nnf? (disj-left formula)) (nnf? (disj-right formula)))]
        [(neg? formula) (literal? formula)]))
           
  
(define nnf (conj
             (neg 'p) (disj (neg 'q) (neg 'r))))

(define nnf2 (conj
             (neg 'p) (neg
                       (disj (neg 'q) (neg 'r)))))
;;*** ZAD 5  ********************************************************************

(define (convert-to-nnf formula)

  (define (neg-formula formula)
  (cond [(var? formula) (neg formula)]
        [(neg? formula) (convert-to-nnf (neg-subf formula))]
        [(disj? formula) (conj (neg-formula (disj-left formula))
                               (neg-formula (disj-right formula)))]
        [(conj? formula) (disj (neg-formula (conj-left formula))
                               (neg-formula (conj-right formula)))]))

  (cond [(var? formula) formula]
        [(neg? formula) (neg-formula (neg-subf formula))]
        [(conj? formula) (conj (convert-to-nnf (conj-left formula))
                               (convert-to-nnf (conj-right formula)))]
        [(disj? formula) (disj (convert-to-nnf (disj-left formula))
                               (convert-to-nnf (disj-right formula)))]))
        
  
;;*** ZAD 6  ********************************************************************


;jebac cnfa