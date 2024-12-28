; 7.
; a) Write a function to eliminate the n-th element of a linear list.
; b) Write a function to determine the successor of a number represented digit by digit as a list, without
; transforming the representation of the number from list to number. Example: (1 9 3 5 9 9) --> (1 9 3 6 0 0)
; c) Write a function to return the set of all the atoms of a list.
; Exemplu: (1 (2 (1 3 (2 4) 3) 1) (1 4)) ==> (1 2 3 4)
; d) Write a function to test whether a linear list is a set.

; a)
(defun eliminate-n (l n)
  (cond 
    ((null l) nil)
    ((= n 1) (cdr l))
    (t
      (cons
        (car l)
        (eliminate-n (cdr l) (- n 1))
      )
    )
  )
)

; (print (eliminate-n '(1 2 3 4 5 6 7) '4))

; b)


; c) % does not work yet
(defun atom-set (l) 
  (cond 
    ((null l) nil)
    ((atom (car l))
      (
       (let ((tail (atom-set (cdr l))))
        (if ((is-member tail (car l)))
          tail
          (cons
            (car l)
            tail
          )
        )
       )
      )
    )
    (t
      (cons
        (atom-set (car l))
        (atom-set (cdr l))
      )
    )
  )
)

(print (atom-set '(1 (2 (1 3 (2 4) 3) 1) (1 4))))

; d)
(defun set-test (l) 
  (cond 
    ((null l) t)
    ((is-member (cdr l) (car l)) nil)
    (t 
      (set-test (cdr l))
    )
  )
)

(defun is-member (l e)
  (cond 
    ((null l) nil)
    ((= (car l) e) t)
    (t 
      (is-member (cdr l) e)
    )
  )
)

; (print (set-test '(1 1 3 5)))
