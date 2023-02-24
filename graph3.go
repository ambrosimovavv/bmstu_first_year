//число компонент связности
package main

import (
        "fmt"
	"github.com/skorobogatov/input"
)

type elem struct {
	d int
	p *elem
}

func FindRoot(x *elem) *elem {
	if x == x.p {
		return x
	}
	x.p = FindRoot(x.p)
	return x.p
}
func main() {
	var i, n, m, a, b, c int
	input.Scanf("%d%d", &n, &m)
	arr := make([]elem, n)
	for i = 0; i < n; i++ {
		arr[i].p = &arr[i]
	}
	for i = 0; i < m; i++ {
		input.Scanf("%d%d", &a, &b)
		x := FindRoot(&arr[a])
		y := FindRoot(&arr[b])
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
		}
	}
	fmt.Printf("%d", n-c)
}
