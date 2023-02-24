; перевод из одной системы счисления в другую
(define (power a b)
  (define (power-rec x y res)
    (cond 
      ((= y 0) 1)
      ((= y 1) res)
      (else (power-rec x (- y 1) (* res x)))))
  (power-rec a b a))

(define (certain->decimal s b)
  (if (not (correct-number? s b))
   'number-conversion-error
   (cer-dec (string->list s) b 0))) 
  
   
(define (cer-dec lst a res)
  (cond
    ((null? lst) res)
    ((> (char->integer (car lst)) 96) (cer-dec (cdr lst) a 
                                                  (+ res (* (- (char->integer (car lst)) 87) (power a (- (length lst) 1))))))
    ((> (char->integer (car lst)) 64) (cer-dec (cdr lst) a 
                                                  (+ res (* (-  (char->integer (car lst)) 55) (power a (- (length lst) 1))))))
    ((> (char->integer (car lst)) 47) (cer-dec (cdr lst) a
                                                   (+ res (* (-  (char->integer (car lst)) 48) (power a (- (length lst) 1))))))))
(define (correct-number? s b)
  (define (cheak lst x)
    (cond
      ((null? lst) #t)
      ((and (> (char->integer (car lst)) 47) (> x (- (char->integer (car lst)) 48))) (cheak (cdr lst) x))
      ((and (> (char->integer (car lst)) 64) (> x (- (char->integer (car lst)) 55))) (cheak (cdr lst) x))
      ((and (> (char->integer (car lst)) 96) (> x (- (char->integer (car lst)) 87))) (cheak (cdr lst) x))
      (else #f)))
  (cheak (string->list s) b))

(define (decimal->certain a b)
  (define (dec-cer x y res)
    (cond
      ((= x 0) (list->string res))
      ((> (remainder x y) 9) (dec-cer (quotient x y) y (cons (integer->char (+ (remainder x y) 55)) res)))
      (else (dec-cer (quotient x y) y (cons (integer->char (+ (remainder x y) 48)) res)))))
  (dec-cer a b '()))
 
