#lang racket

;; zeros: number => lon
(define zeros
  (lambda (n)
    (cond
      ((= n 0) '())
      (else (cons 0 (zeros (sub1 n)))))))

;; seq1 number => lon
(define seq1
  (lambda (n)
    (cond
      ((= n 1) '(1))
      (else (cons n (seq1 (sub1 n)))))))

;; seq2: number => lon
(define seq2
  (lambda (n)
    (cond
      ((= n 1) '(1))
      (else (append
             (seq2 (sub1 n))
             (list n))))))

;; fibonacci: number => lon
(define fibonacci
  (lambda (n)
    (cond
      ((= n 1) '(1))
      ((= n 2) '(1 1))
      (else
       (let ((previous-list (fibonacci (sub1 n))))
         (cons (+ (car previous-list) (cadr previous-list))
               previous-list))))))

;; add-one: lon => lon
(define add-one
  (lambda (lst)
    (cond
      ((null? lst) '())
      (else (cons (add1 (car lst))
                  (add-one (cdr lst)))))))

(define my-append
  (lambda (lst1 lst2)
    (cond
      ((null? lst1) lst2)
      (else (cons (car lst1)
                  (my-append (cdr lst1) lst2))))))

(define my-reverse
  (lambda (lst)
    (cond
      ((null? lst) '())
      (else (append (my-reverse (cdr lst))
                    (list (car lst)))))))

(define filter-even
  (lambda (lst)
    (cond
      ((null? lst) '())
      ((equal? 0 (remainder (car lst) 2))
        (cons (car lst) (filter-even (cdr lst))))
      (else (filter-even (cdr lst))))))












         
