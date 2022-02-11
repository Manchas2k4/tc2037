#lang racket

(require 2htdp/batch-io)

(define list
  (string->list (read-file "D:\\workspace\\tc2037\\project1\\test.c")))

;;list->string

(define copy
  (lambda (source destination)
    (write-file destination (read-file source))))

;;(copy "D:\\workspace\\tc2037\\project1\\test.c" "D:\\workspace\\tc2037\\project1\\copy.c")