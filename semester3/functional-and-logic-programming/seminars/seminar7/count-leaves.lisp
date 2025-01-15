; count the leaves of a tree using MAP functions
; count-leaves (L) = {0, L atom 
;                    {1, L = L1
;                    { sum (count-leaves(Li)), L = L1L2..Ln

(defun count-leaves (L)
  (cond 
    ((atom L) 0)
    (t 
      (if (= (length L) 1)
        1
        (apply #'+ (mapcar #'count-leaves L))
      )
    )
  )
)

(print (count-leaves '(A (B (C) (D (E) (F))))))
