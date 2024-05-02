#lang racket

(define bst
  '(8
    (5 (2 () ())
       (7 () ()))
    (12 ()
       (15 (11 () ())
           ()))))

(define parent
  (lambda (tree)
    (car tree)))

(define left
  (lambda (tree)
    (cadr tree)))

(define right
  (lambda (tree)
    (caddr tree)))

(define find
  (lambda (key tree)
    (cond
      ((null? tree) #f)
      ((equal? key (parent tree)) #t)
      ((< key (parent tree)) (find key (left tree)))
      (else (find key (right tree))))))

(define preorder
  (lambda (tree)
    (cond
      ((null? tree) '())
      (else (cons (parent tree)
                  (append (preorder (left tree))
                          (preorder (right tree))))))))


(define add
  (lambda (key tree)
    (cond
      ((null? tree) (cons key '(() ())))
      ((< key (parent tree)) (list (parent tree)
                                   (add key (left tree))
                                   (right tree)))
      (else (list (parent tree)
                  (left tree)
                  (add key (right tree)))))))
      






















