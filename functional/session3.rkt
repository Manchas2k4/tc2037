;; ITESM QRO
;; Author: Pedro Perez
;; Sesion 3 de Scheme

#lang racket

(define lst '(1 2 3 4 5 6 7 8 9 10))

(define redux-alt
  (lambda (fn lst)
    (cond
      [(empty? lst) '()]
      [(fn (car lst)) (cons (car lst)
                             (redux-alt fn (cdr lst)))]
      [else (redux-alt fn (cdr lst))])))

(define add1
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else (cons (+ (car lst) 1)
                  (add1 (cdr lst)))])))

(define squares
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else (cons (* (car lst) (car lst))
                  (squares (cdr lst)))])))

(define map-alt
  (lambda (fn lst)
    (cond
      [(empty? lst) '()]
      [else (cons (fn (car lst))
                  (map-alt fn (cdr lst)))])))

(define my-deep-list
  '( (1 2 3)
     4
     (5 (6 7 (8 9)))
     10
     (11 (12))))

;; deep-sum: deep-list -> deep-list
(define deep-sum
  (lambda (deep-list)
    (cond
      [(empty? deep-list) 0]
      [(not (list? (car deep-list)))
       (+ (car deep-list) (deep-sum (cdr deep-list)))]
      [else (+ (deep-sum (car deep-list))
               (deep-sum (cdr deep-list)))])))
;; example: (deep-sum my-deep-list) => 68

;; deep-search: number deep-list -> deep-list
(define deep-search
  (lambda (element deep-list)
    (cond
      [(empty? deep-list) #f]
      [(not (list? (car deep-list)))
       (or (eq? (car deep-list) element)
           (deep-search element (cdr deep-list)))]
      [else
       (or (deep-search element (car deep-list))
           (deep-search element (cdr deep-list)))])))
;; example: (deep-search 9 my-deep-list) => #t
;; example: (deep-search 100 my-deep-list) => #f

(define double-it
  (lambda (n)
    (* 2 n)))

;; deep-map: function deep-list -> deep-list
(define deep-map
  (lambda (fn deep-list)
    (cond
      [(empty? deep-list) '()]
      [(not (list? (car deep-list)))
       (cons (fn (car deep-list))
             (deep-map fn (cdr deep-list)))]
      [else
       (cons (deep-map fn (car deep-list))
             (deep-map fn (cdr deep-list)))])))
;; example: (deep-map double-it my-deep-list)

(define my-even
  (lambda (n)
    (if (eq? (remainder n 2) 0) #t #f)))

;; deep-redux: function deep-list -> deep-list
(define deep-redux
  (lambda (fn deep-list)
    (cond
      [(empty? deep-list) '()]
      [(not (list? (car deep-list)))
       (cond
         [(fn (car deep-list)) (cons (car deep-list)
                                     (deep-redux fn (cdr deep-list)))]
         [else (deep-redux fn (cdr deep-list))])]
      [else
       (cons (deep-redux fn (car deep-list))
             (deep-redux fn (cdr deep-list)))])))
;; example: (deep-redux my-even my-deep-list)

;; flatten: deep-list -> list
(define flatten
  (lambda (deep-list)
    (cond
      [(empty? deep-list) '()]
      [(not (list? (car deep-list)))
       (cons (car deep-list)
             (flatten (cdr deep-list)))]
      [else
       (append (flatten (car deep-list))
               (flatten (cdr deep-list)))])))
;; example: (flatten my-deep-list)

(define my-tree
  '(50 (25
        (12 () ())
        (37 () ()))
       (75
        (62 () ())
        (89
         (76 () ())
         (95
          (92 () ())
          (100 () ()))))))

(define parent
  (lambda (tree)
    (car tree)))

(define left
  (lambda (tree)
    (cadr tree)))

(define right
  (lambda (tree)
    (caddr tree)))

(define children
  (lambda (tree)
    (cdr tree)))

(define leaf?
  (lambda (tree)
    (and (not (empty? (parent tree)))
         (empty? (left tree))
         (empty? (right tree)))))

(define count-leaves
  (lambda (tree)
    (cond
      [(leaf? tree) 1]
      [else (+ 1
               (count-leaves (left tree))
               (count-leaves (right tree)))])))

(define depth
  (lambda (tree)
    (cond
      [(empty? tree) 0]
      [else
       (+ 1 (max (depth (left tree)) (depth (right tree))))])))

(define sum-tree
  (lambda (tree)
    (cond
      [(empty? tree) 0]
      [else (+ (parent tree)
               (sum-tree (left tree))
               (sum-tree (right tree)))])))

(define add
  (lambda (number tree)
    (cond
      [(empty? tree) (cons number '( () ()))]
      [(< number (parent tree))
       (cons (parent tree)
             (cons
              (add number (left tree))
              (cons
               (right tree) '())))]
      [(> number (parent tree))
       (cons (parent tree)
             (cons
              (left tree)
              (cons
               (add number (right tree)) '())))]
      [else
       (cons (parent tree)
             (cons
              (left tree)
              (cons
               (right tree) '())))])))

