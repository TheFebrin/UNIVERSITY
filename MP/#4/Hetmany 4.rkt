#lang racket

(define (concatMap f xs)
  (if (null? xs)
      null
      (append (f (car xs)) (concatMap f (cdr xs)))))

(define (from-to s e)
  (if (= s e)
      (list s)
      (cons s (from-to (+ s 1) e))))


(define (queens board-size)
;; Return the representation of a board with 0 queens inserted
  
  (define (empty-board) '())
;; Return the representation of a board with a new queen at
;; (row, col) added to the partial representation `rest'
  (define (adjoin-position row col rest)
    (cons (cons col row) rest))
  
  (define (col queen-setup-pair) ;; column selector
    (car queen-setup-pair))
  
  (define (row queen-setup-pair) ;; row selector
    (cdr queen-setup-pair))
    
;; Return true if the queen in k-th column does not attack any of
;; the others
  
(define (safe? k positions)
  (define (check? lista akt k)
    (cond [(null? lista) true]
        [(or
          (= akt (row (car lista)))
          (= (+ (col (car lista)) (row (car lista))) (+ k akt))
          (= (- (col (car lista)) (row (car lista))) (- k akt))
          )
          false]
[else (check? (cdr lista) akt k)]))
  (check? (cdr positions) (cdr(car positions)) 1))

      

;; Return a list of all possible solutions for k first columns

(define (queen-cols k)
  (if (= k 0)
      (list (empty-board))
      (filter
       (lambda (positions) (safe? k positions))
       (concatMap
        (lambda (rest-of-queens)
          (map (lambda (new-row)
                 (adjoin-position new-row k rest-of-queens))
               (from-to 1 board-size)))
        (queen-cols (- k 1))))))
  (queen-cols board-size))