#lang racket

(require 2htdp/batch-io)

(define list
  (string->list (read-file "D:\\workspace\\tc2037\\project1\\test.c")))

(define copy
  (lambda (source destination)
    (write-file destination (read-file source))))