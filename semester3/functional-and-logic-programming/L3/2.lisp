; Write a function that returns the sum of numeric atoms in a list, at any level.

(defun atom-sum (L)
  (cond
    ((null L) 0)
    ((numberp L) L)
    ((atom L) 0)
    (t
      (apply #'+ (mapcar #'atom-sum L))
    )
  )
)

(print (atom-sum '(1 (5 4 (6 3) 7) 2 3)))
