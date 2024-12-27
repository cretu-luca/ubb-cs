; 6.
; a) Write a function to test whether a list is linear.
; b) Write a function to replace the first occurence of an element E in a given list with an other element O.
; c) Write a function to replace each sublist of a list with its last element.
; A sublist is an element from the first level, which is a list.
; Example: (a (b c) (d (e (f)))) ==> (a c (e (f))) ==> (a c (f)) ==> (a c f)
;         (a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)
; d) Write a function to merge two sorted lists without keeping double values.

; a)
(defun test-linear (l)
  (cond 
    ((null l) t)
    ((listp (car l)) nil)
    (t 
      (test-linear (cdr l))
    )
  )
)

; (print (test-linear '(1 2 2 (4) 3)))

; b)
(defun replace-e (l e o)
  (cond
    ((= (car l) e) 
      (cons 
        o
        (cdr l)
      )
    )
    (t
      (cons
        (car l)
        (replace-e (cdr l) e o)
      )
    )
  )
)

; (print (replace-e '(1 2 3 4) '3 '5 ))

; c)
(defun replace-last (l)
  (cond 
    ((null l) nil)
    ((listp (car l)) 
      replace-last
    )
  )
)

; d)
(defun my_merge (l p)
  (cond
    ((null p) l)
    ((null l) p)
    (t (let ((h1 (car l))
            (h2 (car p))
           )
        
        (cond 
          ( (< h1 h2)
            (cons 
              h1
              (my_merge (cdr l) p)
            )
          )
          ( (> h1 h2) 
            (cons 
              h2
              (my_merge l (cdr p))
            )
          )
          (t 
            (cons 
              h1
              (my_merge (cdr l) (cdr p))
            )
          )
        )
      )
    )
  )
)

; (print (my_merge '(1 2 3 5) '(2 4 5 6)))
