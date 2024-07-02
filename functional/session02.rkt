#lang racket

(define sum
  (lambda (n)
    (cond
      ;; [(< n 0) (- (sum (- n)))]
      [(= n 1) 1]
      [else (+ n (sum (sub1 n)))])))

(define count-digits
  (lambda (n)
    (cond
      [(< n 10) 1]
      [else (+ 1 (count-digits (quotient n 10)))])))

(define sum-digits
  (lambda (n)
    (cond
      [(= n 0) 0]
      [else (+ (remainder n 10)
               (sum-digits (quotient n 10)))])))

(define lst '(1 2 5 3 4))

(define len
  (lambda (lst)
    (cond
      [(null? lst) 0]
      [else (+ 1 (len (cdr lst)))])))

(define sum-list
  (lambda (lst)
    (cond
      [(null? lst) 0]
      [else (+ (car lst) (sum-list (cdr lst)))])))

(define count-even
  (lambda (lst)
    (cond
      [(null? lst) 0]
      [(even? (car lst)) (+ 1 (count-even (cdr lst)))]
      [else (+ 0 (count-even (cdr lst)))])))

(define greater
  (lambda (lst)
    (cond
      [(null? lst) 0]
      [else
       (let ([result (greater (cdr lst))])
         (if (> (car lst) result) (car lst) result))])))

























