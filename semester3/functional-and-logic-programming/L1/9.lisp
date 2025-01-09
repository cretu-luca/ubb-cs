; 9.
; a) Write a function that merges two sorted linear lists and keeps double values.
; b) Write a function to replace an element E by all elements of a list L1 at all levels of a given list L.
; c) Write a function to determines the sum of two numbers in list representation, and returns the
; corresponding decimal number, without transforming the representation of the number from list to
; number.
; d) Write a function to return the greatest common divisor of all numbers in a linear list.

; a)
(defun my-merge (l p)
  (cond
    ((null l) p)
    ((null p) l)
    ((< (car l) (car p)) 
      (cons 
        (car l)
        (my-merge (cdr l) p) 
      )
    )
    (t
      (cons 
        (car p)
        (my-merge l (cdr p))
      )
    )
  )
)

; (print (my-merge '(1 4 5 7) '(2 3 4 6 7)))

; b)
(defun replace-l (l e p)
  (cond 
    ((null l) nil)
    ((listp (car l)) 
      (append
        (replace-l (car l) e p)
        (replace-l (cdr l) e p)
      )
    )
    (t
      (if 
        (equal (car l) e)
          (append 
            (list p)
            (replace-l (cdr l) e p)
          )
          (cons
            (car l)
            (replace-l (cdr l) e p)
          )
      )
    )
  )
)

; (print (replace-l '(1 2 3 2 4) '2 '(99 99 99))); => (1 (99 99 99) 3 (99 99 99) 4)

; c)
(defun two-sum (l p)
  (two-sum-aux (reverse l) (reverse p) 0)
)
(defun two-sum-aux (l p tr)
  (cond
    ((AND (null l) (null p))  
      (if (equal tr 1)
        (list 1)
        nil
      )
    )
    ((null l) 
      (let ((tr2 (floor (+ (car p) tr) 10 ))
            (c (mod (+ (car p) tr) 10))
           )
        (if 
          (= tr2 1)
          (list c)
          (list c 1)
        )
      )
    )
    (t 
      (let ((tr2 (floor (+ (car p) (car l) tr) 10 ))
            (c (mod (+ (car p) (car l) tr) 10))
           )
        (append
          (two-sum-aux 
            (cdr l) (cdr p) tr2 
          )
          (list c)
        )
      )
    )
  )
)

(print (two-sum '(1 5) '(9 9)))
