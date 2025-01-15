(defun subm (lst)
  (cond 
    ((null lst) (list nil))
    (t 
      ((lambda (s)
        (append 
          s
          (mapcar #'(lambda (sb) (cons (car lst) sb)) s)
        )
      ) (subm (cdr lst))
     )
   )
  )
)

(print (subm '(1 2 3)))
