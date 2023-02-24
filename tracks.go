//дорожки в парке
package main

import (
        "fmt"
	"math"
	"github.com/skorobogatov/input"
)

type elem struct {
	d int
	c1, c2 float64
	p *elem
}
type dist struct{
	dis float64
	i, j int
}

func FindRoot(x *elem) *elem {
	if x == x.p {
		return x
	}
	x.p = FindRoot(x.p)
	return x.p
}

func Heapify (a_d [] dist, i, n int) {
	var left, right, j int
	for {
		left = 2*i + 1
		right = 2*i + 2
		j = i
		if (left < n) && (a_d[i].dis > a_d[left].dis) {
			i = left
		}
		if (right < n) && (a_d[i].dis > a_d[right].dis) {
			i = right
		}
		if i == j {
			break
		}
		a_d[i], a_d[j] = a_d[j], a_d[i]
	}
}

func Bild (n int, a_d []dist) {
	for i :=n/2 - 1; i >= 0; i-- {
		Heapify (a_d, i, n)
	}
}

func Kruskal (a_e []elem, a_d []dist, n int) float64{
	var answ float64
	var c int 
	m := len (a_d)
	for i := m - 1; i >= 0; i-- {
		if c >= n { break }
		a := a_d[0].i
		b := a_d[0].j
		x := FindRoot(&a_e[a])
		y := FindRoot(&a_e[b])
		if x != y { 
			c++
			if x.d < y.d {
				x.p = y
			} else {
				y.p = x
				if x.d == y.d {
					x.d++
				}
			}
			answ += a_d[0].dis
		}
		a_d[0], a_d[i] = a_d[i], a_d[0]
		Heapify (a_d, 0, i)
	}
	return answ
}

func InitDistStruct (i, j, l int, arr_e []elem, arr_d [] dist) {
	sq_c1 := (arr_e[i].c1 - arr_e[j].c1) * (arr_e[i].c1 - arr_e[j].c1)
	sq_c2 := (arr_e[i].c2 - arr_e[j].c2) * (arr_e[i].c2 - arr_e[j].c2)
	d := math.Sqrt(sq_c1 + sq_c2)
	arr_d[l].dis = d
	arr_d[l].i = i
	arr_d[l].j = j
}

func main () {
	var n, l, i, j int
	input.Scanf ("%d", &n)
	arr_e := make ([]elem, n)
	arr_d := make ([]dist, n*(n - 1)/2)
	for i = 0; i < n; i++ {
		input.Scanf ("%f %f", &arr_e[i].c1, &arr_e[i].c2)
		arr_e[i].p = &arr_e[i]
	}
	for i = 0; i < n; i++ {
		for j = i +1; j < n; j++{
			InitDistStruct (i, j, l, arr_e, arr_d)
			l++
		}
	}
	Bild (len (arr_d), arr_d)
	res := Kruskal (arr_e, arr_d, n - 1)
	fmt.Printf ("%.2f \n", res)
}	