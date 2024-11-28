; a) A linear list is given. Eliminate from the list all elements from N to N steps, N-given.
; b) Write a function to test if a linear list of integer numbers has a "valley" aspect (a list has a valley
; aspect if the items decrease to a certain point and then increase. Eg. 10 8 6 17 19 20). A list must have
; at least 3 elements to fullfill this condition.
; c) Build a function that returns the minimum numeric atom from a list, at any level.
; d) Write a function that deletes from a linear list of all occurrences of the maximum element.

; a) 
(defun eliminate_main (my_list n)
  (eliminate my_list n 1))

(defun eliminate (my_list n index)
  (cond ((null my_list) nil)
        ((zerop (mod index n)) (eliminate (cdr my_list) n (1+ index)))
        (t (cons (car my_list) 
                 (eliminate (cdr my_list) n (1+ index))))))

(print (eliminate_main '(1 2 3 4 5) 3))

; b)
(defun is_valley (my_list)
  (if (< (length my_list) 3)
      nil
      (let ((first_two_decrease (< (cadr my_list) (car my_list))))
        (valley_helper (cdr my_list) (car my_list) first_two_decrease nil))))

(defun valley_helper (my_list prev is_decreasing found_decrease)
  (cond
    ((null my_list) (and (not is_decreasing) found_decrease))
    
    (is_decreasing
     (cond
       ((< (car my_list) prev)
        (valley_helper (cdr my_list) (car my_list) t t))
       ((> (car my_list) prev)
        (valley_helper (cdr my_list) (car my_list) nil t))
       (t nil)))
    
    (t
     (if (> (car my_list) prev)
         (valley_helper (cdr my_list) (car my_list) nil found_decrease)
         nil))))
  
(print (is_valley '(10 8 6 17 19 20)))
(print (is_valley '(1 2 3 4 5)))  
(print (is_valley '(3 4 5 4 3 2 1)))    
      
; c) 
(defun find_min_number (my_list)
  (cond 
    ((null my_list) nil)
    ((numberp (car my_list))
     (let ((rest_min (find_min_number (cdr my_list))))
       (if (null rest_min) 
           (car my_list)
           (min (car my_list) rest_min))))
    
    ((listp (car my_list))
     (let ((current_min (find_min_number (car my_list)))
           (rest_min (find_min_number (cdr my_list))))
       (cond 
         ((null current_min) rest_min)
         ((null rest_min) current_min)
         (t (min current_min rest_min)))))
    (t (find_min_number (cdr my_list)))))
    
(print (find_min_number '(1 2 3 (4 5 (0) 6) 7)))
      
; d)
(defun find_max (my_list)
  (cond ((null (cdr my_list)) (car my_list))
        (t (max (car my_list)
                (find_max (cdr my_list))))))

(defun remove_max (my_list)
  (let ((max (find_max my_list)))
    (remove_max_helper my_list max)))

(defun remove_max_helper (my_list max)
  (cond ((null my_list) nil)
        ((= (car my_list) max) (remove_max_helper (cdr my_list) max))
        (t (cons (car my_list) 
                 (remove_max_helper (cdr my_list) max)))))

(print (remove_max '(1 5 3 9 8 2)))
