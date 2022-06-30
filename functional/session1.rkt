#lang racket
;; sum-of-squares: number number => number
(define sum-of-squares
  (lambda (n m)
    (+ (* n n) (* m m))))

;; (sum-of-squares 2 3)

;; area-of-circle: number => number
(define area-of-circle
  (lambda (radio)
    (* 3.141592 radio radio)))

;; (area-of-circle 1)


;; area-of-disk: number number => number
(define area-of-disk
  (lambda (outer inner)
    (- (area-of-circle outer)
       (area-of-circle inner))))

;; (area-of-disk 10 1)

;; wage: number number => number
(define wage
  (lambda (payment hours)
    (* payment hours)))

;; tax: number number => number
(define tax
  (lambda (wage rate)
    (* wage rate)))

;; netpay: number number number => number
(define netpay
  (lambda (payment hours rate)
    (- (wage payment hours)
       (tax (wage payment hours) rate))))

;; max2: number number => number
(define max2
  (lambda (a b)
    (cond
      [(> a b) a]
      [else b])))

;; interest-rate: number => number
(define interest-rate
  (lambda (amount)
    (cond
      [(<= amount 1000) 0.04]
      [(<= amount 5000) 0.045]
      [else 0.05])))
      