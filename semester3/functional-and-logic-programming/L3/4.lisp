; Write a function that returns the product of numeric atoms in a list, at any level.
(defun atom-sum (L)
  (cond
    ((null L) 1)
    ((numberp L) L)
    ((atom L) 1)
    (t
      (apply #'* (mapcar #'atom-sum L))
    )
  )
)

(print (atom-sum '(1 (5 4 (2 3) 7) 2)))
