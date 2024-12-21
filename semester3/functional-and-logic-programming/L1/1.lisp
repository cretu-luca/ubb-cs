; a) Write a function to return the n-th element of a list, or NIL if such an element does not exist.
; b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.
; c) Write a function to determine the list of all sublists of a given list, on any level.
; A sublist is either the list itself, or any element that is a list, at any level. Example:
; (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 sublists :
; ( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) )
; d) Write a function to transform a linear list into a set.

; a)
(defun remove_n (l n)
  (cond
    ((null l) nil)
    ((= n 0) (cdr l))
    (t (cons (car l) (remove_n (cdr l) (- n 1) )))
  )
)

(print (remove_n '(1 2 3 4 5 6) 4))

; b)
(defun my-member (l e)
  (cond 
    ((null l) nil)
    ((listp (car l))
      (or (my-member (car l) e) 
          (my-member (cdr l) e)))
    (t 
      (or (eql (car l) e)
          (my-member (cdr l) e)))
  )
)

(print (my-member '(1 2 3 4 5) 2))

; c)
(defun all-sublists (l)
  (cond
    ((null l) nil)
    ((listp l)
     (append
      (list l)
      (apply #'append (mapcar #'all-sublists l))))
    (t nil)))

(print (all-sublists '(1 2 (3 (4 5) (6 7)) 8 (9 10))))

; d)
(defun to-set (lst)
  (if (null lst)
      nil
      (let ((rest (to-set (cdr lst))))
        (if (member (car lst) rest)
            rest
            (cons (car lst) rest)
        )
      )
  )
)

(print (to-set '(1 2 3 2 4 3 5)))
