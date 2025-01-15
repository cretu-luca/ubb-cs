; write a function to remove all elems multiple of k from a nonlinear list
; using MAP functions
; remove-mk (L, k) = { [], L number and multiple of k
;                    { [L], L number and not multiple or non-numerical atom
;                    { U remove-mk(Li, k), i = 1..n, L = L1L2..Ln
; remove-mk-main (L, K) = first-el-of(remove-mk(L, k))

(defun remove-mk
  (cond 
    ((and (numberp L) (equal 0 (mod L k))) nil)
    ((atom L) (list L))
    (t
      (list (apply #'append (mapcar #'(lambda (x) (remove-mk x k)) L)))
    )
  )
)

(defun remove-mk-main (L k)
  (car (remove-mk L k))
)

; apply #'append mapcar ... => mapcan 
