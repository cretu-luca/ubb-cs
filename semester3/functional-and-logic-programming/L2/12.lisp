; 12. Determine the list of nodes accesed in preorder in a tree of type (2).
(defun preorder (l)
  (cond
    ((null l) nil)
    (t 
      (append (list (car l))
              (preorder (cadr l))
              (preorder (caddr l))
      )
    )
  )
)

(print (preorder '(a (b () (f) ) (d (e) ())))) ; Root L R
;        a 
;      /   \
;    b      d
;     \   / 
;      f e
; preorder -> a b f d e
