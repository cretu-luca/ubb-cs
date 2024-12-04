; remove all occ of elem elem
(defun remE (l e)
  (cond
    ((null l) ())
    ((and (atom (car l) ) (equal (car l) e)) (remE (cdr l) e))
    ((atom (car l)) (cons (car l) (remE (cdr l) e)))
    (t (cons (remE (car l) e) (remE (cdr l) e)))
  )
)

(print (remE '(1 2 (2 1 (5 6 (1))) a b) 1))
