#include <stdio.h>
#include <stdlib.h>

struct elem{
        int k;
	int *v;
	int index;
};

struct queue{
	struct elem *heap;
	int cap;
	int count;
};

struct queue PQueue (int n)
{
	struct queue q;
	q.cap = n;
	q.heap = malloc (sizeof(struct elem)*n);
	q.count = 0;
	return q;
}

struct elem Min (struct queue *q)
{
	struct elem ptr;

	if (q->count == 0)
		printf ("error\n");
	ptr = q->heap[0];
	return ptr;
}

int QEmpty (struct queue *q)
{
	return q->count == 0;
}

void Insert (struct queue *q, struct elem ptr)
{
	struct elem swap;
	int i;

	i = q->count;
	if (i == q->cap)
		printf ("error\n");
	q->count = i+1;
	//printf ("{%d}", q->count);
	q->heap[i] = ptr;

	while (i > 0 && q->heap[(i-1)/2].v[q->heap[(i-1)/2].k] > q->heap[i].v[q->heap[i].k])
	{
		//printf("%d <-> %d", i, (i-1)/2);
		swap = q->heap[i];
		q->heap[i] = q->heap[(i-1)/2];
		q->heap[(i-1)/2] = swap;
		q->heap[i].index = i;
		i = (i-1)/2;
	}
	//printf ("-%d\n", q->heap[0].v[0]);
	q->heap[i].index = i;

}

void heapify(int a, int b, struct elem *P)
{
     int l;
     int r;
     int j;
     struct elem x;

     while (0 == 0)
     {
	     l = 2*a + 1;
	     r = l + 1;
	     j = a;
	     
	     if(l < b && P[a].v[P[a].k] > P[l].v[P[l].k])
	          a = l;
	          
	     if(r < b && P[a].v[P[a].k] > P[r].v[P[r].k])
	          a = r;
	          
	     if (a == j)
	          break;
	     
	     x = P[a];
	     P[a] = P[j];
	     P[j] = x;
	     P[a].index = a;
	     P[j].index = j;
     }
}

struct elem ExtractMin (struct queue *q)
{
	struct elem ptr;
	//printf ("[%d]", q->count);

	if (q->count == 0)
		printf ("error\n");

	ptr = q->heap[0];
	q->count--;
	//printf ("(%d)", q->count);

	if (q->count > 0)
	{
		q->heap[0] = q->heap[q->count];
		q->heap[0].index = 0;
		heapify (0, q->count, q->heap);
	}
	//printf ("%d\n", ptr.k);
	return ptr;
}


void IncKey (struct queue *q, struct elem ptr, int k1)
{
	int i;
	struct elem swap;

	i = ptr.index;
	ptr.k = k1;

	while (i > 0 && q->heap[(i-1)/2].k > k1)
	{
		q->heap[(i-1)/2] = swap;
		swap = q->heap[i];
		q->heap[i] = q->heap[(i-1)/2];
		q->heap[i].index = i;
		i = (i-1)/2;
	}

	ptr.index = i;
}

int main ()
{
	int sum41 = 0;
	int z;
	int key;
	int i;
	int j;
	int *N;
	int **M;
	struct elem *elem1;
	struct queue q;
	struct elem a;

	scanf ("%d", &key);
	N = malloc (sizeof(int)*key);
	M = malloc (sizeof (int*)*key);
	elem1 = malloc (sizeof (struct elem)*key);

	for (i = 0; i < key; i++)
	{
		scanf ("%d", &N[i]);
		sum41 += N[i];
	}

	for (i = 0; i < key; i++)
	{
		M[i] = malloc (sizeof(int)*(N[i]+1));
		for (j = 0; j < N[i]; j++)
			scanf ("%d", &M[i][j]);
		if (N[i] != 0)
			M[i][N[i]] = M[i][N[i]-1]-1;
	}

	q = PQueue (key);

	for (i = 0; i < key; i++)
	{
		elem1[i].v = M[i];
		elem1[i].k = 0;
		//printf("(%d)", elem1[i].k);
		if (N[i] != 0)
			Insert (&q, elem1[i]);
	}

	for (i = 0; i < sum41; i++)
	{
		a = ExtractMin (&q);
		printf ("%d ", a.v[a.k]);
		if (a.v[a.k+1] >= a.v[a.k])
		{
			a.k++;
			Insert (&q, a);
		}
	}
	printf("\n");
	free(elem1);
	for (i = 0; i < key; i++)
		free(M[i]);
	free(M);
	free(N);
	free(q.heap);
	return 0;
}
