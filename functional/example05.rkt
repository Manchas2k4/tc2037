#lang racket

(define lst1 '(2 (1 4 (3 5) (10) 8) 9 6 7))

(define count-deep
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((list? (car lst)) (+ (count-deep (car lst))
                            (count-deep (cdr lst))))
      (else (+ 1 (count-deep (cdr lst)))))))

(define sum-deep
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((list? (car lst)) (+ (sum-deep (car lst))
                            (sum-deep (cdr lst))))
      (else (+ (car lst) (sum-deep (cdr lst)))))))

(define count-even-deep
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((list? (car lst)) (+ (count-even-deep (car lst))
                            (count-even-deep (cdr lst))))
      ((= 0 (remainder (car lst) 2))
       (+ 1 (count-even-deep (cdr lst))))
      (else (count-even-deep (cdr lst))))))

(define greater-deep
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((list? (car lst))
       (let ( (the-first (greater-deep (car lst)))
              (the-rest (greater-deep (cdr lst))) )
         (if (> the-first the-rest) the-first the-rest)))
      (else
       (let ( (result (greater-deep (cdr lst))) )
         (if (> (car lst) result) (car lst) result))))))











    



