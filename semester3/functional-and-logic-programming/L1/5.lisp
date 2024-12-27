; 5.
; a) Write twice the n-th element of a linear list. Example: for (10 20 30 40 50) and n=3 will produce (10 20 30 30 40 50).
; b) Write a function to return an association list with the two lists given as parameters.
; Example: (A B C) (X Y Z) --> ((A.X) (B.Y) (C.Z)).
; c) Write a function to determine the number of all sublists of a given list, on any level.
; A sublist is either the list itself, or any element that is a list, at any level. Example:
; (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 lists:
; (list itself, (3 ...), (4 5), (6 7), (9 10)).
; d) Write a function to return the number of all numerical atoms in a list at superficial level.

; a)
(defun duplicate (L N)
  (cond 
    ((null L) nil)
    ((= N 1)
      (cons
       (car L)
       L
      )
      ; (print (car L))
    )
    (t 
      (cons 
        (car L)
        (duplicate (cdr L) (- N 1))
      )
    )
  )
)

; (print (duplicate '(10 20 30 40 50) '3))

; b)
(defun my-assoc (L P)
  (cond 
    ((null L) nil)
    (t 
      (cons
        (cons (car L) (car P))
        (my-assoc (cdr L) (cdr P))
      )
    )
  )
)

; (print (my-assoc '(A B C) '(X Y Z)))

; c)
(defun list-count (L)
  (cond 
    ((null L) 0)
    ((atom L) 0)
    (t 
      (+ 1 (list-count (cdr L)))
    )
  )
)

(print (list-count '(1 2 (3 (4 5) (6 7)) 8 (9 10))))

; d)
(defun atom-count (L)
  (cond 
    ((null L) 0)
    ((atom (car L)) 
      (+ 1 (atom-count (cdr L)))
    )
    (t
      (atom-count (cdr L))
    )
  )
)

; (print (atom-count '(1 2 (3 (4)) 4 5 (6) 7)))
