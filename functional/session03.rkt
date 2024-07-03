#lang racket

(define zeros
  (lambda (n)
    (cond
      [(= n 0) '()]
      [else (cons 0 (zeros (sub1 n)))])))

(define descending-list
  (lambda (n)
    (cond
      [(= n 0) '()]
      [else (cons n (descending-list (sub1 n)))])))

(define ascending-list
  (lambda (n)
    (cond
      [(= n 0) '()]
      [else (append (ascending-list (sub1 n)) (list n))])))

(define fibonacci-aux
  (lambda (n)
    (cond
      [(= n 1) '(1)]
      [(= n 2) '(1 1)]
      [else
       (let ([previous-list (fibonacci-aux (sub1 n))])
         (cons (+ (car previous-list) (cadr previous-list))
               previous-list))])))

(define fibonacci-list
  (lambda (n)
    (reverse (fibonacci-aux n))))

(define increment
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [else (cons (add1 (car lst))
                  (increment (cdr lst)))])))

(define my-append
  (lambda (lst1 lst2)
    (cond
      [(null? lst1) lst2]
      [else (cons (car lst1)
                  (my-append (cdr lst1) lst2))])))

(define my-reverse
  (lambda (lst)
    (cond
      [(null? lst) '()]
      [else (append (my-reverse (cdr lst))
                    (list (car lst)))])))

(define swapper
  (lambda (a b lst)
    (cond
      [(null? lst) '()]
      [(equal? a (car lst)) (cons b (swapper a b (cdr lst)))]
      [(equal? b (car lst)) (cons a (swapper a b (cdr lst)))]
      [else (cons (car lst) (swapper a b (cdr lst)))])))

(define deep-lst '(1 ((2) 3) (4) (5 6 7) 8 9 10))

(define len
  (lambda (deep-lst)
    (cond
      [(null? deep-lst) 0]
      [(list? (car deep-lst)) (+ (len (car deep-lst))
                                 (len (cdr deep-lst)))]
      [else (+ 1 (len (cdr deep-lst)))])))

(define sum
  (lambda (deep-lst)
    (cond
      [(null? deep-lst) 0]
      [(list? (car deep-lst)) (+ (sum (car deep-lst))
                                 (sum (cdr deep-lst)))]
      [else (+ (car deep-lst) (sum (cdr deep-lst)))])))

(define count-even
  (lambda (deep-lst)
    (cond
      [(null? deep-lst) 0]
      [(list? (car deep-lst)) (+ (count-even (car deep-lst))
                                 (count-even (cdr deep-lst)))]
      [(even? (car deep-lst)) (+ 1
                                 (count-even (cdr deep-lst)))]
      [else (+ 0 (count-even (cdr deep-lst)))])))
























