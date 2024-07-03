#lang racket

(define bst
  '(8
    (5 (2 () ()) (7 () ()))
    (9 ()        (15 (11 () ()) ()))))

(define parent
  (lambda (tree)
    (car tree)))

(define left
  (lambda (tree)
    (cadr tree)))

(define right
  (lambda (tree)
    (caddr tree)))

(define search
  (lambda (number tree)
    (cond
      [(null? tree) #f]
      [(= number (parent tree)) #t]
      [(< number (parent tree)) (search number (left tree))]
      [else (search number (right tree))])))

(define preorder
  (lambda (tree)
    (cond
      [(not (empty? tree))
       (begin
         (writeln (parent tree))
         (preorder (left tree))
         (preorder (right tree)))])))


(define add
  (lambda (val tree)
    (cond
      [(null? tree) (list val '() '())]
      [(< val (parent tree))
       (if (empty? (left tree))
           (cons (parent tree)
                 (cons (list val '() '())
                       (list (right tree))))
           (cons (parent tree)
                 (cons (add val (left tree))
                       (list (right tree)))))]
      [else
       (if (empty? (right tree))
           (cons (parent tree)
                 (cons (left tree)
                       (list (list val '() '()))))
           (cons (parent tree)
                 (cons (left tree)
                       (list (add val (right tree))))))]
      )))














  