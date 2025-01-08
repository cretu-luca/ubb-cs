; 8) Return the list of nodes of a tree of type (2) accessed inorder.

(defun inorder (l)
  (cond
    ((null l) nil)
    (t (append (inorder (cadr l))
               (list (car l)) 
               (inorder (caddr l))
       ) 
    )
  )
)

(print (inorder '(a (b () (f) ) (d (e) ())))) ; L Root R
;        a 
;      /   \
;    b      d
;     \   / 
;      f e
; inorder -> b f a e d 
