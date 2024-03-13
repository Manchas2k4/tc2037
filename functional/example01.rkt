#lang racket

;; sum: number number => number
(define sum
  (lambda (a b)
    (+ a b)))

;; area-of-triangle: number number => number
(define area-of-triangle
  (lambda (base height)
    (/ (* base height) 2)))

;; area-of-circle: number => number
(define area-of-circle
  (lambda (radius)
    (* radius radius 3.141592)))

;; area-of-ring: number number => number
(define area-of-ring
  (lambda (outer inner)
    (- (area-of-circle outer)
       (area-of-circle inner))))

;; volume-of-cylinder: number number => number
(define volume-of-cylinder
  (lambda (radius height)
    (* (area-of-circle radius) height)))
