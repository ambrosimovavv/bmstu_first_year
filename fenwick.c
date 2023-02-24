
#include <stdio.h>
#include <stdlib.h>

int min (int a, int b)
{
        if (a < b) return a;
        return b;
}

int f (int n)
{
        int x = 2;
        while (x <= n)  x *= 2;
        return x;
}

int peak (int *arr, int i, int nel)
{
        if ((i < 0) || (i >= nel)) return 0;
        if (i == 0) return (arr[i] >= arr[i + 1]);
        if (i == nel - 1) return (arr[i - 1] <= arr[i]);
        return ((arr[i - 1] <= arr[i]) && (arr[i] >= arr[i + 1]));
}

int query (int *T, int i)
{
        int v = 0;
        while (i >= 0) {
                v = v + T[i];
                i = (i & (i + 1)) - 1;
        }
        return v;
}

int FenwickTree_Query (int *T, int l, int r)
{
        return query (T, r) - query (T, l - 1);
}

void FenwickTree_Update (int i, int d, int *T, int nel)
{
        while (i < nel) {
                T [i] = T [i] + d;
                i = i|(i + 1);
        }
}

int build (int *v, int nel, int l, int r, int *T)
{
        int sum = 0, bound = min (r, nel), m;
        while (l < bound) {
                m = (l + r)/2;
                sum = sum + build (v, nel, l, m, T);
                l = m + 1;
        }
        if (r < nel) {
                sum = sum + v[r];
                T[r] = sum;
        }
        return sum;
}

void FenwickTree_Build (int *v, int *T, int nel)
{
        
        int r = f (nel);
        build (v, nel, 0, r - 1, T);
}

int main()
{
        int nel, i, j, m, a, b, n;
        char s[5];
        scanf("%d", &nel);
        if (nel > 1) {
                int *arr = (int *)malloc(nel*sizeof(int));
                int *v = (int *)malloc(nel*sizeof(int));
                int *T = (int *)malloc(nel*sizeof(int));
                for (i = 0; i < nel; i++) {
                        scanf("%d", arr + i);
                        v[i] = 0;
                        T[i] = 0;
                }
                for (i = 0; i < nel; i++) v[i] = peak (arr, i, nel);
                FenwickTree_Build (v, T, nel);
                scanf("%d", &m);
                for (i = 0; i < m; i++){
                        scanf("%s %d %d", s, &a, &b);
                        if (s[0] == 'U'){
                                arr[a] = b;
        			for (j = -1; j < 2; j++) {
	        			if (a + j >= 0 && a + j < nel && v[a + j] != peak (arr, a + j, nel)) {
		        		      FenwickTree_Update (a + j, peak(arr, a + j, nel) - v[a + j], T, nel);
			        	      v[a + j] = peak (arr, a + j, nel);
				        }
                                }
                        } else printf("%d\n", FenwickTree_Query (T, a, b));
                }
                free(T);
                free(arr);
                free(v);
        } else {
                scanf("%d", &n);
                scanf("%d", &m);
                for (i = 0; i < m; i++){
                        scanf("%s %d %d ", s, &a, &b);
                        if (s[0] == 'U'){
                                n = b;
                        } else printf("1\n");
                }
        }
                
	return 0;
}
