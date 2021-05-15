#lang racket
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

(define max-aux
  (lambda (current-price previous-price)
    (cond
      [(> (profit previous-price) (profit current-price)) previous-price]
      [else (max-aux (- current-price 0.10) current-price)])))

(define max-profit
  (max-aux 5.00 0))