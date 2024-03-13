#lang racket

;; max2: number number => number
(define max2
  (lambda (a b)
    (if (> a b) a b)))

;; max3: number number number => number
(define max3
  (lambda (a b c)
    (max2 a (max2 b c))))

;; interest: number => number
(define interest
  (lambda (amount)
    (cond
      [(< amount 1000) (* 0.04 amount)]
      [(< amount 5000) (* 0.045 amount)]
      [else (* 0.05 amount)])))

;; how-many?: number number number => number
(define how-many?
  (lambda (a b c)
    (cond
      [(> (* b b) (* 4 a c)) 2]
      [(= (* b b) (* 4 a c)) 1]
      [else 0])))
           
