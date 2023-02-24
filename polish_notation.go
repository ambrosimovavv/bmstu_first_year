//экономное вычисление выражений в польской записи
package main

import  "fmt"

func main (){
        var expr string
	var arr_of_expr [] rune
	var help_arr [] int
	var count, i, j, n, answ int
	fmt.Scan (&expr)
	arr_of_expr = []rune (expr)
	if arr_of_expr[0] == '(' {
		n = len (arr_of_expr)
		help_arr = make ([]int, 50)
		str := make (map [string] int, 50)
		for i = 0; i < n; i++ {
			if arr_of_expr[i] == '(' {
				count++
				help_arr[count] = i + 1
			}
			if arr_of_expr[i] == ')' {
				j = help_arr[count]
				count--
				_, full := str[expr[j:i]]
				if !full {
					str[expr[j:i]] = 0
					answ++
				}
			}
		}
		fmt.Printf ("%d", answ)
	} else {
		fmt.Print ("0")
	}
}