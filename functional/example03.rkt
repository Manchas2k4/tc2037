#lang racket

;; sum: number => number
(define sum
  (lambda (n)
    (cond
      ((= n 0) 0)
      (else (+ n (sum (sub1 n)))))))

;; display: number => void
(define display
  (lambda (n)
    (cond
      ((= n 1) (writeln 'hola))
      (else (begin
              (writeln 'hola)
              (display (sub1 n)))))))

;; secuence: number => void
(define secuence
  (lambda (n)
    (cond
      ((= n 1) (writeln n))
      (else (begin
              (writeln n)
              (secuence (sub1 n )))))))

;; count-digits: number => number
(define count-digits
  (lambda (n)
    (cond
      ((< n 10) 1)
      (else (+ 1 (count-digits (quotient n 10)))))))

;; factorial: number => number
(define factorial
  (lambda (n)
    (cond
      ((= n 1) 1)
      (else (* n (factorial (sub1 n)))))))













 
  