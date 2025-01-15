; A nonlinear list is given. Write a LISP function to return as result the initial list in which the atoms from the level k from the initial list have been replaced with 0 (the superficial level is considered 1). Use a MAP function. Write the mathematical model and the meaning of all parameters for each function used.

(defun inloc (lst lvl k) 
  (cond
    ((null lst) nil)
    ((atom lst) 
      (if (equal lvl k)
        0
        lst
      )
    )
    (t 
      (mapcar #'(lambda (x) (inloc x (+ lvl 1) k)) lst)
    )
  )
)

(print (inloc '(a (1 (2 b)) (c (d))) 0 2))
