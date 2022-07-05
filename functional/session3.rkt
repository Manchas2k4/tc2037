#lang racket
(define lst '(10 9 8 7 6 5 4 3 2 1))

(define even-list
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [(= (remainder (first lst) 2) 0) (cons (first lst) (even-list (rest lst)))]
      [else (even-list (rest lst))])))

(define odd-list
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [(= (remainder (first lst) 2) 1) (cons (first lst) (odd-list (rest lst)))]
      [else (odd-list (rest lst))])))

(define ugly-numbers-list
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [(or (= (remainder (first lst) 2) 0)
           (= (remainder (first lst) 3) 0)
           (= (remainder (first lst) 5) 0)) (cons (first lst) (ugly-numbers-list (rest lst)))]
      [else (ugly-numbers-list (rest lst))])))

(define even?
  (lambda (n)
    (= (remainder n 2) 0)))

(define odd?
  (lambda (n)
    (= (remainder n 2) 1)))

(define ugly-number?
  (lambda (n)
    (or (= (remainder n 2) 0)
        (= (remainder n 3) 0)
        (= (remainder n 5) 0))))

(define redux
  (lambda (pred? lst)
    (cond
      [(empty? lst) '()]
      [(pred? (first lst)) (cons (first lst) (redux pred? (rest lst)))]
      [else (redux pred? (rest lst))])))

(define mult2
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else (cons (* 2 (first lst)) (mult2 (rest lst)))])))

(define sub1
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else (cons (- (first lst) 1) (sub1 (rest lst)))])))

(define my-map
  (lambda (fn lst)
    (cond
      [(empty? lst) '()]
      [else (cons (fn (first lst)) (my-map fn (rest lst)))])))

(define quick2
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else (append
             (quick2 (filter (lambda (n) (< n (first lst))) lst)) ;; menores => list
             (cons (first lst) '())
             (quick2 (filter (lambda (n) (> n (first lst))) lst)) ;; mayores o iguales => lst
             )])))

(define depth-list
  '( (1 2 3)
     4
     (5 (6 7 (8 9)))
     10
     (11) (12) ))

(define sum-depth-list
  (lambda (lst)
    (cond
      [(empty? lst) 0]
      [(list? (first lst)) (+ (sum-depth-list (first lst))
                              (sum-depth-list (rest lst)))]
      [(+ (first lst)
          (sum-depth-list (rest lst)))])))

(define search-depth-list
  (lambda (key lst)
    (cond
      [(empty? lst) #f]
      [(list? (first lst)) (or (search-depth-list key (first lst))
                               (search-depth-list key (rest lst)))]
      [(eq? key (first lst)) #t]
      [else (search-depth-list key (rest lst))])))

(define redux-depth-list
  (lambda (pred? lst)
    (cond
      [(empty? lst) '()]
      [(list? (first lst)) (cons (redux-depth-list pred? (first lst))
                                 (redux-depth-list pred? (rest lst)))]
      [else
       (cond
         [(pred? (first lst)) (cons (first lst) (redux-depth-list pred? (rest lst)))]
         [else (redux-depth-list pred? (rest lst))])])))

(define map-depth-list
  (lambda (fn lst)
    (cond
      [(empty? lst) '()]
      [(list? (first lst)) (cons (map-depth-list fn (first lst))
                                 (map-depth-list fn (rest lst)))]
      [else (cons (fn (first lst))
                  (map-depth-list fn (rest lst)))])))

(define bst-tree
  '(50
    (25
     (12 () ())
     (35
      (30 () ())
      (40 () ())))
    (75
     (60
      (55 () ())
      (68 () ()))
     (85
      ()
      (90 () ())))))

(define parent
  (lambda (bst-tree)
    (first bst-tree)))

(define left
  (lambda (bst-tree)
    (first (rest bst-tree))))

(define right
  (lambda (bst-tree)
    (first (rest (rest bst-tree)))))

(define post-order
  (lambda (tree)
    (cond 
      [(empty? tree) '()]
      [else (append (post-order (left tree))
                  (post-order (right tree))
                  (cons (parent tree) '()))])))

(define pre-order
  (lambda (tree)
    (cond 
      [(empty? tree) '()]
      [else (append (cons (parent tree) '())
                    (pre-order (left tree))
                    (pre-order (right tree)))])))

(define in-order
  (lambda (tree)
    (cond 
      [(empty? tree) '()]
      [else (append (in-order (left tree))
                    (cons (parent tree) '())
                    (in-order (right tree)))])))

(define depth
  (lambda (tree)
    (cond
      [(empty? tree) 0]
      [else (+ 1 (max (depth (left tree))
                      (depth (right tree))))])))

(define graph1
  '( (A B C)
     (B D)
     (C D)
     (D )))

(define graph2
  '( (A B) (A C) (B D) (C D) ))

  
















     