//сортировка слиянием на сопрограммах
package main
import (
        "fmt"
	"github.com/skorobogatov/input"
)
func Merge (first chan int, second chan int, answ chan int) {
	var abs_x, abs_y int
	x, full_frs_chan := <- first
	y, full_scn_chan := <- second
	for {
		if full_frs_chan && !full_scn_chan {
			for full_frs_chan {
				answ <- x
				x, full_frs_chan = <- first
			}
			break
		}
		if full_scn_chan && !full_frs_chan {
			for full_scn_chan {
				answ <- y
				y, full_scn_chan = <- second
			}
			break
		} 
		if full_frs_chan && full_scn_chan {
			if x < 0 {
				abs_x = -1*x
			} else {
				abs_x = x
			}
			if y < 0 {
				abs_y = -1*y
			} else {
				abs_y = y
			}
			if abs_y < abs_x {
				answ <- y
				y, full_scn_chan = <- second
			} else {
				answ <- x
				x, full_frs_chan = <- first
			}
		}
	}
	close (answ)
}

func Mergesort (array [] int, channel chan int, n int) {
	if n == 1 {
		channel <- array[0]
		close (channel)
	} else {
		first := make (chan int)
		second := make (chan int)
		go Mergesort (array[:n/2], first, n/2)
		go Mergesort (array[n/2:], second, (n - n/2))
		go Merge (first, second, channel)
	}
}

func main () {
	var n, i int 
	input.Scanf ("%d", &n)
	array := make ([] int, n)
	channel := make (chan int)
	for i = 0; i < n; i++ {
		input.Scanf ("%d", &array[i])
	}
	go Mergesort (array, channel, n)
	x, full := <- channel
	for full {
		fmt.Printf ("%d ", x)
		x, full = <- channel 
	}
}