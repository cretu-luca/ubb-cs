(defun merge (L, P)
    (cond
        ((null L) P)
        ((null P) L)
        ((< (car L) (car P)) (cons (car L) (merge (cdr L) P)))
        ((> (car L) (car P)) (cons (car P) (merge L (cdr P))))
        (t (cons (car L) (merge (cdr L) (cdr P))))
    )
)
