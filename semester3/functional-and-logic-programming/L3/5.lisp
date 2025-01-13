; Write a function that computes the sum of even numbers and the decrease the sum of odd numbers,
; at any level of a list.
(defun atom-sum (L)
  (cond
    ((null L) 0)
    ((numberp L) 
      (cond 
        ((equal (mod L 2) 0)  L)
        (t 
          (* L -1)
        )
      )
    )
    ((atom L) 0)
    (t
      (apply #'+ (mapcar #'atom-sum L))
    )
  )
)

(print (atom-sum '(1 (5 4 (2 3) 7) 2)))
