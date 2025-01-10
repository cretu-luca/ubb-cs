(defun find_path_left (tree x nv ne path)
  (cond
    ((null tree) nil)
    ((= nv (+ 1 ne)) nil)
    ((equal (car tree) x) (reverse (cons x path)))
    (t
       (let ((result (find_path_left (cddr tree) x 
                                   (+ 1 nv) 
                                   (+ (cadr tree) ne) 
                                   (cons (car tree) path))))
         (if result 
             result
             nil)
        )
    )
  )
)

(defun find_path_right (tree x nv ne path)
  (cond
    ((null tree) nil)
    ((= nv (+ 1 ne)) (find_path_left tree x 0 0 path))
    (t (find_path_right (cddr tree) x 
                       (+ 1 nv) 
                       (+ (cadr tree) ne) 
                       path))
  ))

(defun find_path (tree x)
  (cond
    ((null tree) nil)
    ((equal (car tree) x) (list x))
    (t
       (let ((left-result (find_path_left (cddr tree) x 0 0 (list (car tree)))))
         (if left-result
             left-result
             (let ((right-result (find_path_right (cddr tree) x 0 0 (list (car tree)))))
               (if right-result
                   right-result
                   nil)
             )
         )
       )
    )
  )
)
                   
(print (find_path '(A 2 B 0 C 2 D 0 E 0) 'D))
(print (find_path '(A 2 B 0 C 2 D 0 E 0) 'B))
(print (find_path '(a 2 b 1 f 0 d 2 e 1 k 0 l 0) 'k))

; horeb XD
(print (mapcar #' (lambda (a b) (eval (list a b))) '(list max min evenp) '(1 2 3 4 5 6))) 
