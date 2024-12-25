; a) Write a function to return the product of two vectors.
; b) Write a function to return the depth of a list. Example: the depth of a linear list is 1.
; c) Write a function to sort a linear list without keeping the double values.
; d) Write a function to return the intersection of two sets.

; a)
(defun dot-prod (l p)
  (cond
    ((or (null l) (null p)) 0) 
    (t (+ (* (car l) (car p)) 
          (dot-prod (cdr l) (cdr p))))))

; (print (dot-prod '(1 2 3) '(1 2 3)))

; b)
(defun depth (l)
  (cond 
    ((null l) 1)
    ((atom (car l))
      (depth (cdr l))
    )
    (t
      (max (+ 1 (depth (car l))) (depth (cdr l)))
    )
  )
)

; (print (depth '((1 2) (3 (4 5)))))
; (print (depth '((1 2) (3 (4 (6 7) 5)))))
; (print (depth '(1 2 (3 4) 5)))
; (print (depth '(1 2 3)))

; c)
(defun insert (e tree)
  (cond
    ((null tree) (list e))
    ((<= e (car tree)) (list (car tree)
    (insert e (cadr tree)) (caddr tree)))
    (t (list (car tree) (cadr tree) (insert e (caddr tree))))
  )
)

(defun construct (l)
  (cond
    ((null l) nil)
    (t (insert (car l) (construct (cdr l))))
  )
)

(defun inorder (arb)
  (cond
    ((null arb) nil)
    (t (append (inorder (cadr arb))
    (list (car arb))
    (inorder (caddr arb))))
  )
)

(defun sortare (l)
  (inorder
    (construct l)
  )
)

; (print (sortare '(-2 5 3 -3 4 1 2 0 -1)))

; d)
(defun intersect (l p)
  (cond 
    ((null l) 
      nil
    )
    ((is-member p (car l)) 
      (cons (car l) (intersect (cdr l) p))
    )
    (t 
      (intersect (cdr l) p)
    )
  )
)

(defun is-member (l e)
  (cond
    ((null l) nil)
    ((equalp e (car l)) t)
    (t (is-member (cdr l) e))
  )
)

(print (intersect '(1 2 3 4) '(2 4 5)))
; (print (is-member '(1 2 3 4) 2))
