#lang racket


(define (make-queue) (mcons null null ))

(define (front-ptr queue) (mcar queue))
(define (rear-ptr queue) (mcdr queue))

(define (set-front-ptr! queue item) (set-mcar! queue item))
(define (set-rear-ptr! queue item) (set-mcdr! queue item))

(define (empty-queue? queue)
  (null? (front-ptr queue)))

(define (front-queue queue)
  (if (empty-queue? queue)
      (error "front called on empty queue" queue)
      (mcar (front-ptr queue))))

(define (insert-queue! queue item)
  (let ((new-pair (mcons item null)))
    (cond [(empty-queue? queue)
           (set-front-ptr! queue new-pair)
           (set-rear-ptr! queue new-pair)
           queue]
          [else
           (set-mcdr! (rear-ptr queue) new-pair)
           (set-rear-ptr! queue new-pair)
           queue])))

(define (delete-queue! queue)
  (cond [(empty-queue? queue)
         (error "delete on empty queue")]
        [else
         (set-front-ptr! queue (mcdr (front-ptr queue)))
         queue]))

(define q (make-queue))
(display "kolejka: \n")
q
(display "dodajemy \n")
(insert-queue! q 1)
(insert-queue! q 2)

  