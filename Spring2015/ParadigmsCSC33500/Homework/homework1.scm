#lang scheme

; Assigned January 29 2015, following Lecture 1

; Read sections 1.1.1 through 1.1.6 in Abelson and Sussman

; Solve exercises 1.1 through 1.5


;1.1
;easy 

; 1.2
; express some equation
;(/ (+ 5 (+ 4 (- 2 (- 3 (+ 6 (/ 4 5)))))) (* 3 (* (- 6 2) (- 2 7) )))

; 1.3
#|(define sum_twolargest(a b c)
	(+ (cond ((> a b) a)
		(else b))
	(cond ((> b  c) b)
	(else c))
	) )
|#

; 1.3
(define (sumlargestsqrs a b c)
	 (cond ((and (< a b) (< a c)) (squaresum b c))	
		((and (< b a) (< b c)) (squaresum a c))
		((and (< c a)(< c b)) (squaresum a b) )) )

(define (squaresum x y)
	(+ (* x x)(* y y))
	)

(sumlargestsqrs 1 2 4)



; iterative works in constant space 
; check difference between iterative and recursion
