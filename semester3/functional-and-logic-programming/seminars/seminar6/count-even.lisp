(defun countEven (tree level)
  (cond 
    ((and (atom tree) (= (mod level 2) 0)) 1)
    ((atom tree) 0)
    (t
      (apply '+ (mapcar #'(lambda (tree_i) (countEven tree_i (+ level 1))) tree))
    )
  )
)

(defun main (tree)
  (countEven tree 1)
)

(print (main '((A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K)))))))
