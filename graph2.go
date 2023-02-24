package main

import (
        "fmt"
	"sort"
	"strconv"
	"github.com/skorobogatov/input"
)


type (
	sw struct {
		A, B int
		C string
	}
	out struct { A, B string }
	Stack struct {
		data [][]int
		top int
	}
)

func (s *Stack) Push(n []int) {
	s.data = append(s.data[:s.top], n)
	s.top++
}
func (s *Stack) Pop() []int {
	s.top--
	return s.data[s.top]
}

func (s *Stack) StackEmpty() bool {
	if s.top == 0 { return true } 
	return false
}

func DFS (q, λ int, C *(map[int]int), delta [][][]int) {
	if _, ok := (*C)[q]; !ok {
		(*C)[q] = q
		if λ != -1 {
			for _, w := range delta[q][λ] { DFS(w, λ, C, delta) }
		}
	}
}

func Closure (λ int, delta [][][]int, z []int) []int {			
	C, out := make(map[int]int, 0), make([]int, 0)
	for _, q := range z { DFS (q, λ, &C, delta) }
	for _, q := range C { out = append(out, q) }
	return out
}

func MakeLabel (z []int, n int) (str string) {
	str = "["
	for i := 0; i < n-1; i++ {
		str += strconv.Itoa(z[i])
		str += ","
	}
	if n != 0 { str += strconv.Itoa(z[n-1]) }
	str += "]"
	return
}

func Det (St, λ int, X map[string]int, F []int, X1[]string, delta [][][]int) {
	var (
		s Stack
		tmp out
	)
	Q, F1, Out := make(map[string]int), make(map[string]bool, 0), make(map[out][]string, 0)
	
	xx := make([]int, 0)
	q0 := Closure (λ, delta, append(xx, St))
	sort.Ints(q0)
	buf := MakeLabel (q0, len(q0))
	Q[buf] = len(Q)
	s.Push(q0)
	
	for !s.StackEmpty() {
		z := s.Pop()
		z_str := MakeLabel(z, len(z))
		F1[z_str] = false
		for _, u := range z {
			if F[u] == 1 {
				F1[z_str] = true
				break
			}
		}
		
		for _, k := range X {
			if k == λ { continue }
			
			tmp2 := make([]int, 0)
			for _, u := range z {
				for _, tr := range delta[u][k]{
					tmp2 = append(tmp2, tr)
				}
			}
			z1 := Closure (λ, delta, tmp2)
			sort.Ints(z1)
			z1_str := MakeLabel(z1, len(z1))
			if _, ok := Q[z1_str]; !ok {
				Q[z1_str] = len(Q)
				s.Push(z1)
			}
			tmp.A, tmp.B = z_str, z1_str
			Out[tmp] = append(Out[tmp], X1[k])
		}
	}
	Diagram (Q, F1, Out)
}

func Init () (St, λ int, X map[string]int, F []int, X1[]string, delta [][][]int) {
	X, X1 =  make(map[string]int, 0), make([]string, 0)
	var (
		N, M, count int
		Sw []sw
	)
	input.Scanf ("%d%d", &N, &M)
	Sw, F, delta = make([]sw, M),make([]int, N), make([][][]int, N)
	λ = -1
	for i := 0; i < M; i++ {
		input.Scanf ("%d%d%s", &Sw[i].A, &Sw[i].B, &Sw[i].C)
		if _, ok := X[Sw[i].C]; !ok {
			if Sw[i].C == "lambda"{ λ = count }
			X[Sw[i].C] = count
			count++
			X1 = append(X1, Sw[i].C)
		}
	}
	for i := 0; i < N; i++ { input.Scanf ("%d", &F[i]) }
	input.Scanf ("%d", &St)
	for i := 0; i < N; i++ { delta[i] = make([][]int, count) }
	for i := 0; i < M; i++ { 
		delta[Sw[i].A][X[Sw[i].C]] = append(delta[Sw[i].A][X[Sw[i].C]], Sw[i].B) 
	}
	return
}

func Diagram (Q map[string]int, F1 map[string]bool, Out map[out][]string) {
	fmt.Printf("digraph {\n\trankdir = LR\n\tdummy [label = \"\", shape = none]\n")
	for k, v := range Q {
		if fmt.Printf("\t%d [label = \"%s\", ", v, k);  !F1[k] {
			fmt.Printf("shape = circle]\n")
		} else { fmt.Printf("shape = doublecircle]\n") }
	}
	fmt.Printf("\tdummy -> 0\n")
	for k, v := range Out {
		fmt.Printf("\t%d -> %d [label = \"", Q[k.A], Q[k.B])
		for j, n := 0, len(v); j < n-1; j++ { fmt.Printf("%s, ", v[j])}
		fmt.Printf("%s\"]\n", v[len(v)-1])
	}
	fmt.Printf("}\n")
}

func main() {
	Det(Init())
} //10