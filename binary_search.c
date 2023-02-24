
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
struct top {
        int k, count;
        struct top *parent, *left, *right;
	char v[10];
} *t;
     
void  InitBinarySearchTree ()
{
	t = NULL;
}

void Insert (int k, char *s)
{
	struct top *x = t, *y = (struct top*)malloc(sizeof(struct top));
	y -> k = k;
	strcpy(y -> v, s);
	y -> count = 1;
	y -> parent = y -> left = y -> right = NULL;
	if (t == NULL) t = y;
	else for (; ; ) {
		if (x -> k > k) {
			if (x -> left == NULL) {
				x -> left = y;
				y -> parent = x;
				x -> count++;
				break;
			}
			x = x -> left;
		} else {
			if (x -> right == NULL) {
				x -> right = y;
				y -> parent = x;
				x -> count++;
				break;
			}
			x = x -> right;
		}
		(x -> parent) -> count++;
	}
}
     
char *Search (int i) 
{
	int n = i + 1;
	struct top *x = t;
	for ( ; ; ) {
		if (x -> left != NULL) {
			if (n - 1== (x -> left) -> count) {
				return x -> v;
				break;
			} else if ((x -> left) -> count >= n) x = x -> left;
			else {
				n -= (x -> left) -> count + 1;
				x = x -> right;
			}
		} else {
			if (n == 1) {
				return x -> v;
				break;
			} else {
				x = x -> right;
				n--;
			}
		}
	}
}
     
struct top *Descend (int k)
{
	struct top *x = t;
	while ((x != NULL) && (x -> k != k)) {
		if (k < x -> k) x = x -> left;
		else x = x -> right;
	}
	return x;
}

struct top *Minimum (struct top *x)
{
	if (x == NULL) return NULL;
	else {
                struct top *y = x;
		while (y -> left != NULL)
		y = y -> left;
	}
	return y;
}
     
struct top *Succ (struct top *x)
{
	struct top *y;
	if (x -> right != NULL) y = Minimum (x -> right);
	else {
		y = x -> parent;
		while ((y != NULL) && (x == y -> right)) {
			x = y;
			y = y -> parent;
		}
	}
	return y;
}
          
void DecreaseCount(struct top *x)
{
	while (x != t) {
		x = x -> parent;
		x -> count--;
	}
}
     
void ReplaceNode(struct top *x, struct top *y)
{
	struct top *z = x -> parent;
	if (x == t) t = y;
	else {
		if (y != NULL) y -> parent = z;
		if (z -> left == x) z -> left = y;
		else z -> right = y;
	  }
}
     
void DeleteTop (int k) 
{
	struct top *x = Descend (k), *y;
	if ((x -> right == NULL) && (x -> left == NULL)) {
		DecreaseCount (x);
		ReplaceNode (x, NULL);
	} else if (x -> left == NULL) {
		DecreaseCount (x);
		ReplaceNode (x, x -> right);
	} else if (x -> right == NULL) {
		DecreaseCount (x);
		ReplaceNode (x, x -> left);
	} else { 
		y = Succ (x);
		DecreaseCount (y);
		ReplaceNode (y, y -> right);
		(x -> left) -> parent = y;
		y -> left = x -> left;
		if (x -> right != NULL) (x -> right) -> parent = y;
		y -> right = x -> right;
		y -> count = x -> count;
		ReplaceNode (x, y);
	}
	free(x);
}
          
char *Lookup (int k) 
{
	return (Descend (k)) -> v;
}

void DeleteTree (struct top *x)
{
	if (x != NULL) {
		if (x -> left != NULL) DeleteTree (x -> left);
		if (x -> right != NULL) DeleteTree (x -> right);
		free(x);
	}
}
     
int main ()
{
	int i, n, arg, k, x;
	InitBinarySearchTree ();
	scanf("%d", &n);
	char s[7], v[10];
	for (i = 0; i < n; i++) {
		scanf("%s", s);
		switch (s[0]) {
			case ('I') : scanf ("%d %s", &k, v);
				Insert (k, v);
				continue;
			case ('S') : scanf ("%d", &x);
				printf ("%s\n", Search (x));
				continue;
			case ('D') : scanf ("%d", &k);
				DeleteTop (k);
				continue;
			case ('L') : scanf ("%d", &k);
				printf ("%s\n", Lookup (k));
				continue;
		}
	}
	DeleteTree (t);
	return 0;
}
