#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_of_word;
//cr string[100000];
struct Elem {
        struct Elem *next;
	char *word;
} *sinlinlst, *cdrlist;

void InitSingleLinkedList ()
{
	sinlinlst = (struct Elem *)malloc(sizeof(struct Elem));
	sinlinlst->next = sinlinlst;
	cdrlist = sinlinlst;
}
void Insert (char *w)
{
        struct Elem *x = (struct Elem *)malloc(sizeof(struct Elem));
	x->word = w;
	struct Elem *a = cdrlist->next;
	cdrlist->next = x;
	x->next = a;
	cdrlist = x;
}


int MakeStruct (char *s)
{
	int in_word = 0, count_of_word = 0, i = 0;
	while (1){
		if (s[i] == '\0') break;
		if (s[i] == ' '){
			if (in_word == 0) i++;
			else {
				in_word = 0;
				i++;
			}
		}else if (in_word == 0){
			Insert(s + i);
			count_of_word++;
			in_word = 1;
			i++;
		}else i++;
	}
        return count_of_word;
}

int lenght(char *w)
{
	int l = 0;
	while (1){
		if ((w[l] != ' ') && (w[l])) l++;
		else break;
	}
	return l;
}

void BoubleSort ()
{
	struct Elem *y;
	int n = count_of_word - 1, b, i, len1, len2;
	char *w;
	while (n > 0) {
		y = sinlinlst->next;
		b = n;
		n = 0;
		i = 0;
		while (i < b) {
                        len1 = lenght((y->next)->word);
                        len2 = lenght(y->word);
			if (len1 < len2) {
				w = y->word;
				y->word = (y->next)->word;
				(y->next)->word = w;
				n = i;
			}
			i++;
			y = y->next;
		}
	}
}
void Delete (struct Elem *a)
{
        struct Elem *b = a->next;
        a->next = b->next;
        b->next = 0;
        free (b);
}
int main ()
{
        char string[100000];
	int n, l, i;
	char *w;
	InitSingleLinkedList();
	gets(string);
	n = MakeStruct(string);
	BoubleSort();
	struct Elem *a = sinlinlst->next;
	while (n > 0){
                w = a->word;
		l = lenght(w);
		n--;
		i = 0;
		while(l > 0){
			printf ("%c", w[i]);
			i++; 
			l--;
		}
		printf(" ");
                //struct Elem *g = sinlinlst;
                Delete(sinlinlst);
	}
	free(sinlinlst);
	return 0;
}