#lang racket

(require 2htdp/batch-io)

;;https://docs.racket-lang.org/teachpack/2htdpbatch-io.html#%28def._%28%28lib._2htdp%2Fbatch-io..rkt%29._write-file%29%29
;;https://docs.racket-lang.org/reference/characters.html

;; Defines the name of the input file. The input file is considered
;; to be in the current working directory.
(define input-filename "test.cpp")

;; Defines the name of the output file. The input file is considered
;; to be in the current working directory.
(define output-filename "output.cpp")

;; The function opens an input file, reads it character by character,
;; returning it in a list of characters.
;; file->list-of-strings: filename => list
(define file->list-of-chars
  (lambda (filename)
    (flatten
     (map string->list
          (read-1strings filename)))))
;; usage example
;; (file->list-of-chars input-filename)

;; The function converts a list of characters to a list of strings.
;; It is an auxiliary function of the function that appears after,
;; although it can be used independently.
;; list-of-chars->list-of-strings: list list list => list
(define list-of-chars->list-of-strings
  (lambda (loc aux result)
    (cond
      [(empty? loc) result]
      [(char-whitespace? (car loc))
       (list-of-chars->list-of-strings (cdr loc)
                                       '()
                                       (cons
                                        (list->string
                                         (cons (car loc) '()))
                                        (cons
                                         (list->string aux)
                                         result)))]
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
;; usage example
;; (list-of-chars->list-of-strings (file->list-of-chars input-filename) '() '())


;; The function opens an input file, reads it character by character,
;; returning it in a list of string.
;; file->list-of-strings: filename => list
(define file->list-of-strings
  (lambda (filename)
    (reverse
     (list-of-chars->list-of-strings
      (file->list-of-chars input-filename) '() '()))))
;; usage example
;; (file->list-of-strings input-filename)


;; The function receives a list of strings and returns a single
;; string that is the result of concatenating all the elements of the
;; list.
(define list-of-strings->string
  (lambda (strlst)
    (string-join strlst " ")))
;; usage example
;; (define strlst (file->list-of-strings input-filename))
;; (list-of-strings->string strlst)

;; The function receives a list of strings and the name of an output
;; file. The function writes the content of the string to the output
;; file.
(define list-of-strings->file
  (lambda (strlst filename)
    (write-file filename (list-of-strings->string strlst))))
;; usage example
;; (list-of-strings->file (file->list-of-strings input-filename) output-filename)

