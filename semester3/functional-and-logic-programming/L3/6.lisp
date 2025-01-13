; Write a function that returns the maximum of numeric atoms in a list, at any level.
(defun find-max (L)
  (cond 
    ((null L) -1)
    ((numberp L) L)
    ((atom L) -1)
    (t 
      (apply #'max (mapcar #'find-max L))
    )
  )
)
(print (find-max '(1 (5 4 (2 8 3) 7) 2)))
