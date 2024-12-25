; a) Write a function that inserts in a linear list a given atom A after the 2nd, 4th, 6th, ... element.
; b) Write a function to get from a given list the list of all atoms, on any level, but reverse order. 
; Example: (((A B) C) (D E)) ==> (E D C B A)
; c) Write a function that returns the greatest common divisor of all numbers in a nonlinear list.
; d) Write a function that determines the number of occurrences of a given atom in a nonlinear list.

; a)
(defun insert-even-aux (l e flag)
  (let ((newFlag (- 1 flag)))
    (cond 
      ((null l) nil)
      ((= flag 1) 
        (cons (car l) 
          (insert-even-aux (cdr l) e newFlag)
        )
      )
      
      (t
        (cons (car l) 
          (cons e
            (insert-even-aux (cdr l) e newFlag)
          )
        )
      )
    )
  )
)

; (print (insert-even-aux '(1 2 3 4) 'x 1))

; b)
(defun get-atoms-rev (l)
  (cond
    ((null l) nil) 
    ((atom (car l))
     (append (get-atoms-rev (cdr l))
             (list (car l))
     )
    )
    (t 
     (append (get-atoms-rev (cdr l)) 
             (get-atoms-rev (car l))
     )
    )
  )
)

; (print (get-atoms-rev '(((A B) C) (D E))))

; c)
(defun my-gcd (m n)
  (cond 
    ((= m n) n)
    ((< m n) 
      (let ((nn (- n m))) 
        (my-gcd m nn)
      )
    )
    (t
      (let ((mm (- m n))) 
        (my-gcd mm n)
      )
    )
  )
)

(defun gcd-l (l)
  (cond 
    ((null (cdr l)) 
      (car l))
    ((null (cddr l)) 
      (my-gcd (car l) (car (cdr l)))
    )
    (t
      (my-gcd (car l) (gcd-l (cdr l)))
    )
  )
)

(defun get-numbers (l)
  (cond 
    ((null l) nil)
    ((atom (car l)) 
      (cons 
        (car l)
        (get-numbers (cdr l))  
      )
    )
    (t 
      (append 
        (get-numbers (car l))
        (get-numbers (cdr l))
      )
    )
  )
)

; (print (get-numbers '(1 2 (3 4 (5 6 (6 9))))))

(defun gcd-nl (l)
  (gcd-l (get-numbers l))
)

(print (gcd-nl '(48 (24 (24 (72) 72 (96)) 576))))

;(print (gcd-nl '(16 (24 (8 72)) 4)))

; (print (gcd-l '(16 24 8)))

; d)
(defun app (l e)
  (cond
    ((null l) 0)
    ((atom (car l))
      (if (equal (car l) e)
        (+ 1 (app (cdr l) e))
        (app (cdr l) e)
      )
    )
    (t 
      (+ (app (car l) e)
         (app (cdr l) e)
      )
    )
  )
)

; (print (app '(1 2 (5 2 (1 5 (2 3)) 3 2 (2 3))) 2)) 
