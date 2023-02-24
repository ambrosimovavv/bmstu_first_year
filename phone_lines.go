//телефонные линии
package main 
import (
        "fmt"
	"github.com/skorobogatov/input"
)

type elem struct {
	p_elem *elem
	v, l int
}

type El struct {
	p_elem *elem
	k, i int
}
type queue struct {
	h []*El
	c int
}

func Heapify (arr_El [] *El, i, n int) {
	var left, right, j int
	for {
		left = 2*i + 1
		right = 2*i + 2
		j = i
		if (left < n) && (arr_El[i].k > arr_El[left].k) {
			i = left
		}
		if (right < n) && (arr_El[i].k > arr_El[right].k) {
			i = right
		}
		if i == j {
			break
		}
		arr_El[i], arr_El[j] = arr_El[j], arr_El[i]
		arr_El[i].i = i
		arr_El[j].i = j
	}
}

func Insert (que *queue, E *El) {
	var i, j int
	i = que.c
	que.c++
	que.h[i] = E
	j = (i-1)/2
	for i > 0 {
		if que.h[j].k <= E.k {
			break
		}
		que.h[j], que.h[i] = que.h[i], que.h[j] 
		que.h[i].i = i
		i = j
		j = (j-1)/2
	}
	que.h[i].i = i
}
func ExtractMin (que *queue) *El {
	var min_El *El
	min_El = que.h[0]
	que.c--
	t := que.c
	if que.c != 0 {
		que.h[0] = que.h[t]
		que.h[0].i = 0
		Heapify (que.h, 0, t)
	}
	return min_El
}
func DecK (que *queue, i, k int) {
	var j int
	que.h[i].k = k
	j = (i-1)/2
	for i > 0 {
		if que.h[j].k <= k{
			break
		}
		que.h[j], que.h[i] = que.h[i], que.h[j]
		que.h[i].i = i
		i = j
		j = (j-1)/2
	}
	que.h[i].i = i
}
func Prim (E [] El, que queue, n int) int {
	var answ int
	var x *El
	x = &E[0]
	for {
		//fmt.Print ("!\n")
		x.i = -101
		e := x.p_elem
		for e != nil {
			//fmt.Print ("  !!\n")
			a := &E[e.v]
			l := e.l
			if a.i == -100 {
				a.k = l
				Insert (&que, a)
			} else if (a.i != -101) && (l < a.k){
				DecK (&que, a.i, l)
			}
			e = e.p_elem
		}
		if que.c == 0 {
			break
		}
		x = ExtractMin(&que)
		answ += x.k
	}
	return answ
}

func main () {
	var n, m, i, u, v, l int
	var que queue
	input.Scanf ("%d%d", &n, &m)
	arr_El := make ([] El, n)
	for i = 0; i < m; i++ {
                var e1, e2 elem
		input.Scanf ("%d%d%d", &u, &v, &l)
		e1.v = u
		e1.l = l
		e1.p_elem = arr_El[v].p_elem
		e2.v = v
		e2.l = l
		e2.p_elem = arr_El[u].p_elem
		arr_El[v].p_elem = &e1
		arr_El[u].p_elem = &e2
	}
	que.h = make ([] *El, n - 1) 
	for i = 0; i < n; i++ {
		arr_El[i].i = -100
	}
	answ := Prim(arr_El, que, n)
	fmt.Printf ("%d \n", answ)
}