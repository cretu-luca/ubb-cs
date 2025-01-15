; An n-ary tree is represented in LISP: (root subtreel subtree2 ......). Write a function to replace all nodes from the odd levels in the tree with a given value e. The level of root is considered O.
; Use a MAP function. Write the mathematical model and the meaning of all parameters fomeach function used. Eg: for tree (a (b (g)) (c (d (e)) (f))) si e=h => (a (h (g)) (h (d (h)) (h))

(defun inloc (lst lvl e)
  (cond 
    ((atom lst) 
      (if 
        (equal (mod lvl 2) 1)
        e
        lst
      )
    )
    (t 
      (mapcar #'(lambda (x) (inloc x (+ lvl 1) e)) lst)
    )
  )
)

(print (inloc '(a (b (g)) (c (d (e)) (f))) 1 'h))
