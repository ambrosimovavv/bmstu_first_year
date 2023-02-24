//число мостов
package main

import (
        "fmt"
	"github.com/skorobogatov/input"
)

type elem struct {
	p_elem *elem
	v int
}

type El struct {
	p_elem *elem
	c, m, i int
	par_El *El
}

func InsertBefore (arr []El, e elem, v, u  int) {
	arr[v].m = 0
	arr[v].c = -1
	e.v = u
	e.p_elem = arr[v].p_elem
	arr[v].p_elem = &e
}

func VisVert1 (arr []El, E El, Chanel chan int) {
	var a *elem
	arr[E.i].m = 1
	Chanel <- E.i
	a = E.p_elem
	for a != nil {
		b := arr[a.v]
		if b.m == 0 {
			arr[b.i].par_El = &arr[E.i]
			VisVert1 (arr, b, Chanel)
		}
		a = a.p_elem
	}
}
	
func DFS1 (arr []El, Chanel chan int) int {
	var count, n int
	n = len (arr)
	for i := 0; i < n; i++ {
		a := arr[i]
		if a.m == 0 {
			count++
			VisVert1 (arr, a, Chanel)
		}
	}
	close (Chanel)
	return count
}

func VisVert2 (arr []El, E El, c int) {
	arr[E.i].c = c
	var x *elem
	x = E.p_elem
	for  x != nil {
		a := arr[x.v]
		if (a.c < 0) && (*arr[a.i].par_El != arr[E.i]) {
			VisVert2 (arr, a, c)
		}
		x = x.p_elem
	}
}

func DFS2 (arr []El, Chanel chan int) (c int) {
	for i := range Chanel {
		a := arr[i]
		if a.c < 0 {
			c++
			VisVert2 (arr, a, c)
		}
	}
	return
}

func main () {
	var n, m, v, u, i, answ, c int
	var a, b elem
	input.Scanf ("%d%d", &n, &m)
	arr := make ([]El, n)
	for i = 0; i < n; i++ {
		arr[i].i = i
	}
	for i = 0; i < m; i++ {
		input.Scanf ("%d%d", &v, &u)
		InsertBefore(arr, a, v, u)
		InsertBefore(arr, b, u, v)
	}
	Chanel := make (chan int, n)
	c = DFS1 (arr, Chanel)
	answ = DFS2 (arr, Chanel)
	fmt.Printf ("%d\n", answ - c)
}