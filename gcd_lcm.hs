main :: IO ()
mygcd a b = mygcd' (abs a) (abs b) where
	mygcd' x 0 = x
	mygcd' x y = mygcd' y (rem x y)

mylcm m n = mylcm' (abs m) (abs n) where
	mylcm' 0 k = 0
	mylcm' l 0 = 0
	mylcm' l k = abs ((quot l (gcd l k)) * k)
--main = print $ mygcd 16 24
--main = print $ mylcm 5 3

prime m = [(m, n)| n <- [1..m], mygcd m n == 1]
main = print $ prime 7