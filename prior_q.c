#include <stdio.h>
#include <stdlib.h>

struct el {
    int i, v;
} *queue;
        
int k = 0;

void InitPriorityQueue ()
{
        queue = (struct el *)malloc(k*sizeof(struct el));
}

void Swap (int a, int b)
{
        struct el t;
        t = queue[a];
        queue[a] = queue[b];
        queue[b] = t;
}

int max (int a, int b)
{
	return (a > b) ? a : b;
}

void heapify (int k, int i) 
{
        int l = 2*i, r = 2*i + 1, m = 0, count = 0;
        if (l < k && queue[l].v < queue[i].v) {
                m = l;
        	count++;
        }
	if (!count) m = i;
        if (r < k && queue[r].v < queue[m].v)  m = r;
        if (!(m == i)) {
                Swap(i, m);
                heapify (k, m);
        }
}

void BuildHeap () 
{
	int i = k/2;
        for ( ; i > -2; i--) heapify (k, i + 1);
}

void ScanAndPrint ()
{
	int i = 0, j = 0, m = 0, N = 0;
	int n [k], B [k];
	InitPriorityQueue ();
        for (i = 0; i < k; i++) {
                scanf("%d", n + i);
		m = max (n[i], m);
		N += n[i];
	}
        int matrix [k][m + 1];
        for (i = 0; i < k; i++) {
                for (j = 0; j < n[i]; j++) {
                        scanf("%d", &(matrix [i][j]));
                }
                matrix [i][j] = 33554432;
                queue [i].v = matrix [i][0];
                queue [i].i = i;
		B [i] = 0;
        }
        BuildHeap ();
        for (i = 0; i < N; i++) {
                printf("%d ", queue [0].v);
                B [queue [0].i]++;
                queue [0].v = matrix [queue [0].i][B [queue[0].i]];
                heapify (k, 0);
        }
}

int main ()
{
        scanf("%d", &k);
        ScanAndPrint ();
        free (queue);
        return 0;
}