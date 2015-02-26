#lang scheme


#|
sum digits in nmber 
|#

( define (sum-iter notyetproc sum-so-far)
	(cond((zero? notyetproc) sum-so-far) 	
	(else (sum-iter (quotient notyetproc 10) (+ (remainder  notyetproc 10) sum-so-far)))
	))

(quotient 234 10)
(remainder 234 10)
(sum-iter 234 0)
