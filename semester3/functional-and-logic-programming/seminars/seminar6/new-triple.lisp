(defun newtriple (x)
  (cond
    ((numberp x) (* 3 x))
    ((atom x) x)
    (t
      (mapcar #'newtriple x)
    )
  )
)

(print (newtriple '(1 2 a (3 (0 b)))))
