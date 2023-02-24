//n-е число Фиббоначи
package main
import (
        "fmt"
	"math/big"
)
type matrix [4](*big.Int)

func Mul_Matrix (A, B matrix) matrix {
	var answ matrix
	var ab_0, ab_1 big.Int
	var arr[4] big.Int
	ab_0.Mul(A[0], B[0])
	ab_1.Mul(A[1], B[2])
	arr[0].Add(&ab_0, &ab_1)
	answ[0] = &arr[0]
	
	ab_0.Mul(A[0], B[1])
	ab_1.Mul(A[1], B[3])
	arr[1].Add(&ab_0, &ab_1)
	answ[1] = &arr[1]
	
	ab_0.Mul(A[2], B[0])
	ab_1.Mul(A[3], B[2])
	arr[2].Add(&ab_0, &ab_1)
	answ[2] = &arr[2]
	
	ab_0.Mul(A[2], B[1])
	ab_1.Mul(A[3], B[3])
	arr[3].Add(&ab_0, &ab_1)
	answ[3] = &arr[3]
	return answ
}

/*func Power_Matrix (A matrix, n int) matrix {
	var B matrix
	B = A
	for i := 1; i < n; i++ {
		B = Mul_Matrix(A, B) 
	}
	return B
}*/
func Power_Matrix (A matrix, n int) matrix {
	if n == 1 { return A }
	K := Power_Matrix (A, n/2)
	R := Mul_Matrix(K, K)
	return R
}
func main () {
	var n, i, ind int
	var C, A, B matrix
	fmt.Scanf("%d", &n)
	C[0] = big.NewInt(1)
	C[1] = big.NewInt(1)
	C[2] = big.NewInt(1)
	C[3] = big.NewInt(0)
	if n == 1 {
		fmt.Print ("1") 
	} else {
		i = 1
		n--
		for n > 0{
			if n & 1 != 0 {
				if ind == 0 {
					A = Power_Matrix (C, i)
					ind = 1
				} else {
					B = Power_Matrix (C, i)
					A = Mul_Matrix (A, B)
				}
			}
			i *= 2
			n /=2
		}
		fmt.Print (A[0]) 
	}
}
