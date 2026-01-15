#lang racket

(define sum
  (lambda (a b)
    (+ a b)))

(define area-of-triangle
  (lambda (base height)
    (/ 2 (* base height))))

(define area-circle
  (lambda (radius)
    (* 3.14 radius radius)))

(define area-of-ring
  (lambda (inner outer)
    (- (area-circle outer) (area-circle inner))))

(define volumne-of-cylinder
  (lambda (radius height)
    (* (area-circle radius) height)))

(define max2
  (lambda (a b)
    (if (> a b) a b)))

(define max3
  (lambda (a b c)
    (max2 a (max2 b c))))

(define interest
  (lambda (amount)
    (cond
      ((<= amount 1000) (* amount 0.04))
      ((<= amount 5000) (* amount 0.045))
      (else (* amount 0.05)))))

(define how-many
  (lambda (a b c)
    (cond
      ((> (* b b) (* 4 a c)) 2)
      ((= (* b b) (* 4 a c)) 1)
      (else 0))))