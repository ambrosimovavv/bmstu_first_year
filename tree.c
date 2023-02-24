#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

struct Tree{
    int k, count;
    char *v;
    struct Tree *left, *right, *parent;
};

struct Tree* Descend(struct Tree *t, int k) 
{
    struct Tree *x;
    x=t;
    while (x != 0&&x->k != k)
    {
        if (k < x->k)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

struct Tree* Insert(struct Tree *t, int k, char* o, int len) 
{
    struct Tree *x, *y, *buf;
    char *w;
    int i;
    y = malloc(sizeof(struct Tree));
    w = malloc(sizeof(char)*(len+1));
    for (i = 0; i < len; i++)
    {
        w[i] = o[i];
        w[i+1] = 0;
    }
    y->k = k;
    y->v = w;
    y->parent = NULL;
    y->left = NULL;
    y->right = NULL;
    y->count = 1;
    if (t == NULL)
        t = y;
    else 
    {
        x = t;
        while(0==0)
        {
            if (x->k == k)
                return 0;
            if (k<x->k)
            {
                if (x->left == NULL)
                {
                    x->left = y;
                    y->parent = x;
                    buf = y;

                    while (buf!=t)
                    {
                        buf->parent->count++;
                        buf = buf->parent;
                    }
                    break;
                }
                x = x->left;
            }
            else
            {
                if (x->right == NULL)
                {
                    x->right = y;
                    y->parent = x;
                    buf = y;
                    while (buf != t)
                    {
                        buf->parent->count++;
                        buf = buf->parent;
                    }
                    break;
                }
                x = x->right;
            }
        }
    }
    return t;
}

void Lookup(struct Tree *t, int k) 
{
    struct Tree *x;
    x = Descend(t, k);
    printf("%s \n", x->v);
}

void Search(struct Tree *t, int rank) 
{
    struct Tree *buf = t;
    int x;
    char *v;
    x = 0;
    while(0 == 0)
        if (buf->left == NULL)
        {
            if (rank == x)
                break;
            else
            {
                x += 1;
                buf = buf->right;
            }
        }
        else 
        {
            if (buf->left->count+x == rank)
                break;
            else 
            {
                if (buf->left->count+x > rank)
                    buf = buf->left;
                else 
                {
                    x += buf->left->count+1;
                    buf = buf->right;
                }
            }
        }

    v = buf->v;
    printf("%s\n", buf->v);
}
void SuperFree (struct Tree *t)
{
    if (t != NULL)
    {
        SuperFree(t->left);
        SuperFree(t->right);
        free(t->v);
        free(t);
    }
}
struct Tree* replace (struct Tree *t, struct Tree *x, struct Tree *y)
{
    struct Tree *p;
        if (x == t)
        {
            t = y;
            if (y != NULL)
                t->parent = NULL;
        }
        else 
        {
            p = x->parent;
            if (y!=NULL)
                y->parent = p;
            if (p->left == x)
                p->left = y;
            else
                p->right = y;
        }
    return t;

}
struct Tree* Min(struct Tree *t)
{
    struct Tree *x;
    if (t == NULL)
        x = NULL;
    else
    {
        x = t;
        while (x->left != NULL)
            x = x->left;
    }
    return x;

}

struct Tree* Succ(struct Tree *x)
{
    struct Tree *y;

    if (x->right != NULL)
        y = Min(x->right);
    else
    {
        y = x->parent;
        while (y != NULL && x == y->right)
        {
            x = y;
            y = y->parent;
        }
    }
    return y;
}
struct Tree* Del (struct Tree *t, int k)
{
    struct Tree *x, *y, *buf;
    x = Descend(t,k);
    if (x == NULL)
        return t;
    if (x->count == 1)
    {
        buf = x;
        t = replace(t,x,NULL);
        if (t != NULL)
            while (buf != NULL&&buf->parent != NULL)
            {
                buf->parent->count--;
                buf = buf->parent;
            }

    }
    else 
    {
        if (x->left == NULL)
        {
            buf = x;
            t = replace(t, x, x->right);
            while (buf != NULL && buf->parent != NULL)
            {
                buf->parent->count--;
                buf = buf->parent;
            }
        }
        else 
        {
            if (x->right == NULL)
            {
                buf = x;
                t = replace(t, x, x->left);
                while (buf != NULL && buf->parent != NULL)
                {
                    buf->parent->count--;
                    buf = buf->parent;
                }
            }
            else
            {
                y = Succ(x);
                buf = y;
                while (buf != NULL && buf->parent != NULL)
                {
                    buf->parent->count--;
                    buf = buf->parent;
                }
                y->count = x->count;
                t = replace(t, y, y->right);
                x->left->parent = y;
                y->left = x->left;
                if (x->right != NULL)
                    x->right->parent = y;
                y->right = x->right;
                t = replace(t, x, y);
            }
        }
    }
    free(x->v);
    free (x);
    return t;
}

int main()
{
    struct Tree *tr = NULL;
    int n;
    int i;
    int x;
    char *s;
    char *e;
    char c[40];

    scanf("%d\n", &n);
    s = malloc(40*sizeof(char*));
    for (i = 0; i < n; i++)
    {
        gets(s);
        if (s[0]== 'I')
            {
                x = strtol(s+7, &e, 10);
                strncpy(c, e+1, 10);
                tr = Insert(tr, x, c, strlen(c));
            }
         if (s[0]== 'S')
            {
                x = strtol(s+7, &e, 10);
                Search(tr, x);
            }
         if (s[0]== 'L')
            {
                x = strtol(s+7, &e, 10);
                Lookup(tr, x);
            }
         if (s[0]== 'D')
            {
                x = strtol(s+7, &e, 10);
                tr = Del(tr, x);
            } 
    }
    SuperFree(tr);
    free(s);
    return 0;
}
