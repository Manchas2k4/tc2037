#lang racket
;; factR: number => number
(define factR
  (lambda (n)
    (cond
      [(= n 1) 1]
      [else (* n (factR (- n 1)))])))

;; factT: number number => number
(define factT
  (lambda (n acum)
    (cond
      [(= n 1) acum]
      [else (factT (- n 1) (* n acum))])))

;; fibR: number => number
(define fibR
  (lambda (n)
    (cond
      [(= n 1) 1]
      [(= n 2) 1]
      [else (+ (fibR (- n 1))
               (fibR (- n 2)))])))

;; sumR: number number => number
(define sumR
  (lambda (inf sup)
    (cond
      [(= inf sup) sup]
      [else (+ inf (sumR (+ 1 inf) sup))])))

;; sumT: number number number => number
(define sumT
  (lambda (inf sup acum)
    (cond
      [(> inf sup) acum]
      [else (sumT (+ inf 1) sup (+ inf acum))])))

(define lst '(1 2 3 4 5 6 7 8 9 10))

;; sumListR: list => number
(define sumListR
  (lambda (lst)
    (cond
      [(empty? lst) 0]
      [else (+ (first lst)
               (sumListR (rest lst)))])))

;; sumListT: list number => number
(define sumListT
  (lambda (lst acum)
    (cond
      [(empty? lst) acum]
      [else (sumListT (rest lst)
                      (+ (first lst) acum))])))

;; searchR: number list => boolean
(define searchR
  (lambda (number lst)
    (cond
      [(empty? lst) #f]
      [(= number (first lst)) #t]
      [else (searchR number (rest lst))])))

;; repeatR: number number => list
(define repeatR
  (lambda (number times)
    (cond
     [(= times 0) '()]
     [else (cons number
                 (repeatR number (- times 1)))])))

;; repeatT: number number list => list
(define repeatT
  (lambda (number times lst)
    (cond
     [(= times 0) lst]
     [else (repeatT number
                    (- times 1)
                    (cons number lst))])))

;; push-back: number list => list
(define push-back
  (lambda (number lst)
    (cond
      [(empty? lst) (cons number lst)]
      [else (cons (first lst)
                  (push-back number (rest lst)))])))

(define my-append
  (lambda (lst1 lst2)
    (cond
      [(empty? lst1) lst2]
      [else (cons (first lst1)
                  (append (rest lst1) lst2))])))
      





