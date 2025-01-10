(defun mountain (a seen-increase seen-decrease)
  (cond
    ((null (cdr a)) (and seen-increase seen-decrease))
    ((> (cadr a) (car a)) ; increasing 
     (if seen-decrease 
         nil
         (mountain (cdr a) t nil)))
    ((< (cadr a) (car a)) ; decreasing 
     (if seen-increase
         (mountain (cdr a) seen-increase t)
         nil))
    (t nil)))

(print (mountain '(2 3 4 5 4 3 2 1) nil nil))
