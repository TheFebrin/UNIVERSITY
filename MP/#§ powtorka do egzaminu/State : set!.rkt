#lang racket

(define (make-account balance password)

  (define withdraw
     (lambda (amount)
    (if (<= amount balance)
        (begin (set! balance (- balance amount))
               (display balance))
        (display "Not enought founds"))))

  (define deposit
     (lambda (amount)
        (begin (set! balance (+ balance amount))
               (display balance))))

  (define (dispatch m pass)
    (if (eq? password pass)
        (cond [(eq? m 'withdraw) withdraw]
              [(eq? m 'deposit) deposit])
        (error "Wrong password!!!")))

  dispatch)


(define a (make-account 1000 'racket))

;;Licznik
   
(define make-counter 
  (let ([counter 0])
    (cons
     (lambda () (begin (set! counter (+ 1 counter)) counter))
     (lambda () (set! counter -1)))))

(define counter make-counter)
(define next (car counter))
(define reset (cdr counter))


;; set-car!

(define (cons! x y)
  (define (set-x! v) (set! x v))
  (define (set-y! v) (set! y v))
  (define (dispatch m)
    (cond ((eq? m 'car) x)
          ((eq? m 'cdr) y)
          ((eq? m 'set-car!) set-x!)
          ((eq? m 'set-cdr!) set-y!)
          (else (error "Undefined operation -- CONS" m))))
  dispatch)

(define (car1 z) (z 'car))
(define (cdr1 z) (z 'cdr))

(define (set-car! z new-value)
  ((z 'set-car!) new-value)
  z)

(define (set-cdr! z new-value)
  ((z 'set-cdr!) new-value)
  z)

;;QUEUE



(define (front-ptr queue) (mcar queue))
(define (rear-ptr queue) (mcdr queue))
(define (set-front-ptr! queue item) (set-mcar! queue item))
(define (set-rear-ptr! queue item) (set-mcdr! queue item))

(define (empty-queue? queue) (null? (front-ptr queue)))

(define (make-queue) (mcons '() '()))

(define (front-queue queue)
  (if (empty-queue? queue)
      (error "FRONT called with an empty queue" queue)
      (mcar (front-ptr queue))))

(define (insert-queue! queue item)
  (let ((new-pair (mcons item '())))
    (cond ((empty-queue? queue)
           (set-front-ptr! queue new-pair)
           (set-rear-ptr! queue new-pair)
           queue)
          (else
           (set-mcdr! (rear-ptr queue) new-pair)
           (set-rear-ptr! queue new-pair)
           queue))))

(define (delete-queue! queue)
  (cond ((empty-queue? queue)
         (error "DELETE! called with an empty queue" queue))
        (else
         (set-front-ptr! queue (mcdr (front-ptr queue)))
         queue)))


;;

(define (histogram-list l)
  (foldl (lambda (n l) (list-update l n (lambda (k) (+ k 1))))
         (build-list (+ (apply max l) 1)
                     (lambda (k) 0))
         l))

(define (histogram-vec l)
  (define v (make-vector (+ (apply max l) 1) 0))
  (for-each (lambda (n) (vector-set! v n (+ 1(vector-ref v n)))) l)
  (vector->list v))


;; leniwe listy

;; spamiętywanie

(define (memo-proc proc) 
  (let ((already-run? false) (result false))
    (lambda ()
      (if (not already-run?)
          (begin (set! result (proc))
                 (set! already-run? true)
                 result)
          result))))



;; alternatywna implementacja wykorzystująca listy modyfikowalne

(define (lcons x f)
  (mcons x f))

(define (lhead l)
  (mcar l))

(define (ltail l)
  (when (procedure? (mcdr l))
      (set-mcdr! l ((mcdr l))))
  (mcdr l))

;; dodatkowy przykład: liczby pierwsze

(define (integers-starting-from n)
  (lcons n (lambda () (integers-starting-from (+ n 1)))))

(define naturals (integers-starting-from 0))

(define (divisible? x y) (= (remainder x y) 0))

