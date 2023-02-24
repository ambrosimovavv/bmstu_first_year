package main
import "fmt"
import "github.com/skorobogatov/input"
type Vert struct {
	array []int
	depth, val int
	parent *Vert
}
func Find(elem *Vert) *Vert {
	if elem.parent == elem {
		return elem
	}	
	elem.parent = Find(elem.parent)
	return elem.parent
}
func Split1(conv []Vert, sign [][]rune, classes *map[int]int) int {
	res, equal := len(conv), false
	var prom1, prom2 *Vert
	for i := 0; i < len(conv); i++ {
		conv[i].parent = &conv[i]
		conv[i].depth, conv[i].val = 0, i
	}
	for i:= 0; i < len(conv); i++ {
		for j := i+1; j < len(conv); j++ {
			prom1, prom2 = Find(&conv[i]), Find(&conv[j])
			if prom1.val != prom2.val {
				equal = true
				for k := 0; k < len(sign[0]); k++ {
					if sign[i][k] != sign[j][k] {
						equal = false
						break
					}
				}
			}
			if equal {
				if prom1.depth < prom2.depth {
					prom1.parent = prom2
				} else {
					prom2.parent = prom1
					if prom1.depth == prom2.depth {
							prom1.depth++
					}
				}
				res--
			}
		}
	}
	for i := 0; i < len(conv); i++ {
		(*classes)[i] = Find(&conv[i]).val+1
	}
	return res
}
func Split(conv []Vert, sign [][]rune, classes *map[int]int) int {
	res, equal := len(conv), false
	var prom1, prom2 *Vert
	for i := 0; i < len(conv); i++ {
		conv[i].parent = &conv[i]
		conv[i].depth, conv[i].val = 0, i
	}
	for i:= 0; i < len(conv); i++ {
		for j := i+1; j < len(conv); j++ {
			equal = false
			prom1, prom2 = Find(&conv[i]), Find(&conv[j])
			if ((*classes)[i] == (*classes)[j]) && (prom1.val != prom2.val) {
				equal = true
				for k := 0; k < len(sign[0]); k++ {
					if (*classes)[conv[i].array[k]] != (*classes)[conv[j].array[k]] {
						equal = false
						break
					}
				}
			}
			if equal {
				if prom1.depth < prom2.depth {
					prom1.parent = prom2
				} else {
					prom2.parent = prom1
					if prom1.depth == prom2.depth {
						prom1.depth++
					}
				}
				res--
			}
		}
	}
	for i := 0; i < len(conv); i++ {
		(*classes)[i] = Find(&conv[i]).val+1
	}
	return res
}
var check, reverce map[int]int
func canon(conv []Vert, sign [][]rune, ent int, classes map[int]int) {
	check[classes[ent]-1] = len(check)+1
	reverce[len(check)-1] = classes[ent]
	for i := 0; i < len(sign[classes[ent]-1]); i++ {
		if check[classes[conv[classes[ent]-1].array[i]]-1] == 0 {
			canon(conv, sign, conv[classes[ent]-1].array[i], classes)
		}
	}
}
func minimize(n int, m int, conv []Vert, sign [][]rune, ent int) {
	var cnum, cnumnew int
	classes := make(map[int]int, 0)
	cnum = Split1(conv, sign, &classes)
	for ;; {
		cnumnew = Split(conv, sign, &classes)
		if cnum == cnumnew {
			break
		}
		cnum = cnumnew
	}
	check, reverce = make(map[int]int, 0), make(map[int]int, 0)
	canon(conv, sign, ent, classes)
	fmt.Printf("digraph {\n rankdir = LR\n dummy [label = \"\", shape = none]\n")
	for i := 0; i < len(check); i++ {
		fmt.Printf(" %d [shape = circle]\n", i)
	}
	fmt.Printf(" dummy -> %d\n", check[classes[ent]-1]-1)
	for i:= 0; i < len(check); i++ {
		for j := 0; j < m; j++ {
			fmt.Printf(" %d -> %d [label = \"%c(%c)\"]\n", i, check[classes[conv[reverce[i]-1].array[j]]-1]-1, 'a'+j, sign[reverce[i]-1][j])
		}
	}
	fmt.Printf("}\n")
}
func main () {
	var n, m, ent int
	input.Scanf("%d\n%d\n%d\n", &n, &m, &ent)
	conv := make([]Vert, n)
	for i := 0; i < n; i++ {
		conv[i].array = make([]int, m)
		for j := 0; j < m; j++ {
			if j == m-1 {
				input.Scanf("%d\n", &conv[i].array[j])
				continue
			}
			input.Scanf("%d ", &conv[i].array[j])
		}
	}
	sign := make([][]rune, n)
	for i := 0; i < n; i++ {
		sign[i] = make([]rune, m)
		for j := 0; j < m; j++ {
			if j == m-1 {
				input.Scanf("%c\n", &sign[i][j])
				continue
			}
			input.Scanf("%c ", &sign[i][j])
		}
	}
	minimize(n, m, conv, sign, ent)
}