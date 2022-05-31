;; Sesión 2

#lang racket

;; fact-head: number -> number
(define fact-head
  (lambda (n)
    (cond
      [(< n 1) 1]
      [else (* n (fact-head (- n 1)))])))
;; example: (fact-head 5) => 120

;; fact-tail: number -> number
(define fact-tail
  (lambda (n acc)
    (cond
      [(< n 1) acc]
      [else (fact-tail (- n 1) (* n acc))])))
;; example: (fact-tail 5 1) => 120

;; fib-head: number -> number
(define fib-head
  (lambda (n)
    (cond
      [(< n 3) 1]
      [else (+ (fib-head (- n 1)) (fib-head (- n 2)))])))
;; example: fib-head(5) => 5

;; sum-head: number -> number
(define sum-head
  (lambda (n)
    (cond
      [(eq? n 1) 1]
      [else (+ n (sum-head (- n 1)))])))
;; example: (sum-head 10) => 55

;; sum-tail: number number -> number
(define sum-tail
  (lambda (n acc)
    (cond
      [(eq? n 0) acc]
      [else (sum-tail (- n 1) (+ n acc))])))
;; example: (sum-tail 10 0) => 55

(define my-list (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 (cons 6 '())))))))

;;(define lst '( 1 2 3 4 5 6))

;; sum-list-head list-of-number -> number
(define sum-list-head
  (lambda (list)
    (cond
      [(null? list) 0]
      [else (+ (car list) (sum-list-head (cdr list)))])))
;; example: (sum-list-head my-list) => 21

;; sum-list-tail: list-of-number number -> number
(define sum-list-tail
  (lambda (list acc)
    (cond
      [(null? list) acc]
      [else (sum-list-tail (cdr list) (+ (car list) acc))])))
;; example: (sum-list-tail list 0)

;; repeat-head: atom number -> list-of-atom
(define repeat-head
  (lambda (atom amount)
    (cond
      [(eq? amount 0) '()]
      [else (cons atom (repeat-head atom (- amount 1)))])))
;; example: (repeat-head 'a 4) => '(a a a a)

;; repeat-head: atom number number -> list-of-atom
(define repeat-tail
  (lambda (atom amount acc)
    (cond
      [(eq? amount 0) acc]
      [else (repeat-tail atom (- amount 1) (cons atom acc))])))
;; example: (repeat-tail 'a 4 '()) => '(a a a a)

;; list-of-numbers-head: number number -> list-of-number
(define list-of-numbers-head
  (lambda (start end)
    (cond
      [(> start end) '()]
      [else (cons start (list-of-numbers-head (+ start 1) end))])))
;; example: (list-of-numbers-head 1 5) => '(1 2 3 4 5)

;; list-of-numbers-tail: number number list-of-number -> list-of-number
(define list-of-numbers-tail
  (lambda (start end acc)
    (cond
      [(> start end) acc]
      [else (list-of-numbers-tail start (- end 1) (cons end acc))])))
;; example: (list-of-numbers-tail 1 5 '()) => '(1 2 3 4 5)

;; push-back: atom list -> list
(define push-back
  (lambda (atom list)
    (cond
      [(null? list) (cons atom '())]
      [else (cons (car list)
                  (push-back atom (cdr list)))])))
;; example: (push-back 'a '(b c d)) => '(b c d a)

;; my-append: list list -> list
(define my-append
  (lambda (lst1 lst2)
    (cond
      [(null? lst1) lst2]
      [else (cons (car lst1)
                  (my-append (cdr lst1) lst2))])))
;; example: (my-append '(1 2) '(3 4)) => '(1 2 3 4)

;; reverse-head: list -> list
(define reverse-head
  (lambda (list)
    (cond
      [(null? list) '()]
      [else (my-append (reverse-head (cdr list))
                       (cons (car list) '()))])))
;; example: (reverse-head '(1 2 3)) => '(3 2 1)

;; reverse-tail: list -> list
(define reverse-tail
  (lambda (list acc)
    (cond
      [(null? list) acc]
      [else (reverse-tail (cdr list)
                          (cons (car list) acc))])))
;; example: (reverse-tail '(1 2 3) '()) => '(3 2 1)

;; create-list: number -> list-of-number
(define create-list
  (lambda (amount)
    (cond
      [(eq? amount 0) '()]
      [else (cons (random 100)
                  (create-list (- amount 1)))])))
;; example: (create-list 4) => '(71 73 26 82)

(define random-list (create-list 20))

;; small-items list number -> list
(define small-items
  (lambda (list threshold)
    (cond
      [(null? list) '()]
      [(< (car list) threshold) (cons (car list)
                                      (small-items (cdr list) threshold))]
      [else (small-items (cdr list) threshold)])))
;; example: (small-items '(71 73 26 82) 50) = '(26)

;; large-items list number -> list
(define large-items
  (lambda (list threshold)
    (cond
      [(null? list) '()]
      [(> (car list) threshold) (cons (car list)
                                      (large-items (cdr list) threshold))]
      [else (large-items (cdr list) threshold)])))
;; example: (large-items '(71 73 26 82) 50) = '(71 73 82)

;; quicksort: list-of-numbers -> list-of-numbers
(define quicksort
  (lambda (list)
    (cond
      [(null? list) '()]
      [else (append (quicksort (small-items list (car list)))
                    (cons (car list) '())
                    (quicksort (large-items list (car list))))])))
;; example: (quicksort '(71 73 26 82)) => '(26 71 73 82)

(define greater
  (lambda (threshold)
    (lambda (n)
      (> n threshold))))

(define my-filter
  (lambda (fn threshold)
    (lambda (n)
      (fn n threshold))))

(define addn
  (lambda (x)
    (lambda (y)
      (+ y x))))

(define redux
  (lambda (fn list)
    (cond
      [(null? list) '()]
      [(fn (car list)) (cons (car list)
                             (redux fn (cdr list)))]
      [else (redux fn (cdr list))])))

(define my-map
  (lambda (fn list)
    (cond
      [(null? list) '()]
      [else (cons (fn (car list))
                  (my-map fn (cdr list)))])))

(define quick2
  (lambda (list)
    (cond
      [(null? list) '()]
      [else (append (quick2 (redux (lambda (x) (> x (car list))) list))
                    (cons (car list) '())
                    (quick2 (redux (lambda (x) (< x (car list))) list)))])))
                          