(defun repl-odd (lst lvl e e1)
  (cond 
    ((null lst) nil)
    ((atom lst) 
      (if (and (equal lst e) (equal (mod lvl 2) 1))
        e1
        lst
      )
    )
    (t
      (mapcar #'(lambda (x) (repl-odd x (+ 1 lvl)  e e1)) lst)
    )
  )
)

(print (repl-odd '(1 d (2 d (d))) 0 'd 'f))
