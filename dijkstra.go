//кратчайший путь 
package main 
import (
        "fmt"
	"github.com/skorobogatov/input"
)

type elem struct {
	d, x, y, i, v int
}

func MakeMap (n int) [][]elem{ 
	array := make([][]elem, n)
	for i := 0; i < n; i++ {
		array[i] = make([]elem, n)
		for j := 0; j < n; j++ {
			input.Scanf("%d", &array[i][j].v)
			array[i][j].d = -1
			array[i][j].x, array[i][j].y = i, j
		}
	}
	array[0][0].d = array[0][0].v
	return array
}

func MakeQueue (array [][]elem, n int) []*elem {
	que := make ([]*elem, 0)
	for i:= 0; i < n; i++ {
		for j := 0; j < n; j++ {
			array[i][j].i = i*n+j
			que = append(que, &array[i][j])
		}
	}
	return que
}

func DecKey(que []*elem, el  elem) {
	i := el.i
	que[i].d = el.d
	for (i > 0) && (((que[(i-1)/2].d > que[i].d) && (que[i].d >= 0)) || ((que[(i-1)/2].d < 0) && (que[i].d >= 0))) {
		que[(i-1)/2], que[i] = que[i], que[(i-1)/2]
		que[i].i = i
		i = (i-1)/2
		}
		que[i].i = i
}

func Heapify(que []*elem, n int) {
	var left, right, j, i int
	for {
		left = 2*i+1
		right = left+1
		j = i
		if (left < n) && (((que[i].d > que[left].d) && (que[left].d >= 0)) || ((que[i].d < 0) && (que[left].d >= 0))) {
			i = left 
			}
		if (right < n) && (((que[i].d > que[right].d) && (que[right].d >= 0)) || ((que[i].d < 0) && (que[right].d >= 0))) { 
			i = right 
		}
		if i == j { break }
		que[i].i, que[j].i = que[j].i, que[i].i
		que[i], que[j] = que[j], que[i]
	}
}

func ExtractMin(que []*elem, n int) (int, elem) {
	el := que[0]
	n--
	if n != 0 {
		que[0] = que[n]
		que[0].i = 0
		Heapify(que, n)
	}
	return n, *el
}

func Relax(array[][]elem, s, d elem) bool {
	c := s.d +d.v
	res := (c < d.d) || (d.d < 0)
	if res {
		array[d.x][d.y].d = c
	}
	return res
} 


func Dijkstra(array [][]elem) int {
	var el elem
	n := len(array)
	queue := MakeQueue(array, n)
	n = n*n
	for n > 0 {
		n, el = ExtractMin(queue, n)
		a := el.x
		b := el.y
		array[a][b].i = -1
		for i := -1; i < 2; i+=2 {
			if (a+i >= 0) && (a+i < len(array)) && (array[a+i][b].i != -1) && (Relax(array, el, array[a+i][b])) {
				DecKey(queue, array[a+i][b])
			}
			if (b+i >= 0) && (b+i < len(array)) && (array[a][b+i].i != -1) && (Relax(array, el, array[a][b+i])) {
				DecKey(queue, array[a][b+i])
			}
		}
	}
	n = len(array)
	return array[n-1][n-1].d
}

func main () {
	var n int
	var array[][] elem
	input.Scanf ("%d", &n)
	array = MakeMap(n)
	res := Dijkstra(array)
	fmt.Printf("%d\n", res)
}