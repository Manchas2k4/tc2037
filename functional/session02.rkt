#lang racket

(define sum
  (lambda (n)
    (cond
      ((= n 0) 0)
      (else (+ n (sum (- n 1)))))))

(define display
  (lambda (n)
    (cond
      ((= n 1) (writeln 'hola))
      (else (begin
              (display (sub1 n))
              (writeln 'hola))))))

(define sequence
  (lambda (n)
    (cond
      ((= n 1) (writeln n))
      (else (begin
              (writeln n)
              (sequence (sub1 n)))))))

(define count-digits
  (lambda (n)
    (cond
      ((< n 10) 1)
      (else (+ 1 (count-digits (quotient n 10)))))))

(define lst '(2 1 3 6 5 4))

(define length
  (lambda (lst)
    (cond
      ((null? lst) 0)
      (else (+ 1 (length (cdr lst)))))))

(define add-elements
  (lambda (lst)
    (cond
      ((null? lst) 0)
      (else (+ (car lst) (add-elements (cdr lst)))))))

(define count-even
  (lambda (lst)
    (cond
      ((null? lst) 0)
      ((even? (car lst)) (+ 1 (count-even (cdr lst))))
      (else (count-even (cdr lst))))))

(define greater
  (lambda (lst)
    (cond
      ((null? lst) 0)
      (else
       (let ((result (greater (cdr lst))) (b 5) (c 3))
         (if (> (car lst) result) (car lst) result))))))

(define zeros
  (lambda (n)
    (cond
      ((= n 0) '())
      (else (cons 0 (zeros (sub1 n)))))))

(define descending
  (lambda (n)
    (cond
      ((= n 0) '())
      (else (cons n (descending (sub1 n)))))))

(define ascending
  (lambda (n)
    (cond
      ((= n 0) '())
      (else (append (ascending (sub1 n)) (list n))))))

(define fibonacci-list
  (lambda (n)
    (cond
      ((<= n 1) '(1))
      ((= n 2) '(1 1))
      (else
       (let ((previous-list (fibonacci-list (sub1 n))))
         (cons (+ (car previous-list) (cadr previous-list))
               previous-list))))))















 