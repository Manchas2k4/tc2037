;; ITESM QRO
;; Author: Pedro Perez
;; Sesion 2 de Scheme

#lang racket

;; Imagine al propietario de una sala de cine que tiene total
;; libertad para fijar los precios de las entradas. Cuanto más
;; cobra, menos personas pueden pagar las entradas. En un
;; experimento reciente, el propietario determinó una relación
;; precisa entre el precio de un boleto y la asistencia promedio.
;; A un precio de $ 5.00 por entrada, 120 personas asisten a una
;; función. Disminuir el precio en una moneda de diez centavos
;; ($ .10) aumenta la asistencia en 15. Desafortunadamente,
;; el aumento de la asistencia también tiene un costo mayor.
;; Cada actuación le cuesta al propietario $ 180. Cada asistente
;; cuesta otros cuatro centavos ($ 0.04). Al propietario le gustaría
;; saber la relación exacta entre el beneficio y el precio del boleto
;; para poder determinar el precio al que puede obtener el mayor
;; beneficio.

;; attendees: number -> number
(define attendees
  (lambda (ticket-price)
    (+ 120
       (* (/ 15 0.10) (- 5.00 ticket-price)))))
;;(attendees 4.90) => 134.99

;;revenue: number -> number
(define revenue
  (lambda (ticket-price)
    (* (attendees ticket-price) ticket-price)))
;; (revenue 4.90) => 661.49

;; cost: number -> number
(define cost
  (lambda (ticket-price)
    (+ 180
       (* 0.04 (attendees ticket-price)))))
;;(cost 4.90) => 185.40

;; best-ticket-price: number number -> number
(define best-ticket-price
  (lambda (ticket-price best)
    (cond
      [(<= ticket-price 0.0) 'not_found]
      [(> (- (revenue ticket-price)
             (cost ticket-price)) best)
       (best-ticket-price (- ticket-price 0.10)
                          (- (revenue ticket-price)
                             (cost ticket-price)))]
      [else ticket-price])))

(define lst '(1 2 3 4 5 6 7 8 9 10))

;; size-head: list-of-number -> number
(define size-head
  (lambda (lst)
    (cond
      [(empty? lst) 0]
      [else (+ 1 (size-head (cdr lst)))])))

;; size-tail: list-of-number -> number
(define size-tail
  (lambda (lst acc)
    (cond
      [(empty? lst) acc]
      [else (size-tail (rest lst) (+ acc 1))])))

;; sum-list-head: list-of-number -> number
(define sum-list-head
  (lambda (lst)
    (cond
      [(empty? lst) 0]
      [else (+ (car lst) (sum-list-head (cdr lst)))])))

;; sum-list-tail: list-of-number -> number
(define sum-list-tail
  (lambda (lst acc)
    (cond
      [(empty? lst) acc]
      [else (sum-list-tail (cdr lst) (+ acc (car lst)))])))

;; average: list-of-number -> number
(define average
  (lambda (lst)
    (/ (sum-list-tail lst 0)
       (size-tail lst 0))))

;; maximum-tail: list-of-number number -> number
(define maximum-tail
  (lambda (lst best)
    (cond
      [(empty? lst) best]
      [(> (car lst) best) (maximum-tail (cdr lst)
                                        (car lst))]
      [else (maximum-tail (cdr lst) best)])))

;; maximum-head: list-of-number -> number
(define maximum-head
  (lambda (lst)
    (cond
      [(empty? lst) 0]
      [(> (car lst) (maximum-head (cdr lst))) (car lst)]
      [else (maximum-head (cdr lst))])))

;;list-of-numbers: number number -> list-of-numbers
(define list-of-numbers
  (lambda (start end)
    (cond
      [(> start end) (list-of-numbers end start)]
      [(eq? start end) (cons start '())]
      [else (cons start
                  (list-of-numbers (+ start 1) end))])))

;; evens: list-of-numbers -> list-of-numbers
(define evens
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [(= (remainder (car lst) 2) 0)
       (cons (car lst) (evens (cdr lst)))]
      [else (evens (cdr lst))])))

;; more-than: number list-of-number -> list-of-numbers
(define more-than
  (lambda (n lst)
    (cond 
      [(empty? lst) '()]
      [(> (car lst) n) (cons (car lst)
                             (more-than n (cdr lst)))]
      [else (more-than n (cdr lst))])))

;; less-than: number list-of-number -> list-of-numbers
(define less-than
  (lambda (n lst)
    (cond 
      [(empty? lst) '()]
      [(< (car lst) n) (cons (car lst)
                             (less-than n (cdr lst)))]
      [else (less-than n (cdr lst))])))

(define aux '(8 7 3 2 10 9 5 1 4 6))
;; quick-sort: list-of-number -> list-of-number
(define quick-sort
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else
       (append (quick-sort (less-than (car lst) (cdr lst)))
               (cons (car lst)
                     (quick-sort
                      (more-than (car lst) (cdr lst)))))])))

;; not-multiples: number list-of-number -> list-of-number
(define not-multiples
  (lambda (n lst)
    (cond
      [(empty? lst) '()]
      [(= (remainder (car lst) n) 0)
       (not-multiples n (cdr lst))]
      [else (cons (car lst)
                  (not-multiples n (cdr lst)))])))

;; sieve-aux: list-of-numbers -> list-of-numbers
(define sieve-aux
  (lambda (lst)
    (cond
      [(empty? lst) '()]
      [else (cons (car lst)
                  (sieve-aux (not-multiples (car lst)
                                            (cdr lst))))])))

;; sieve-of-eratosthenes: number -> list-of-numbers
(define sieve-of-eratosthenes
  (lambda (n)
    (sieve-aux (list-of-numbers 2 n))))
    

      



















