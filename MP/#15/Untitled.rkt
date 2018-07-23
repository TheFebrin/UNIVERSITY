#lang racket

;; współbieżne uruchomienie funkcji

(define (run-concurrent . thunks)
  (define threads (map thread thunks))
  (for-each thread-wait threads))

;(define a (run-concurrent (lambda () (sleep 0.1)) (lambda () (sleep 0.5))))
;(define b (run-concurrent (lambda () (sleep 0.5)) (lambda () (sleep 0.1))))

;; zwykłe, nieprzystosowane do współbieżności konto bankowe

(define (random-sleep)
  (sleep (/ (random) 100)))

(define (with-random-sleep proc)
  (lambda args
    (random-sleep)
    (apply proc args)))

(define (make-account balance)
  (define (withdraw amount)
    (random-sleep)
    (if (>= balance amount)
        (begin (set! balance ((with-random-sleep -) balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (random-sleep)
    (set! balance ((with-random-sleep +) balance amount))
    balance)
  (define (dispatch m)
    (cond [(eq? m 'withdraw) withdraw]
          [(eq? m 'deposit) deposit]
          [(eq? m 'balance) balance]
          [else (error "Unknown request -- MAKE-ACCOUNT"
                       m)]))
  dispatch)

(define acc (make-account 100))

;(run-concurrent
; (lambda ()
;   (for ([i (in-range 100)])
;     ((acc 'deposit) 1)))
; (lambda ()
;   (for ([i (in-range 100)])
;     ((acc 'withdraw) 1))))

;(acc 'balance)

;; synchronizacja funkcji

(define (make-serializer)
  (define sem (make-semaphore 1))
  (lambda (proc)
    (lambda args
      (semaphore-wait sem)
      (define ret (apply proc args))
      (semaphore-post sem)
      ret)))

;; konto z synchronizacją

(define (make-account-serialized balance)
  (define (withdraw amount)
    (random-sleep)
    (if (>= balance amount)
        (begin (set! balance ((with-random-sleep -) balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (random-sleep)
    (set! balance ((with-random-sleep +) balance amount))
    balance)
  (define protected (make-serializer))
  (define (dispatch m)
    (cond [(eq? m 'withdraw) (protected withdraw)]
          [(eq? m 'deposit) (protected deposit)]
          [(eq? m 'balance) balance]
          [else (error "Unknown request -- MAKE-ACCOUNT"
                       m)]))
  dispatch)

(define sacc (make-account-serialized 100))

;(run-concurrent
; (lambda ()
;   (for ([i (in-range 100)])
;     ((sacc 'deposit) 1)))
; (lambda ()
;   (for ([i (in-range 100)])
;     ((sacc 'withdraw) 1))))
;
;(sacc 'balance)

;; zamiana wartości na koncie

(define (exchange account1 account2)
  (let ([difference (- (account1 'balance)
                       (account2 'balance))])
    ((account1 'withdraw) difference)
    ((account2 'deposit) difference)))

(define sacc2 (make-account-serialized 90))
(define sacc3 (make-account-serialized 80))

;(run-concurrent
; (lambda ()
;   (exchange sacc sacc2))
; (lambda ()
;   (exchange sacc2 sacc3)))

;(sacc 'balance)
;(sacc2 'balance)
;(sacc3 'balance)

;; konta z zewnętrzną synchronizacją

(define (make-account-with-serializer balance)
  (define (withdraw amount)
    (random-sleep)
    (if (>= balance amount)
        (begin (set! balance ((with-random-sleep -) balance amount))
               balance)
        "Insufficient funds"))
  (define (deposit amount)
    (random-sleep)
    (set! balance ((with-random-sleep +) balance amount))
    balance)
  (define account-serializer (make-serializer))
  (define (dispatch m)
    (cond [(eq? m 'withdraw) withdraw]
          [(eq? m 'deposit) deposit]
          [(eq? m 'balance) balance]
          [(eq? m 'serializer) account-serializer]
          [else (error "Unknown request -- MAKE-ACCOUNT"
                       m)]))
  dispatch)

(define (serialized-deposit account amount)
  (let ([s (account 'serializer)]
        [d (account 'deposit)])
    ((s d) amount)))

(define (serialized-withdraw account amount)
  (let ([s (account 'serializer)]
        [w (account 'withdraw)])
    ((s w) amount)))

(define wsacc (make-account-with-serializer 100))

;(run-concurrent
; (lambda ()
;   (for ([i (in-range 100)])
;     (serialized-deposit wsacc 1)))
; (lambda ()
;   (for ([i (in-range 100)])
;     (serialized-withdraw wsacc 1))))

;(sacc 'balance)

(define wsacc2 (make-account-with-serializer 90))
(define wsacc3 (make-account-with-serializer 80))

(define (serialized-exchange account1 account2)
  (let ([serializer1 (account1 'serializer)]
        [serializer2 (account2 'serializer)])
    ((serializer1 (serializer2 exchange))
     account1
     account2)))

;(run-concurrent
; (lambda ()
;   (serialized-exchange wsacc wsacc2))
; (lambda ()
;   (serialized-exchange wsacc2 wsacc3)))

;(wsacc 'balance)
;(wsacc2 'balance)
;(wsacc3 'balance)

;; deadlock

(define (serialized-exchange-with-delay account1 account2)
  (let ([serializer1 (account1 'serializer)]
        [serializer2 (account2 'serializer)])
    ((serializer1 (with-random-sleep (serializer2 exchange)))
     account1
     account2)))

;(run-concurrent
; (lambda ()
;   (serialized-exchange-with-delay wsacc wsacc2))
; (lambda ()
;   (serialized-exchange-with-delay wsacc2 wsacc)))

;; unikanie deadlocków przez numerację

(define make-account-with-number
  (let ((number 0))
    (lambda (balance)
      (define account-number number)
      (set! number (+ number 1))
      (define (withdraw amount)
        (random-sleep)
        (if (>= balance amount)
            (begin (set! balance ((with-random-sleep -) balance amount))
                   balance)
            "Insufficient funds"))
      (define (deposit amount)
        (random-sleep)
        (set! balance ((with-random-sleep +) balance amount))
        balance)
      (define account-serializer (make-serializer))
      (define (dispatch m)
        (cond [(eq? m 'withdraw) withdraw]
              [(eq? m 'deposit) deposit]
              [(eq? m 'balance) balance]
              [(eq? m 'serializer) account-serializer]
              [(eq? m 'number) account-number]
              [else (error "Unknown request -- MAKE-ACCOUNT"
                           m)]))
      dispatch)))

(define (serialized-exchange-with-numbers account1 account2)
  (let ([serializer1 (account1 'serializer)]
        [serializer2 (account2 'serializer)]
        [number1 (account1 'number)]
        [number2 (account2 'number)])
    (let ([serialized-exchange
           (if (< number1 number2)
               (serializer1 (with-random-sleep (serializer2 exchange)))
               (serializer2 (with-random-sleep (serializer1 exchange))))])
      (serialized-exchange account1 account2))))

(define nsacc (make-account-with-number 100))
(define nsacc2 (make-account-with-number 90))

(run-concurrent
 (lambda ()
   (serialized-exchange-with-numbers nsacc nsacc2))
 (lambda ()
   (serialized-exchange-with-numbers nsacc2 nsacc)))



(define x 10)
(run-concurrent
 (lambda () (set! x (* x x)))
 (lambda () (set! x (* x x x))))

(define y 10)
(define s (make-serializer))
(run-concurrent
(s (lambda () (set! y (* y y))))
(s (lambda () (set! y (* y y y)))))