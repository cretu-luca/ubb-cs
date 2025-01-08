; 15. Determine the list of nodes accesed in postorder in a tree of type (2).
(defun postorder (l)
  (cond
    ((null l) nil)
    (t 
      (append (postorder (cadr l))
              (postorder (caddr l))
              (list (car l))
      )
    )
  )
)

(print (postorder '(a (b () (f) ) (d (e) ())))) ; L R Root
;        a 
;      /   \
;    b      d
;     \   / 
;      f e
; postorder -> f b e d a 
