#lang racket

(define aplica
  (lambda (fn a b)
    (fn a b)))

(define tipo
  (lambda (n)
    (cond
      [(= n 1) +]
      [(= n 2) -]
      [(= n 3) *]
      [else /])))

(define insert
  (lambda (element lst cmp)
    (cond
      [(null? lst) (list element)]
      [(cmp element (car lst)) (cons element lst)]
      [else (cons (car lst)
                  (insert element (cdr lst) cmp))])))

(define insertion-sort
  (lambda (lst cmp)
    (cond
     [(null? lst) '()]
     [else (insert (car lst)
                   (insertion-sort (cdr lst) cmp)
                   cmp)])))

(define lst '(1 3 5 7))
(define unordered-list '(9 6 4 8 10 1 2 7 5 3))

(define m '((1 2 3)
            (4 5 6)
            (7 8 9)))

(define sum-matrix
  (lambda (m)
    (apply +
           (map (lambda (a) (apply + a)) m))))

(define transpose
  (lambda (m)
    (apply map list m)))

(define other-list
  '((1) (2 3 4) (4 5 6 7 6) () (3 2)))


(define genera-fn-incremento
  (lambda (inc)
    (lambda (value)
      (+ value inc))))

(define genera-fn-two-apply
  (lambda (value)
    (lambda (fn)
      (fn (fn value)))))






















 