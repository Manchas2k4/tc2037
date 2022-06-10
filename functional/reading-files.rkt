#lang racket

(require 2htdp/batch-io)

;;https://docs.racket-lang.org/teachpack/2htdpbatch-io.html#%28def._%28%28lib._2htdp%2Fbatch-io..rkt%29._write-file%29%29
;;https://docs.racket-lang.org/reference/characters.html

(define input-file "D:\\workspace\\scheme-files\\test.cpp")

(define output-file "D:\\workspace\\scheme-files\\test2.cpp")

(define (flatten lists)
   (foldr append empty lists))

;;(string-downcase str)
(define file->list-of-chars
  (lambda (filename)
    (flatten
     (map string->list
          (read-1strings filename)))))

;;(define input-characters (file->list-of-chars input-file))

(define list-of-chars->file
  (lambda (lst filename)
    (write-file filename (list->string lst))))

(define copy-and-upcase
  (lambda (input-file output-file)
    (list-of-chars->file
     (map char-upcase (file->list-of-chars input-file))
     output-file)))

;; (map char-upcase (file->list-of-chars input-file))

(define list-chars (file->list-of-chars "/home/pperezm/workspace/test.cpp"))

(define list-of-chars->list-of-strings
  (lambda (loc aux result)
    (cond
      [(empty? loc) result]
      [(char-whitespace? (car loc))
       (list-of-chars->list-of-strings (cdr loc)
                                       '()
                                       (cons
                                        (list->string aux)
                                        result))]
      [(char-punctuation? (car loc))
       (list-of-chars->list-of-strings (cdr loc)
                                       '()
                                       (cons
                                        (list->string
                                         (cons (car loc) '()))
                                        (cons
                                         (list->string aux)
                                         result)))]
      [else
       (list-of-chars->list-of-strings (cdr loc)
                                       (append aux (cons (car loc) '()))
                                       result)])))

;;(list-of-chars->list-of-strings list-chars '() '())