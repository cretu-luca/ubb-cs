; Write a function that removes all occurrences of an atom from any level of a list.
(defun _replace (L E)
  (cond ((null L) nil)
        ((atom L) (if (equal L E) nil L))
        (t (remove nil (mapcar #'(lambda (x) (_replace x E)) L)))
  )
)

(print (_replace '(1 (3 4 (3 2 1 3 4) 5 3 6) 2 3) '3))
