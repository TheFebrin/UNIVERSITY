#lang racket

;; sygnatura: grafy
(define-signature graph^
  ((contracted
    [graph        (-> list? (listof edge?) graph?)]
    [graph?       (-> any/c boolean?)]
    [graph-nodes  (-> graph? list?)]
    [graph-edges  (-> graph? (listof edge?))]
    [edge         (-> any/c any/c edge?)]
    [edge?        (-> any/c boolean?)]
    [edge-start   (-> edge? any/c)]
    [edge-end     (-> edge? any/c)]
    [has-node?    (-> graph? any/c boolean?)]
    [outnodes     (-> graph? any/c list?)]
    [remove-node  (-> graph? any/c graph?)]
    )))

;; prosta implementacja grafów
(define-unit simple-graph@
  (import)
  (export graph^)

  (define (graph? g)
    (and (list? g)
         (eq? (length g) 3)
         (eq? (car g) 'graph)))

  (define (edge? e)
    (and (list? e)
         (eq? (length e) 3)
         (eq? (car e) 'edge)))

  (define (graph-nodes g) (cadr g))

  (define (graph-edges g) (caddr g))

  (define (graph n e) (list 'graph n e))

  (define (edge n1 n2) (list 'edge n1 n2))

  (define (edge-start e) (cadr e))

  (define (edge-end e) (caddr e))

  (define (has-node? g n) (not (not (member n (graph-nodes g)))))
  
  (define (outnodes g n)
    (filter-map
     (lambda (e)
       (and (eq? (edge-start e) n)
            (edge-end e)))
     (graph-edges g)))

  (define (remove-node g n)
    (graph
     (remove n (graph-nodes g))
     (filter
      (lambda (e)
        (not (eq? (edge-start e) n)))
      (graph-edges g)))))

;; sygnatura dla struktury danych
(define-signature bag^
  ((contracted
    [bag?       (-> any/c boolean?)]
    [bag-empty? (-> bag? boolean?)]
    [empty-bag  (and/c bag? bag-empty?)]
    [bag-insert (-> bag? any/c (and/c bag? (not/c bag-empty?)))]
    [bag-peek   (-> (and/c bag? (not/c bag-empty?)) any/c)]
    [bag-remove (-> (and/c bag? (not/c bag-empty?)) bag?)])))

;; struktura danych - stos
(define-unit bag-stack@
  (import)
  (export bag^)

  (define (bag? b)
    (and (eq? (car b) 'stos)
         (list? b)))

  (define (bag-stack b)
    (second b))

  (define (make-stack b)
    (list 'stos b))
  
  (define (bag-empty? b)
    (null? (bag-stack b)))
  
  (define empty-bag
    (make-stack null))

  (define (bag-insert b x)
    (make-stack (cons x
                      (bag-stack b))))

  (define (bag-peek b)
    (car (bag-stack b)))

  (define (bag-remove b)
    (make-stack (cdr (bag-stack b))))
  ;; TODO: zaimplementuj stos
  )

;; struktura danych - kolejka FIFO
;; do zaimplementowania przez studentów
(define-unit bag-fifo@
  (import)
  (export bag^)

  (define (bag? b)  ;; bag bedzie lista trzy elementowa, gdzie pierwszy element
    (and (list? b)  ;; to tag, drugi to nasza lista wejsciowa, a trzeci to wyjsciowa
         (= (length b) 3)
         (eq? (car b) 'kolejka)))
    

  (define (lista-wejsciowa b)
    (second b))

  (define (lista-wyjsciowa b)
    (third b))

  (define (make-queue w1 w2)
    (list 'kolejka w1 w2))
  
  (define (bag-empty? b)
    (and (null? (lista-wejsciowa b))
         (null? (lista-wyjsciowa b))))

  (define empty-bag
    (make-queue null null))

  (define (bag-insert b x)
    (make-queue (cons x (lista-wejsciowa b))
                (lista-wyjsciowa b)))

  (define (bag-peek b)
    (if (null? (lista-wyjsciowa b))
        (car (reverse (lista-wejsciowa b)))
        (car (lista-wyjsciowa b))))

  (define (bag-remove b)
    (if (null? (lista-wyjsciowa b)) ;;lista wyjsciowa jest pusta
        
        (make-queue null      ;;wrzucam tam odwrocona wejsciowa i zeruje wejsciowa
                    (cdr (reverse (lista-wejsciowa b))))
        
        (make-queue (lista-wejsciowa b)   ;;lista wyjsciowa NIE jest pusta
                    (cdr (lista-wyjsciowa b)))))

        
  ;; TODO: zaimplementuj kolejkę
  )

;; sygnatura dla przeszukiwania grafu
(define-signature graph-search^
  (search))

;; implementacja przeszukiwania grafu
;; uzależniona od implementacji grafu i struktury danych
(define-unit/contract graph-search@
  (import bag^ graph^)
  (export (graph-search^
           [search (-> graph? any/c (listof any/c))]))
  (define (search g n)
    (define (it g b l)
      (cond
        [(bag-empty? b) (reverse l)]
        [(has-node? g (bag-peek b))
         (it (remove-node g (bag-peek b))
             (foldl
              (lambda (n1 b1) (bag-insert b1 n1))
              (bag-remove b)
              (outnodes g (bag-peek b)))
             (cons (bag-peek b) l))]
        [else (it g (bag-remove b) l)]))
    (it g (bag-insert empty-bag n) '()))
  )

;; otwarcie komponentu grafu
(define-values/invoke-unit/infer simple-graph@)

;; graf testowy
(define test-graph
  (graph
   (list 1 2 3 4)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4))))
;; TODO: napisz inne testowe grafy!

(define test-graph2
  (graph
   (list 1 2 3 4 5 6 7 8 9 10)
   (list (edge 1 2)
         (edge 1 3)
         (edge 1 4)
         (edge 1 5)
         (edge 1 6)
         (edge 1 7)
         (edge 7 8)
         (edge 8 9)
         (edge 8 10)
         (edge 4 10)
         (edge 3 9))))

(define test-graph3
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 2)
         (edge 2 3)
         (edge 3 4)
         (edge 4 5)
         (edge 5 1)
         (edge 2 4))))

(define test-graph4
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 2)
         (edge 2 3)
         (edge 3 1)
         (edge 4 5)
         (edge 5 4))))


(define test-graph5
  (graph
   (list 1 2 3 4 5)
   (list (edge 1 1)
         (edge 2 3)
         (edge 3 1)
         (edge 4 5)
         (edge 5 4))))
;; otwarcie komponentu stosu            <<<<<-------------- KOMPONENTY --------------------
;(display "KOMPONENT STOSU \n")
;(define-values/invoke-unit/infer bag-stack@)

;; opcja 2: otwarcie komponentu kolejki
(display "KOMPONENT KOLEJKI \n")
(define-values/invoke-unit/infer bag-fifo@)

;; testy w Quickchecku
(require quickcheck)

;; [TEST 1] - ogolny
;; przykładowy: jeśli do pustej struktury dodamy element
;; i od razu go usuniemy, wynikowa struktura jest pusta
(display "Test 1:  ")
(quickcheck
 (property ([s arbitrary-symbol])
           (bag-empty? (bag-remove (bag-insert empty-bag s)))))

;; [TEST 2] - ogolny
;; jesli dodamy element do pustej struktury
;; i wywolamy bag-peek to dostaniemy ten element
(display "Test 2:  ")
(quickcheck
 (property ([s arbitrary-symbol])
           (eq? s (bag-peek (bag-insert empty-bag s)))))

;; [TEST 3] - dla kolejki
;; wrzucam dwa elementy do pustej koleji, usuwam jeden (front) i patrze czy
;; bag-peek zwroci mi ten drugi
(display "Test 3 (kolejka):  ")
(quickcheck
 (property ([s arbitrary-symbol]
            [q arbitrary-symbol])
  
           (eq? (bag-peek
                 (bag-remove
                  (bag-insert
                   (bag-insert empty-bag s) q)))
                q)))

;; [TEST 4] - dla stosu
;; wrzucam dwa elementy do pustego stosu, usuwam jeden i patrze czy
;; bag-peek zwroci mi ten wrzucony pierwszy
(display "Test 4 (stos):  ")
(quickcheck
 (property ([s arbitrary-symbol]
            [q arbitrary-symbol])
           (eq? (bag-peek
                 (bag-remove
                  (bag-insert
                   (bag-insert empty-bag s) q)))
                s)))

;; [TEST 5]
;; dodanie 2 elementow, a potem usuniecie 2 da pusta strukture
(display "Test 5:  ")
(quickcheck
 (property ([s arbitrary-symbol]
            [q arbitrary-symbol])
           (bag-empty?
            (bag-remove
             (bag-remove
              (bag-insert
               (bag-insert empty-bag s) q))))))



;; TODO: napisz inne własności do sprawdzenia!
;; jeśli jakaś własność dotyczy tylko stosu lub tylko kolejki,
;; wykomentuj ją i opisz to w komentarzu powyżej własności

;; otwarcie komponentu przeszukiwania
(define-values/invoke-unit/infer graph-search@)

;; uruchomienie przeszukiwania na przykładowym grafie
(display "Tests on graphs: \n")
(search test-graph 1)
(search test-graph2 1)
(search test-graph3 1)
(search test-graph4 1)
(search test-graph5 1)
;; TODO: uruchom przeszukiwanie na swoich przykładowych grafach!