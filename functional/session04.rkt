#lang racket

(define m1 '((1 2 3)
             (4 5 6)
             (7 8 9)))

(define add-row
  (lambda (row1 row2)
    (cond
      ((null? row1) '())
      (else (cons (+ (car row1) (car row2))
                  (add-row (cdr row1) (cdr row2)))))))

(define add-matrix
  (lambda (m1 m2)
    (cond
      ((null? m1) '())
      (else (cons (add-row (car m1) (car m2))
                  (add-matrix (cdr m1) (cdr m2)))))))

(define my-tree
  '(8 (5 (2 () ())
         (7 () ()))
      (9 ()
         (15 (11 () ())
             ()))))

;; -------------------------------------------------------- ;;

(define parent
  (lambda (abb)
    (car abb)))

(define left
  (lambda (abb)
    (cadr abb)))

(define right
  (lambda (abb)
    (caddr abb)))

(define preorder
  (lambda (tree)
    (cond
      ((not (null? tree))
       (begin
         (writeln (parent tree))
         (preorder (left tree))
         (preorder (right tree)))))))

(define make-leaf
  (lambda (number)
    (list number '() '())))

(define insert
  (lambda (key tree)
    (cond
      ((null? tree) (make-leaf key))
      ((< key (parent tree))
       (if (null? (left tree))
           (list (parent tree) (make-leaf key) (right tree))
           (list (parent tree) (insert key (left tree)) (right tree))))
      ((> key (parent tree))
       (if (null? (right tree))
           (list (parent tree) (left tree) (make-leaf key))
           (list (parent tree) (left tree) (insert key (right tree))))))))

;; -------------------------------------------------------- ;;

(define aplica
  (lambda (fn a b)
    (fn a b)))

(define tipo
  (lambda (n)
    (cond
      ((= n 1) +)
      ((= n 2) -)
      ((= n 3) *)
      (else /))))

(define LF (list + - * /))

(define sum-matrix 
  (lambda (m1)
    (apply + (map (lambda (row) (apply + row)) m1))))

(define transpose
  (lambda (m1)
    (apply map list m1)))

(define create-random-list
  (lambda (amount)
    (cond
      ((eq? amount 0) '())
      (else (cons (random 100) (create-random-list (sub1 amount)))))))

(define aux (create-random-list 20))

(define quicksort
  (lambda (lst)
    (cond
      ((null? lst) '())
      (else (append
             (quicksort (filter (lambda (n) (< n (car lst))) (cdr lst)))
             (list (car lst))
             (quicksort (filter (lambda (n) (>= n (car lst))) (cdr lst))))))))

;; -------------------------------------------------------- ;;

(define fact1
  (lambda (n)
    (cond
      ((= n 1) 1)
      (else (* n (fact1 (sub1 n)))))))

(define fact2
  (lambda (n)
    (fact2-aux n 1)))

(define fact2-aux
  (lambda (n acc)
    (cond
      ((= n 1) acc)
      (else (fact2-aux (sub1 n) (* n acc))))))

(define ce1
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((even? (car lst)) (+ 1 (ce1 (cdr lst))))
      (else (ce1 (cdr lst))))))

(define ce2
  (lambda (lst)
    (ce2-aux lst 0)))

(define ce2-aux
  (lambda (lst acc)
    (cond
      ((null? lst) acc)
      ((even? (car lst)) (ce2-aux (cdr lst) (add1 acc)))
      (else (ce2-aux (cdr lst) acc)))))

(define crl1
  (lambda (amount)
    (cond
      ((eq? amount 0) '())
      (else (cons (random 100) (crl1 (sub1 amount)))))))

(define crl2
  (lambda (amount)
    (crl2-aux amount '())))

(define crl2-aux
  (lambda (amount acc)
    (cond
      ((eq? amount 0) acc)
      (else (crl2-aux (sub1 amount) (cons (random 100) acc))))))
