#include <stdio.h>
#include <stdlib.h>
int *array;
void swap(int i, int j) 
{ 
        int t = array[i]; 
        array[i] = array[j]; 
        array[j] = t; 
} 
int Partition (int begin, int end, void (*swap)(int i, int j))
{
    int i = begin, j = 0;
    for (j = begin; j < end; j++){
        if (array[j] <= array[end]){
                     swap(i, j);
                     i++;
        } 
    }
    swap(i, end); 
    return i; 
}  
 
void SelectSort (int first_elem, int last_elem)
{ 
    int i, j, max, t;     
    j = last_elem - first_elem; 
    for (j; j > 0; j--){
      max = j;
      for (i = j - 1; i >= 0; i--)
        if (array[max + first_elem] < array[i + first_elem]) max = i;
      t = array[j + first_elem];
      array[j + first_elem] = array[max + first_elem];
      array[max + first_elem] = t;
    }
}   
        
                      
void *QuickSort (int begin, int end, int m)
{
        marker: if (end - begin + 1> m){
		if (end > begin){
			int q = Partition (begin, end, swap);
			if ((q - begin) < (end - q)) {
				QuickSort(begin, q - 1, m);
				begin = q + 1;
				goto marker;
			}else{			
				QuickSort(q, end, m);
				end = q - 1;
				goto marker;
			}                
		}
	} else SelectSort (begin, end);  
}       
int main ()  
{
    int n, m, i;
    scanf ("%d", &n);
    scanf ("%d", &m); 
    array = malloc(n*sizeof(int));
    for (i = 0; i < n; i++) scanf ("%d", array+i);
    QuickSort (0, n-1, m);
    for (i = 0; i < n; i++) {
            printf ("%d ", array[i]);
    }
    free(array); 
}         
 