; compute the depth of a tree represented as (node (subtree 1)...(subtree n))
; using MAP functions

(defun depth (L)
  (cond 
    ((atom L) 0)
    (t
      (+ 1 (apply #'max (mapcar #'depth L)))
    )
  )
)
