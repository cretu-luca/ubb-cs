; (node no-subtrees list-subtree-1 list-subtree-2 ...) (1)
; ex: (A 2 B 0 C 2 D 0 E 0)  (1)
; 14. Determine the list of nodes accesed in postorder in a tree of type (1).

; postorder -> Left Right Root

(defun get_left (tree nv ne)
  (cond
    ((null tree) nil)
    ((= nv (+ 1 ne)) nil)
    (t (cons (car tree) 
        (cons (cadr tree) 
          (get_left (cddr tree) (+ 1 nv) (+ (cadr tree) ne)))
        )
    )
  )
)

(defun left (tree)
  (get_left (cddr tree) 0 0)
)

(defun get_right (tree nv ne)
  (cond
    ((null tree) nil)
    ((= nv (+ 1 ne)) (get_left tree 0 0))
    (t (get_right (cddr tree) (+ 1 nv) (+ (cadr tree) ne)))
  )
)

(defun right (tree)
  (get_right (cddr tree) 0 0)
)

(defun postorder (tree)
  (if (null tree)
      t
      (and (postorder (left tree))
           (postorder (right tree))
           (print (car tree)))))

(postorder '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0))

; (print (left '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0)))
; (print (right '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0)))
