#lang racket

(define test1 '(1 2 3 4 5 6 7 8))
(define test2 '(((6) (2 8)) 4 5 (1 7) 3))

(define deep-count-elements
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((list? (car lst)) (+ (deep-count-elements (car lst))
                            (deep-count-elements (cdr lst))))
      (else (+ 1 (deep-count-elements (cdr lst)))))))

(define deep-sum-elements
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((list? (car lst)) (+ (deep-sum-elements (car lst))
                            (deep-sum-elements (cdr lst))))
      (else (+ (car lst) (deep-sum-elements (cdr lst)))))))

(define deep-count-even
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((list? (car lst)) (+ (deep-count-even (car lst))
                            (deep-count-even (cdr lst))))
      ((even? (car lst)) (+ 1 (deep-count-even (cdr lst))))
      (else (deep-count-even (cdr lst))))))

(define deep-greater
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((list? (car lst))
       (let ((left (deep-greater (car lst)))
             (right (deep-greater (cdr lst))))
         (if (> left right) left right)))
      (else
       (let ((result (deep-greater (cdr lst))) (b 5) (c 3))
         (if (> (car lst) result) (car lst) result))))))

(define lst '((a 1)(a 2)(b 1)(b 2)))