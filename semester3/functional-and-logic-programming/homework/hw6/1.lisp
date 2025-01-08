; 1. Write a function to check if an atom is member of a list (the list is non-liniar)

(defun mapcar-member (l e)
  (cond
    ((null l) nil)
    ((atom l) (equal l e))
    (t
      (some #'identity (mapcar #'(lambda (x) (mapcar-member x e)) l))
    )
  )
)

(print (mapcar-member '(1 2 (4 (1) 6) 2 (4 (7 5)) 3 4 6) '5))

(defun mapcan-member (l e)
  (cond
    ((null l) nil)
    ((atom l) (equal l e))
    (t (if 
        (mapcan #'(lambda (x) 
                    (if (mapcan-member x e) 
                        (list t)
                        nil))
                l)
          t
          nil)
    )
  )
)

; (print (mapcan-member '(1 2 (4 (1) 6) 2 (4 (7 5)) 3 4 6) '5))
