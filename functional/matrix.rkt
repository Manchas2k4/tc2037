#lang racket

(define m '((1 2 3)
            (4 5 6)
            (7 8 9)))

(define add-row
  (lambda (row1 row2)
    (cond
      [(null? row1) '()]
      [else (cons (+ (car row1) (car row2))
                  (add-row (cdr row1) (cdr row2)))])))

(define add-matrix
  (lambda (m1 m2)
    (cond
      [(null? m1) '()]
      [else (cons (add-row (car m1) (car m2))
                  (add-matrix (cdr m1) (cdr m2)))])))