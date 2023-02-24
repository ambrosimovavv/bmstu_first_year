#include <stdio.h>

struct elemp {
    int i;
    int x;
};

void heapify(struct elemp* P, int i,int k) {
    int l=2*i;
    int r=2*i+1;
    int largest=i;
    if (l<k && P[l].x<P[i].x) {
        largest=l;
    }
    if (r<k && P[r].x<P[largest].x) {
        largest=r;
    }
    if (largest!=i) {
        struct elemp v=P[i];
        P[i]=P[largest];
        P[largest]=v;
        heapify(P,largest,k);
    }
}

int find(int i,struct elemp* P,int *B,int *len,int n) {
    if (i>=n) {
        return -1;
    }
    if ((B[i]+1)==len[i]) {
        int i1=-1,i2;
        if (i!=0) {
            i1=find(i*2,P,B,len,n);
        }
        i2=find(i*2+1,P,B,len,n);
        if (i1==-1 || i2==-1) {
            if (i1*i2==1) {
                return -1;
            }
            if (i1!=-1) {
                return i1;
            }
            else
                return i2;
        }
        if (P[i1].x<P[i2].x) {
            return i1;
        }
        else
            return i2;
    }
    else
        return i;
}

void build(struct elemp* P, int k) {
    int i;
    for (i=k/2+1;i>=0;i--) {
        heapify(P,i,k);
    }
}


int main(void)
{
    int n=0,k,kol=0;
    scanf("%d",&k);
    int len[k],maxlen=0;
    struct elemp P[k];
    int i,j;
    for (i=0;i<k;i++) {
        scanf("%d",&len[i]);
        if (len[i]>len[maxlen]) {
            maxlen=i;
        }
        n+=len[i];
    }
    maxlen=len[maxlen];
    int A[k][maxlen+1],B[k];
    for (i=0;i<k;i++) {
        for (j=0;j<len[i];j++) {
            scanf("%d",&A[i][j]);
        }
        A[i][j]=2000000001;
        P[i].x=A[i][0];
        P[i].i=i;
        B[i]=0;
    }    
    build(P,k);
    //второй этап
    int v;
    while (kol<n) {
        printf("%d ",P[0].x);
        B[P[0].i]++;
        P[0].x=A[P[0].i][B[P[0].i]];
        heapify(P,0,k);
        kol++;
    }
    for (i=k-1;i>0;i--) {
        struct elemp v=P[0];
        P[0]=P[i];
        P[i]=v;
        heapify(P,i,k-i+1);
    }
    return 0;
}
