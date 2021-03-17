#lang racket

(define my-deep-list
  '( (1 2 3)
     4
     (5 (6 7 (8 9)))
     10
     (11 (12))))

;; (flatten my-deep-list) => '(1 2 3 4 5 6 7 8 9 10 11 12)

(define my-list '(1 2 3 4 5))

(define deep-sum
  (lambda (deep-list)
    (cond
      [(null? deep-list) 0]
      [(list? (car deep-list)) (+ (deep-sum (car deep-list))
                                  (deep-sum (cdr deep-list)))]
      [else (+ (car deep-list)
               (deep-sum (cdr deep-list)))])))

(define deep-search
  (lambda (element deep-list)
    (cond
      [(null? deep-list) #f]
      [(list? (car deep-list)) (or (deep-search element (car deep-list))
                                   (deep-search element (cdr deep-list)))]
      [else (or (eq? element (car deep-list))
                (deep-search element (cdr deep-list)))])))

(define deep-map
  (lambda (fn deep-list)
    (cond
      [(null? deep-list) '()]
      [(list? (car deep-list)) (cons (deep-map fn (car deep-list))
                                     (deep-map fn (cdr deep-list)))]
      [else (cons (fn (car deep-list))
                  (deep-map fn (cdr deep-list)))])))

(define my-flatten
  (lambda (deep-list)
    (cond
      [(null? deep-list) '()]
      [(list? (car deep-list)) (append (my-flatten (car deep-list))
                                       (my-flatten (cdr deep-list)))]
      [else (cons (car deep-list)
                  (my-flatten (cdr deep-list)))])))


(define deep-reduce
  (lambda (fn deep-list)
    (cond
      [(null? deep-list) '()]
      [(list? (car deep-list)) (cons (deep-reduce fn (car deep-list))
                                     (deep-reduce fn (cdr deep-list)))]
      [else
       (cond
         [(fn (car deep-list)) (cons (car deep-list)
                                     (deep-reduce fn (cdr deep-list)))]
         [else (deep-reduce fn (cdr deep-list))])])))

(define bst-tree
  '(50 (25
        (12 () ())
        (35
         (30 () ())
         (40 () ())))
       (75
        (60
         (55 () ())
         (68
          ()
          (70 () ())))
        (85 () ()))))

(define parent
  (lambda (tree)
    (car tree)))

(define left
  (lambda (tree)
    (cadr tree))) ;; (car (cdr tree))

(define right
  (lambda (tree)
    (caddr tree))) ;; (car (cdr (cdr tree)))

(define leaf?
  (lambda (tree)
    (or (null? tree)
        (and (not (list? (car tree)))
         (null? (left tree))
         (null? (right tree))))))

(define depth
  (lambda (tree)
    (cond
      [(leaf? tree) 0]
      [else (+ 1
               (max (depth (left tree))
                    (depth (right tree))))])))

(define post-order
  (lambda (tree)
    (cond
      [(null? tree) '()]
      [else (append (post-order (left tree))
                    (post-order (right tree))
                    (cons (parent tree) '()))])))

(define sum-tree
  (lambda (tree)
    (cond
      [(null? tree) 0]
      [else (+ (parent tree)
               (sum-tree (left tree))
               (sum-tree (right tree)))])))

(define my-dictionary
  '( (a 10)
     (b 20)
     (c 30)))

(define key
  (lambda (a-pair)
    (car a-pair)))

(define value
  (lambda (a-pair)
    (cadr a-pair)))

(define make-pair
  (lambda (key value)
    (cons key (cons value '()))))

(define keys
  (lambda (dictionary)
    (cond
      [(null? dictionary) '()]
      [else (cons (key (car dictionary))
                  (keys (cdr dictionary)))])))

(define my-graph
  '(
    (A (B C))
    (B (D))
    (C (D))
    (D ())))

(define get-label
  (lambda (node)
    (car node)))

(define get-list
  (lambda (node)
    (cadr node)))

(define look-up
  (lambda (label graph)
    (cond
      [(null? graph) #f]
      [(eq? label (get-label (car graph))) (get-list (car graph))]
      [else (look-up label (cdr graph))])))

