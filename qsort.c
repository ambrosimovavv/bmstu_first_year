#include <stdio.h>
#include <stdlib.h>
int *array;
struct Task {
        int low;
	int high;
};

struct Stack {
	struct Task *data;
	int top;
	int cap;
};


void InitStack (int n, struct Stack *st)
{
	st->data = malloc(sizeof (struct Task)*n);
	st->top = 0; 
	st->cap = n;
	
};

void Push (struct Task x, struct Stack *st)
{
        //if (st->top++ > st->cap) printf ("Overflow");
	st->data[st->top] = x;
        st->top++;
}

struct Task Pop (int n, struct Stack *st)
{
        //if (st->top == 0) printf("Underflow");
        st->top--;
        return st->data[st->top];
	
}
	

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

void QuickSortOnStack (int k)
{
	int q;
	struct Stack arr;
	struct Task n;
	struct Task m;
	//struct Task end;
	
	InitStack (k*k, &arr);
	n.low = 0;
	n.high = k-1;
	Push (n, &arr);
	while (arr.top != 0){
		n = Pop (k, &arr);
		if (n.low < n.high){
			q = Partition( n.low, n.high, swap);
			m.low = n.low;
			m.high = q-1;
			Push (m, &arr);
			m.low = q+1;
			m.high = n.high;
			Push (m, &arr);
		}
	}
	free(arr.data);
}
	

int main ()
{
	int i = 0, k;
	scanf ("%d", &k);
	array = malloc(sizeof(int)*k);
	for (i; i < k; i++) scanf("%d", array+i);
	QuickSortOnStack (k);
	for (i = 0; i < k; i++) printf("%d ", array[i]);
	free(array);
	//free(Stack.data);
	return 0;
} 
	