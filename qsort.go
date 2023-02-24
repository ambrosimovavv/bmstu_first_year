//Быстрая сортировка 
package main
import (
	"fmt"
	"github.com/skorobogatov/input"
)

func Partition (less func (i, j int) bool, swap func (i, j int), Low, Hight int) int {
	var i, VariableL int
	VariableL = Low
	for i = Low ; i < Hight; i++ {
		if  less (i, Hight){
			swap (VariableL, i)
			VariableL++
			}
		}
	swap (VariableL, Hight)
	return VariableL
}

func QuickSortRec  (less func (i, j int) bool, swap func (i, j int), Low, Hight int) {
	var ResultPartition int
	if Low < Hight {
		ResultPartition = Partition  (less, swap, Low, Hight)
		QuickSortRec( less, swap, Low, ResultPartition - 1)
		QuickSortRec( less, swap, ResultPartition + 1, Hight)
	}
}

func QuickSort (n int, swap func (i, j int), less func (i, j int) bool){
	QuickSortRec (less, swap, 0, n - 1)
}

func main () {
	var  i, n int
	input.Scanf("%d", &n)
	a := make ([] int, n)
	for i = 0; i < n; i++ {
		input.Scanf ("%d", &a[i])
	}
	QuickSort (n,
		 func (i, j int) { a[i], a[j] = a[j], a[i] },
		func (i, j int) bool { return a[i] < a[j] })
	for i = 0; i < n; i++ {
		fmt.Printf ("%d ", a[i])
	}
}
