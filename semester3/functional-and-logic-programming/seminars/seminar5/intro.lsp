; factorial(n) = 1, n = 0
;                n * factorial(n - 1), n > 0

(defun factorial (n)
  (cond
    ((= n 0) 1)
    (t (* n (factorial(- n 1))))
  )
)

(print (factorial 7))

; suma(l1l2..ln) = 0, n = 0
;                  l1 + suma(l2..ln), n > 0

(defun suma (l)
  (cond
    ((null l) 0)
    (t (+ (car l) (suma (cdr l))))
  )
)
(print (suma '(1 2 3 4 5)))

(defun sumc (l c)
  (cond 
    ((null l) c)
    (t (sumc (cdr l) (+ c (car l))))
  )
)

(defun mainsc (l)
  (sumc l 0)
)
(print (mainsc '(1 2 3 4)))
