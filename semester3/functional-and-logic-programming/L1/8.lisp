; 8.
; a) Write a function to return the difference of two sets.
; b) Write a function to reverse a list with its all sublists, on all levels.
; c) Write a function to return the list of the first elements of all list elements of a given list with an odd 
; number of elements at superficial level. Example:
; (1 2 (3 (4 5) (6 7)) 8 (9 10 11)) => (1 3 9).
; d) Write a function to return the sum of all numerical atoms in a list at superficial level.

; a)
(defun is_member (l e)
  (cond
    ((null l) nil)
    ((= (car l) e) t)
    (t
      (is_member (cdr l) e)
    )
  )
)

(defun diff (l p) 
  (cond 
    ((null L) nil)
    ((is_member p (car l))
      (diff (cdr l) p)
    )
    (t 
      (cons
        (car l)
        (diff (cdr l) p)
      )
    )
  )
)

; (print (diff '(1 2 3) '(3 4 5 6) ))

; (print (is_member '(1 2 3 4) 3))

; b) 
(defun rev (l)
  (cond 
    ((null l) nil)
    ((listp (car l))
      (append 
        (rev (cdr l)) 
        (list (rev (car l)))
      )
    )
    (t
      (append 
        (rev (cdr l))
        (list (car l))
      )
    )
  )
)

; (print (rev '(1 2 (5 (7 8) 6) 3 4)))

; c) 

; d)
(defun surface-sum (l)
  (cond
    ((null l) 0)
    ((atom (car l)) 
      (+ (car l) (surface-sum (cdr l)))
    )
    (t
      (surface-sum (cdr l))
    )
  )
)

(print (surface-sum '(1 (0) 2 3 (4 5) 2 (4 (1 2) 5 6) 4)))
