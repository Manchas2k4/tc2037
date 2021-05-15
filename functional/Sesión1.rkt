#lang racket

;; esto es un comentario

;; sum: number number -> number
(define sum
  (lambda (a b)
    (+ a b)))
;; example: (suma 10 12) => 22

;; suma-of-squares: number number => number
(define sum-of-squares
  (lambda (a b)
    (+ (* a a) (* b b))))
;; example: (sum-of-squares 2 3) => 13

;; area-of-circle: number -> number
(define area-of-circle
  (lambda (radio)
    (* 3.1415 radio radio)))
;; example (area-of-circle 1) => 3.1415

;; multiple: number number -> boolean
(define multiple
  (lambda (x)
    (lambda (n)
      (eq? (remainder n x) 0))))

;; area-of-disk: number number -> number
(define area-of-disk
  (lambda (outer inner)
    (- (area-of-circle outer) (area-of-circle inner))))
;; example: (area-of-disk 10 4) => 263.886

;; wage: number number -> number
(define wage
  (lambda (payment hours)
    (* payment hours)))
;; example: (wage 10 40) => 400

;; tax: number number -> number
(define tax
  (lambda (wage rate)
    (* wage rate)))
;; example: (tax 100 0.10) => 10

;; netpay: number number number -> number
(define netpay
  (lambda (payment hours rate)
    (- (wage payment hours)
       (tax (wage payment hours) rate))))
;; example: (netpay 10 10 0.10) => 90

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
;; example: (attendees 4.90) => 134.9

;; cost: number -> number
(define cost
  (lambda (ticket-price)
    (+ 180
       (* 0.04 (attendees ticket-price)))))
;; example: (cost 4.90) => 185.4

;; revenue: number -> number
(define revenue
  (lambda (ticket-price)
    (* (attendees ticket-price) ticket-price)))
;; example: (revenue 4.90) => 661.4999999999998

;; profit: number -> number
(define profit
  (lambda (ticket-price)
    (- (revenue ticket-price)
       (cost ticket-price))))
;; example: (profit 4.90)

;; max1: number number -> number
(define max1
  (lambda (a b)
    (if (> a b) a b)))
;; example (max1 10 12) => 12

;; max2: number number => number
(define max2
  (lambda (a b)
    (cond
      [(> a b) a]
      [else b])))
;; example: (max2 10 12) =>

;; interest-rate: number -> number
(define interest-rate
  (lambda (amount)
    (cond
      ((<= amount 1000) (* 0.04 amount))
      ((<= amount 5000) (* 0.045 amount))
      (else (* 0.05 amount)))))
;; example: (interest-rate 10000) => 500.0
      


      