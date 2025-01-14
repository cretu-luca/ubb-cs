(defun multiply-by-level (lst lvl)
  (cond 
    ((null lst) nil)
    ((numberp lst) (* lst lvl))
    ((atom lst) lst)
    (t
      (mapcar #'(lambda (x) (multiply-by-level x  (+ 1 lvl))) lst)
    )
  )
)

(print (multiply-by-level '(1(2)(3(4(5)))) 0))
(print (multiply-by-level '(1(2(A(B)))(3(4(C(5))))) 0))
