(defun prod (lst)
  (cond 
    ((numberp lst) lst)
    ((atom lst) 1)
    (t 
      (apply '* (mapcar #'prod lst))
    )
  )
)

(print (prod '(1 2 c (5 d (7) 1) a 3 4 5)))
