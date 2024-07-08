#lang racket

(define factorial-tradicional
  (lambda (n)
    (cond
      [(= n 1) 1]
      [else (* n (factorial-tradicional (sub1 n)))])))


(define factorial-terminal
  (lambda (n)
    (factorial-terminal-aux n 1)))

(define factorial-terminal-aux
  (lambda (n acc)
    (cond
      [(= n 1) acc]
      [else (factorial-terminal-aux (sub1 n)
                                    (* acc n))])))

;;--------------------------------------------------

(define lst1 '(1 2 3 4 5 6 7 8 9 10))

(define length-tradicional
  (lambda (lst)
    (cond
      [(null? lst) 0]
      [else (+ 1 (length-tradicional (cdr lst)))])))

(define length-terminal
  (lambda (lst)
    (length-terminal-aux lst 0)))

(define length-terminal-aux
  (lambda (lst acc)
    (cond
      [(null? lst) acc]
      [else (length-terminal-aux (cdr lst)
                                 (+ 1 acc))])))

;;--------------------------------------------------

(define even-tradicional
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [(even? (car lst)) (cons (car lst)
                               (even-tradicional (cdr lst)))]
      [else (even-tradicional (cdr lst))])))

(define even-terminal
  (lambda (lst)
    (even-terminal-aux lst '())))

(define even-terminal-aux
  (lambda (lst acc)
    (cond
      [(null? lst) acc]
      [(even? (car lst)) (even-terminal-aux
                          (cdr lst)
                          (append acc (list (car lst))))]
      [else (even-terminal-aux (cdr lst) acc)])))

;;--------------------------------------------------

(define invert-number
  (lambda (n)
    (invert-number-aux n 0)))

(define invert-number-aux
  (lambda (n acc)
    (cond
      [(= n 0) acc]
      [else (invert-number-aux
             (quotient n 10)
             (+ (remainder n 10) (* acc 10)))])))












