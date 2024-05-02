#lang racket

(define lst1 '(1 2 3 4))

;; count: los => number
(define count
  (lambda (lst)
    (cond
      ((null? lst) 0)
      (else (+ 1 (count (cdr lst)))))))

;; sum: lon => number
(define sum
  (lambda (lst)
    (cond
      ((null? lst) 0)
      (else (+ (car lst)
               (sum (cdr lst)))))))

;; count-even: lon => number
(define count-even
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((equal? (remainder (car lst) 2) 0)
       (+ 1 (count-even (cdr lst))))
      (else
       (+ 0 (count-even (cdr lst)))))))

;; greater: lon => number
(define greater
  (lambda (lst)
    (cond
      ((null? lst) 0)
      (else
       (let ((result (greater (cdr lst)))
             (the-first (car lst)))
         (if (> the-first result) the-first result))))))








