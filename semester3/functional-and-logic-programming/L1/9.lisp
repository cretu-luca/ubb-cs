; 9.
; a) Write a function that merges two sorted linear lists and keeps double values.
; b) Write a function to replace an element E by all elements of a list L1 at all levels of a given list L.
; c) Write a function to determines the sum of two numbers in list representation, and returns the
; corresponding decimal number, without transforming the representation of the number from list to
; number.
; d) Write a function to return the greatest common divisor of all numbers in a linear list.

; a)
(defun my-merge (l p)
  (cond
    ((null l) p)
    ((null p) l)
    ((< (car l) (car p)) 
      (cons 
        (car l)
        (my-merge (cdr l) p) 
      )
    )
    (t
      (cons 
        (car p)
        (my-merge l (cdr p))
      )
    )
  )
)

; (print (my-merge '(1 4 5 7) '(2 3 4 6 7)))

; b)
(defun replace-l (l e p)
  (cond 
    ((null l) nil)
    ((listp (car l)) 
      (append
        (replace-l (car l) e p)
        (replace-l (cdr l) e p)
      )
    )
    (t
      (if 
        (equal (car l) e)
          (append 
            (list p)
            (replace-l (cdr l) e p)
          )
          (cons
            (car l)
            (replace-l (cdr l) e p)
          )
      )
    )
  )
)

; (print (replace-l '(1 2 3 2 4) '2 '(99 99 99))); => (1 (99 99 99) 3 (99 99 99) 4)

; c)
(defun two-sum (l p)
  (two-sum-aux (reverse l) (reverse p) 0)
)

(defun two-sum-aux (l p tr)
  (cond 
    ((and (null l) (null p)) 
      (if (> tr 0) 
        (list tr)
        nil
      )
    )
    ((null l)
      (append
        (two-sum-aux nil (cdr p) (floor (+ (car p) tr) 10))
        (list (mod (+ (car p) tr) 10))
      )
    )
    ((null p)
      (append
        (two-sum-aux (cdr l) nil (floor (+ (car l) tr) 10))
        (list (mod (+ (car l) tr) 10))
      )
    )
    (t
      (append
        (two-sum-aux (cdr l) (cdr p) (floor (+ (car l) (car p) tr) 10))
        (list (mod (+ (car l) (car p) tr) 10))
      )
    )
  )
)

; -------------------------------------------------------------

(defun two-dif-aux (l p br)
  (cond 
    ((and (null l) (null p)) 
      (if (< br 0) 
          (list br)
          nil))
    
    ((null p)
      (append
        (two-dif-aux (cdr l) nil (floor (- (car l) br) 10))
        (list (mod (- (car l) br) 10))))
    
    ((null l)
      (append
        (two-dif-aux nil (cdr p) (floor (- 0 (car p) br) 10))
        (list (mod (- 0 (car p) br) 10))))
    
    (t
      (let ((diff (- (car l) (car p) br)))
        (if (< diff 0)
            (append 
              (two-dif-aux (cdr l) (cdr p) 1)
              (list (+ diff 10)))
            (append
              (two-dif-aux (cdr l) (cdr p) 0)
              (list diff)))))))

(defun two-dif (l p)
  (two-dif-aux (reverse l) (reverse p) 0))

(print (two-dif '(1 2 3) '(4 5)))
(print (two-dif '(1 0 0) '(9 9)))
(print (two-dif '(1 0) '(8)))

; (print (two-sum '(9) '(2)))

; d)
(defun gcd-lst (l)
  (cond 
    ((null l) nil)
    ((null (cadr l)) (cadr l))
    ((null (cddr l)) (my-gcd (car l) (cadr l)))
    (t 
      (my-gcd 
        (car l)
        (gcd-lst (cdr l))
      )
    )
  )
)

(defun my-gcd (m n)
  (cond
    ((= m n) n)
    ((> m n) 
      (my-gcd (- m n) n)
    )
    (t 
      (my-gcd m (- n m))
    )
  )
)

(print (gcd-lst '(198 154 44)))
