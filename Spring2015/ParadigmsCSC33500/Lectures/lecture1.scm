
; from Section 1.1 of Abelson and Sussman

; 1.1.1 Expressions

; expressions are evaluated

; some expressions are primitive

; numbers are primitive expressions

486

12.01


; another kind of expression is a primitive procedure

+

; arithmetical expressions are formed from numbers and primitive procedures


; arithmetical expressions are fully parenthesized, with the operator in the
; prefix position


(+ 2 3)

(+ 2 3 4 5)

(+ (* 4 5) 3)

(+ (* 3 (+ (* 2 4) (+ 3 5))) (+ (- 10 7) 6))


; there are many other kinds of expressions, which we will ignore for now

"Hello world"

(string-append "Hello" " world")



; 1.1.2 Naming

; we can name values, and then use them

(define size 2)

(+ 5 size)



(define pi 3.14159265389793)

(define radius 10)

(* pi (* radius radius))



; 1.1.3  Evaluating Combinations

; to evaluate a combination, do the following

;; 1.  evaluate the subexpressions of the combination

;; 2.  apply the procedure that is the value of the leftmost
;;     subexpression (the operator) to the arguments that are the
;;     values of the other subexpressions (the operands)



; use this rule on the third example above:

; (+ (* 3 (+ (* 2 4) (+ 3 5))) (+ (- 10 7) 6))


; clearly, this expression can be cast as a tree, with primitive
; expressions (in this case, numbers) as leaves.

; to halt the recursion implicit in this evaluation rule, scheme stipulates
; that

; the values of numerals are the numbers they name

; the values of built-in operators are the machine instruction sequences
; that carry out the corresponding operations

; the values of other names are the objects associated with those names by
; define



; 1.1.4  Compound Procedures

; functions are values, too

(lambda (x) (* x x))

((lambda (x) (* x x)) 2)

; function values can be named

(define square
  (lambda (x) (* x x)))

(square 2)

; perhaps more conveniently, but with some loss of clarity, we can omit 'lambda'

(define (square x) 
  (* x x))

(square 2)


; some names are local, while others are global

(define x 3)

(define (add-x y)
  (+ x y))


; here, x is global


; note that z has not been defined - nonetheless, we are able to define
; a function which refers to z

(define (add-z y)
  (+ z y))

; we cannot apply add-z until z is defined, however



; function names can occur in other functions' bodies, too 


(define (cube x)
  (* x (square x)))


; here, square is global


; one last point about square: it is generic!

(square 2)

(square 2.1)


; function names can also occur in their own function bodies, as we
; will see very soon.

; functions with this property are said to be recursive


; functions may have more than one argument - for example

(define (sum-of-squares x y)
  (+ (square x) (square y)))


; now we can use sum-of-squares as a building block in constructing
; further procedures

(define (f a)
  (sum-of-squares (+ a 1) (* a 2)))


(f 5)


; functions can also have 0 arguments

(define (one) 1)


; 1.1.5 The Substitution Model for Procedure Application

; To apply a compound procedure to arguments, evaluate the body of the
; procedure with each formal parameter replaced by the (value of) the
; corresponding argument

; to illustrate:

; (f 5)

; ((sum-of-squares (+ a 1) (* a 2)) 5)

; (sum-of-squares (+ 5 1) (* 5 2))

; (sum-of-squares 6 10)

; (+ (square 6) (square 10))

; (+ (* 6 6) (* 10 10))

; (+ 36 100)

; 136
