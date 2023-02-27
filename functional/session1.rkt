;; ITESM QRO
;; Author: Pedro Perez
;; Sesion 1 de Scheme

#lang racket

(define var 3)

(define func1
  (lambda (x y)
    (* (+ x y) 2)))

(define func2
  (lambda (x)
    (lambda (y)
      (* (+ x y) 2))))

;; sum: number number -> number
(define sum
  (lambda (a b)
    (+ a b)))
;; example: (sum 1 3) => 4

;; sum-of-squares: number number -> number
(define sum-of-squares
  (lambda (a b)
    (+ (* a a) (* b b))))
;; example: (sum-of-squares 3 4) => 25

;; area-of-disk: number -> number
(define area-of-disk
  (lambda (radio)
    (* 3.1415 radio radio)))
;; example: (area-of-disk 10) => 314.15000000000003

;; area-of-ring number number -> number
(define area-of-ring
  (lambda (outer inner)
    (- (area-of-disk outer)
       (area-of-disk inner))))
;; example: (area-of-ring 10 4) => 263.886

;; wage: number number -> number
(define wage
  (lambda (payment hours)
    (* payment hours)))
;; example:  (wage 12 2) => 24

;; tax: number number -> number
(define tax
  (lambda (wage rate)
    (* wage rate)))
;; example: (tax 100 0.15) => 15

;; netpay number number number -> number
(define netpay
  (lambda (payment hours rate)
    (- (wage payment hours)
       (tax (wage payment hours) rate))))
;; example: (netpay 12 40 0.15) => 408

;; sum-head: number -> number
(define sum-head
  (lambda (n)
    (cond
      [(<= n 1) 2]
      [else (+ (* 2 n) (sum-head (- n 1)))])))
;; example: (sum-head 10) => 110

;; sum-tail: number number -> number
(define sum-tail
  (lambda (n acc)
    (cond
      [(eq? n 0) acc]
      [else (sum-tail (- n 1) (+ (* 2 n) acc))])))
;; example: (sum-tail 10 0) => 110

;; fact-head: number -> number
(define fact-head
  (lambda (n)
    (cond
      [(eq? 1 n) 1]
      [else (* n (fact-head (- n 1)))])))
;; (fact-head 5) => 120

;; fact-tail: number -> number
(define fact-tail
  (lambda (n acc)
    (cond
      [(eq? 1 n) acc]
      [else (fact-tail (- n 1) (* acc n))])))
;; (fact-tail 5 1) => 120