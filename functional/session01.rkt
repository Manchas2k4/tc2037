#lang racket
(define sum
  (lambda (a b)
    (+ a b)))

(define area-of-triangle
  (lambda (base height)
    (/ (* base height) 2)))

(define area-of-circle
  (lambda (radio)
    (* 3.1415 radio radio)))

(define area-of-ring
  (lambda (inner-radio outer-radio)
    (- (area-of-circle outer-radio)
       (area-of-circle inner-radio))))

(define volume-of-cylinder
  (lambda (radio height)
    (* height (area-of-circle radio))))

(define max2
  (lambda (a b)
    (if (> a b) a b)))

(define max3
  (lambda (a b c)
    (max2 a (max2 b c))))

(define interes
  (lambda (amount)
    (cond
      [(<= amount 1000) (* amount 0.04)]
      [(<= amount 5000) (* amount 0.045)] ;; 1000 < x <= 5000
      [else (* amount 0.05)])))

(define how-many
  (lambda (a b c)
    (cond
      [(> (* b b) (* 4 a c))  2]
      [(= (* b c) (* 4 a c))  1]
      [else 0])))

(define bmi-aux
  (lambda (weight height)
    (/ weight (* height height))))

(define bmi
  (lambda (weight height)
    (cond
      [(< (bmi-aux weight height) 20) 'underweight]
      [(< (bmi-aux weight height) 25) 'normal]
      [(< (bmi-aux weight height) 30) 'obese1]
      [(< (bmi-aux weight height) 40) 'obese2]
      [else 'obese3])))

(bmi 45 1.6) ;;=> underweight
(bmi 55 1.5) ;;=> normal
(bmi 76 1.7) ;;=> obese1
(bmi 81 1.6) ;;=> obese2
(bmi 120 1.6) ;; => obese3

(define bmi-2
  (lambda (weight height)
    (let ([result (/ weight (* height height))])
      (cond
        [(< result 20) 'underweight]
        [(< result 25) 'normal]
        [(< result 30) 'obese1]
        [(< result 40) 'obese2]
        [else 'obese3]))))

(bmi-2 45 1.6) ;;=> underweight
(bmi-2 55 1.5) ;;=> normal
(bmi-2 76 1.7) ;;=> obese1
(bmi-2 81 1.6) ;;=> obese2
(bmi-2 120 1.6) ;; => obese3