; 4.
; a) Write a function to return the sum of two vectors.
; b) Write a function to get from a given list the list of all atoms, on any level, but on the same order. 
; Example: (((A B) C) (D E)) ==> (A B C D E)
; c) Write a function that, with a list given as parameter, inverts only continuous sequences of atoms.
; Example: (a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))
; d) Write a list to return the maximum value of the numerical atoms from a list, at superficial level.

; a) 
(defun sum (L P)
  (cond
    ((null L) nil)
    (t (cons
        (+ (car L) (car P))
        (sum (cdr L) (cdr P))
       )
    )
  )
)

; (print (sum '(1 2 3) '(3 4 5)))

; b)
(defun get-atoms (L)
  (cond
    ((null L) nil)
    ((atom (car L)) 
      (cons
        (car L)
        (get-atoms (cdr L))
      )
    )
    (t 
      (append
        (get-atoms (car L))
        (get-atoms (cdr L))
      )
    )
  )
)

; (print (get-atoms '(((A (X Y) B) (Z) C) (D E))))

; c) DOES NOT SOLVE THE TASK (((i h g (f e) d) c b a) ) instead of (c b a (d (f e) i h g))
(defun invert (L) 
  (cond
    ((null L) nil)
    ((atom (car L))
      (append 
        (invert (cdr L))
        (list (car L))
        ; (invert (cdr L))
      )
    )
    (t
      (append
        (invert (cdr L))
        (list (invert (car L)))
        ; (invert (cdr L))  
      )
    )
  )
)

(print (invert '(a b c (d (e f) g h i))))

; d)
(defun my-max (X Y)
  (if 
    (< X Y) 
      Y
    X
  )
)

(defun find-max (L)
  (cond
    ((null L) -1)
    ((not (numberp (car L)))
      (find-max (cdr L)))
    (t 
      (my-max (car L) (find-max (cdr L)))
    )
  )
)

; (print (find-max '(1 2 (4 (5)) (7) 3 (6))))

; (print (my-max '12 '12))
