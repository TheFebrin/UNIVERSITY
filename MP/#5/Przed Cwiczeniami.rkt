#lang racket

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
           (prop? (disj-rght f)))
      (and (conj? f)
           (prop? (conj-left f))
           (prop? (conj-rght f)))))



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
 
(define (disj-rght f)
  (caddr f))
 
(define (conj-left f)
  (cadr f))
 
(define (conj-rght f)
  (caddr f))

;;***  ZAD 2  ***************************************************

(define (free-vars f)
  (cond [(var? f) (list f)]
        [(neg? f) (free-vars (neg-subf f))]
        [(conj? f) (remove-duplicates
                    (append (free-vars (conj-left f))
                           (free-vars (conj-rght f))))]
        [(disj? f)(remove-duplicates
                   (append (free-vars (disj-left f))
                           (free-vars (disj-rght f))))]
        [else (display "ERROR!")]))

;;*** ZAD 3  ****************************************************


(define (gen-vals xs) ;zbior wszystkich wartosciowan
  (if (null? xs)
      '()
      (let*
          ((vss (gen-vals (cdr xs)))
           (x (car xs))
           (vst (map (lambda (vs) (cons (list x true) vs)) vss))
           (vsf (map (lambda (vs) (cons (list x false) vs)) vss)))
        (append vst vsf))))


(define (falsifiable-eval? xs)
      (cond [(null? xs) false]
            [(eq? 'conj (caaar xs))]
            [(eq? 'disj (caaar xs))]
            [(eq? 'neg (caaar xs))]

            ))

(define (search x xs)
  (cond [(null? xs) false]
        [(equal? x (cadaar xs)) (car xs)]
        [else (search x (cdr xs))]))
      
 (define x '(('a 2) ('b 2) ('x 5)))
  
(define test (conj (disj 'a 'b)
                     (disj 'b 'd)))

(define w '( ('a #t) ('b #f)))


(define (eval-formula f w)


;;***  ZAD 4  *****************************************************

  
  



  

