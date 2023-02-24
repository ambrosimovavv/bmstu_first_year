
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem { 
        struct Elem *next; 
        char *word; 
} *list, *tail;

int Key (char *word)
{
        int len = 0;
        for (; word[len] != ' ' && word[len]; len++);
        //printf("%d %c\n", len, word[0]);
        return len;
}

void InitSingleLinkedList ()
{
        list = (struct Elem *)malloc(sizeof(struct Elem));
        list->next = list;
	tail = list;
}

int ListLength ()
{
	int len = 0;
	struct Elem *x = list;
	while ((x->next) != list) {
		len++;
		x = x->next;
	}
	return len;
}

void InsertAfter (struct Elem *x, struct Elem *y)
{	
	struct Elem *z = x->next;
	x->next = y;
	y->next = z;
	tail = y;
}

void swap (struct Elem *x, struct Elem *y)
{
	char *word = x->word;
	x->word = y->word;
	y->word = word;
//	printf("! %c %c\n", (y->word)[0], (x->word)[0]);
}

void BoubleSort ()
{
	struct Elem *y;
	int t = ListLength () - 1, bound, i;
	while (t > 0) {
		y = list->next;
		bound = t;
		t = 0;
		i = 0;
		while (i < bound) {
			if (Key((y->next)->word) < Key(y->word)) {
				swap (y, y->next);
				t = i;
			}
			i++;
			y = y->next;
		}
		//printf("!!\n");
	}
}

void Insert (char *word)
{
	struct Elem *x = (struct Elem *)malloc(sizeof(struct Elem));
	x->word = word;
	InsertAfter (tail, x);
}


void wins(char *s) 
{ 
        unsigned long i = 1;
        if (s[0] && (s[0] != ' ')) Insert (s);
        while (s[i] && s[i + 1]) {
                if ((s[i] == ' ') && (s[i + 1] != ' ')) Insert (s + i + 1);
                i++;
        }
}

void Print (char *word)
{
        int len = Key (word), i = 0;
        for (; i < len; i++) printf("%c", word[i]);
        printf(" ");
}


void Delete (struct Elem *y)
{
        struct Elem *x = y->next;
        y->next = x->next;
        x->next = NULL;
        free (x);
}

void print ()
{
        int len = ListLength (), i = 0;
        char *word;
        struct Elem *x = list->next;
        for (; i < len; i++) {
                Print(x->word);
                x = x->next;
                Delete (list);
        }
}

int main()
{
        char s[1000000];
	InitSingleLinkedList ();
        gets (s);
        wins (s);
	BoubleSort ();
        print();
	//printf("%s\n", s);
        free(list);
	return 0;
} 
