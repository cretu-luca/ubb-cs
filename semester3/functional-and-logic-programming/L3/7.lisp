; Write a function that substitutes an element E with all elements of a list L1 at all levels of a given list L.

(defun replace-with-lst (L E L1)
  (cond 
    ((null L) nil)
    ((atom L)
      (if (equal L E) 
        L1
        L
      )
    )
    (t (mapcar #'(lambda (x) (replace-with-lst x E L1)) L))
  )
)

(print (replace-with-lst '(1 3 2 3 4) '3 '(9 9 9)))
