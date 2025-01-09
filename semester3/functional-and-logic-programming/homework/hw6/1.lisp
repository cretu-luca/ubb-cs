; Write a function to check if an atom is member of a list (the list is non-liniar)
;                     0, x atom and x = e
; map-member (x, e) = 1, x atom and x != e
;                     1, x is null
;                     ∏ map-member (xi), x = x1x2...xi...x3

(defun map-member (l e)
  (if (= (map-member-aux l e) 0)
      (print "e is member of l")
      (print "e is not member of l")))

(defun map-member-aux (l e)
  (cond 
    ((null l) 1)
    ((atom l) 
      (if (equal l e) 
        0
        1
      )
    )
    (t
      (apply #'* (mapcar #'(lambda (l) (map-member-aux l e)) l))
    )
  )
)

(map-member '(1 2 (3 4) 5) 3)
(map-member '(1 2 (4 5) 6) 3)
(map-member '(1 (2 3) ((4) 5)) 4)

; -----------------------------------------------------------------------------------
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
