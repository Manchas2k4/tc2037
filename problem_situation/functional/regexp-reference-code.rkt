#lang racket

(require 2htdp/batch-io)



(define temp-string "132.13e-18")

(regexp-match #px"\\d+" temp-string 4)

(regexp-match? #px"\\d+" temp-string 4)

(regexp-match-positions #px"\\d+" temp-string 4)

(define cadena "hola todos es un ejemplo de recorrer una cadena")

(define start-position
  (lambda (positions)
    (car (car positions))))

(define end-position
  (lambda (positions)
    (cdr (car positions))))

(define transform
  (lambda (type str)
    (string-append "<" type str ">")))

(define traverse
  (lambda (current end input output)
    (cond
      [(>= current end) output]
      [(regexp-match? #px"^[a-zA-Z]+" input current)
       (let ([positions (regexp-match-positions #px"^[a-zA-Z]+" input current)])
         (traverse (end-position positions)
                   end
                   input
                   (string-append output
                                  (transform "reserved"
                                             (substring input
                                                        (start-position positions)
                                                        (end-position positions))))))]
      [(regexp-match? #px"^[[:blank:]]+" input current)
       (let ([positions (regexp-match-positions #px"^[[:blank:]]+" input current)])
         (traverse (end-position positions)
                   end
                   input
                   (string-append output " ")))]
      [else output])))


;; Defines the name of the input file. The input file is considered
;; to be in the current working directory.
(define input-filename "hola.txt")

;; Defines the name of the output file. The input file is considered
;; to be in the current working directory.
(define output-filename "output.html")

(define input (read-file input-filename))
;;(write-file output-filename (traverse 0 (string-length input) input ""))
(traverse 0 (string-length input) input "")