#include <stdio.h>
#include <stdlib.h>

struct Elem { 
        struct Elem *prev, *next; 
	int v; 
} *elsp;

void InitDoubleLinkedList ()
{
	elsp = (struct Elem *)malloc(sizeof(struct Elem));
	elsp->prev = elsp;
	elsp->next = elsp;
}


void InsertBefore (struct Elem *a, struct Elem *b)
{	
	struct Elem *c = a->prev;
	a->prev = b;
	b->next = a;
	b->prev = c; 
	c->next = b;
}


int compare (struct Elem *a, struct Elem *b)
{
	//struct Elem *b = elsp->next;
	if (a->v >= b->v) return 1;
                else 	return 0;
}

void InsertSort (struct Elem *a)
{
	int res;
	struct Elem *b = elsp->next;
	//printf("ins %d %d\n", a->v, b->v);
	while (b != elsp){
		res = compare(a, b);
		if (res == 1) b = b->next;
		else break;
	}
	InsertBefore(b, a);
}

int main ()
{
	int n, i, el_v;
	scanf("%d", &n);
	InitDoubleLinkedList ();
	for (i = 0; i < n; i++){
		scanf("%d", &el_v);
		struct Elem *a = (struct Elem *)malloc(sizeof(struct Elem));
		a->v = el_v;
		//printf("%d ", a->v);
		InsertSort (a);
	}
	struct Elem *a = elsp->next;
	while (n > 0){
		printf("%d ", a->v);
		a = a->next;
		n--;
		struct Elem *x = a->prev, *b = x->prev, *c = x->next;
		b->next = c;
		c->prev = b;
		x->prev = 0;
		x->next = 0;
		free(x);
	} 
	free(elsp);
	return 0;
}
