
; csc 335 Lecture 2
; February 3 2015


					;
; we begin class with a brief - and very simple! - quiz, offered in self-diagnostic mode
;
; 1.  In Scheme, define a function which inputs one argument - a number -
;     and which returns the square of that number
;
; 2.  In Scheme, define a function f which inputs one argument x - a number -
;     and which returns the sum of (17 + x)^2 and (x - 2)^2.  Use the square
;     function you defined for problem 1.
;
; 3.  Use the substitution model to explain Scheme's evaluation of (f 3)

; (Solutions given in class)


; next, let's return to Chapter 1 of Abelson and Sussman


; 1.1.6 Conditional Expressions and Predicates

(define (myabs x)
  (cond ((> x 0) x)
	((= x 0) 0)
	(else (- x))))

(myabs -4)

; another way

(define (myabs x)
  (cond ((< x 0) (- x))
	(else x)))

; another way

(define (myabs x)
  (if (< x 0)
      (- x)
      x))


; >, =, < are primitive predicates

; Scheme also supplies logical connectives such as and, or, not

(define x 6)

(and (> x 5) (< x 10))

(not (> x 4))

#f

(not #f)

(= x 6)

; and so on



; note that cond and if do not obey the standard evaluation rule -

; (cond (p1 e1) (p2 e2) ... (pn en) (else E)) is evaluated as follows:
;   evaluate p1 -- if #t, then evaluate e1 and return this value
;   otherwise evaluate p2 -- if #t, evaluate e2 and return this value
;   otherwise evaluate p3 -- if #t, evaluate e3 and return this value

;   and so on.  If none of the pi is #t, evaluate E and return this value


; similarly, (if p1 e1 e2) evaluates e1, but not e2, if p1 is #t; it
; evaluates e2, but not e1, if p1 is #f


; cond and if are said to be special forms

; can you see that define is also a special form?  explain!


; it is interesting to note that cond and if forms can be evaluated
; by themselves - they do not need to be embedded in a function
; definition

(define x 6)

(cond ((> x 6) 1)
      ((< x 6) 2)
      (else 0))


(if (= x 6) 2 3)

; and even such expressions as

(+ (cond ((> x 6) 0)
	 (else 1))
   2)



; let's have another example or two

; first, we observe that the substitution model of evaluation described 
; above allows for combinations whose operators are compound expressions. 

(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))

; the first item in the list -- namely (if (> b 0) + -) -- is equal 
; to + if (> b 0), and otherwise -

; thus 

(a-plus-abs-b 4 -5)

; is 9




; next, we write a program to compute the sum of the squares of the two larger
; of three inputs

(define (sum-square-of-two-largest x y z)
  (cond ((= x (min x y z)) (+ (square y) (square z)))
	((= y (min x y z)) (+ (square x) (square z)))
	(else (+ square x) (square y))))

; or, more elegantly, using the special form let, 

(define (sum-squares-of-two-largest x y z)
  (let ((m (min x y z)))
    (cond ((= m x) (+ (square y) (square z)))
	  ((= m y) (+ (square x) (square z)))
	  (else (+ (square x) (square y))))))



; let defines a local variable, with scope just the body of the
; function sum-squares-of-two-largest


; another way to obtain a local variable would be to use define as follows

(define (sum-squares-of-two-largest x y z)
  (define m (min x y z))
  (cond ((= m x) (+ (square y) (square z)))
	((= m y) (+ (square x) (square z)))
	(else (+ (square x) (square y)))))


; this would be considered less elegant than our first version.





; An alternate model for procedure evaluation

; according to the description of evaluation given above, the interpreter
; first evaluates the operator and operands and then applies the resulting
; procedure to the resulting arguments

; this is called applicative order, or call-by-value

; another possibility: hold off on evaluating the operands until their
; values are actually needed.

; this is called normal order, or call-by-name



; let's recall the earlier example

(define (f a)
  (sum-of-squares (+ a 1) (* a 2)))

; using applicative order, the evaluation proceeds as

; (f 5)

; ((sum-of-squares (+ a 1) (* a 2)) 5)

; (sum-of-squares (+ 5 1) (* 5 2))

; (sum-of-squares 6 10)

; (+ (square 6) (square 10))

; (+ (* 6 6) (* 10 10))

; (+ 36 100)

; 136





; using normal order, on the other hand, we obtain the same value 
; as before, but the computation proceeds differently:

; (f 5)

; ((sum-of-squares (+ a 1) (* a 2)) 5)

; (sum-of-squares (+ 5 1) (* 5 2))

; (+ (square (+ 5 1)) (square (* 5 2)))

; (+ (* (+ 5 1) (+ 5 1)) (* (* 5 2) (* 5 2)))

; (+ (* 6 6) (* 10 10))

; (+   36      100)

; 136




; applicative and normal order evaluation do not always give the same result

; consider

(define (p) (p))

(define (test x y)
  (if (= x 0)
      0
      y))

; what will happen if (test 0 (p)) is evaluated using applicative order?  why?
; what will happen if it is evaluated using normal order?


; you can stop an infinite loop under DrRacket by using the red Stop button
; at the top right of your screen




; remark

(if #t 0 (p))

; returns 0 -- because if is a special form, the infinite loop (p) is never evaluated

; to drive this point home, suppose that instead of if, we defined our own function, new-if:

(define (new-if predicate then-clause else-clause)
  (cond (predicate then-clause)
	(else else-clause)))

(new-if (> 2 0) 3 4)

(new-if (> 2 3) 3 4)

; this seems to work!  But should we try ...


(let ((x 0))
  (new-if (= x 0) 
      0
      (p)))


; we find that we have an infinite loop, precisely because the standard evaluation
; rules apply to the user-defined function new-if: new-if is not a special form


; Let us look next at a somewhat longer program in scheme,
; implementing Newton's method for computing square roots,
; to give an idea how one can combine procedures to produce
; larger procedures


; primary interface 


(define (sqrt x)
 (sqrt-iter 1.0 x))

; main auxilliary function

(define (sqrt-iter guess x)
 (if (good-enough? guess x)
     guess
     (sqrt-iter (improve guess x)
                 x)))

; the stopping test

(define (good-enough? guess x)
  (< (abs (- (square guess) x))
     .001))

; derive improve from f(x) = (x^2 - a) using basic calculus  

(define (improve guess x)
 (average guess (/ x guess)))


; other auxilliary functions for sqrt

(define (average x y) (/ (+ x y) 2))

(define (square x) (* x x))


(define (abs x)
 (if (>= x 0)  
     x
     (- x)))




; You might want to check: what happens when the initial guess 1.0
; is replaced by -1.0?  By 25.0?  




; in preparation for the next class, please read, in Abelson and Sussman, Sections 1.1.7, 1.1.8 and 1.2.1
