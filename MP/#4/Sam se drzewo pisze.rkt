#lang racket

(define (make-node val left right)
  (list val left right))

(define (node-val t)
  (first t))

(define (node-left t)
  (second t))

(define (node-right t)
  (third t))

(define t (make-node 1
                     (make-node 2 null null) (make-node 3 null null)))
                                

               
