#include <stdio.h>
#include <stdlib.h>

typedef struct { int *a; int size; int cap; int isMax; } Heap;

Heap makeHeap(int cap, int isMax){
    Heap h; h.a=(int*)malloc(sizeof(int)*cap); h.size=0; h.cap=cap; h.isMax=isMax; return h;
}
int cmp(Heap* h, int x, int y){ return h->isMax ? (x>y) : (x<y); }
void swap(int *x,int *y){ int t=*x; *x=*y; *y=t; }

void heapify_up(Heap* h, int i){
    while (i>0){
        int p=(i-1)/2;
        if (cmp(h,h->a[i],h->a[p])) { swap(&h->a[i],&h->a[p]); i=p; }
        else break;
    }
}
void heapify_down(Heap* h, int i){
    while (1){
        int l=2*i+1, r=2*i+2, best=i;
        if (l<h->size && cmp(h,h->a[l],h->a[best])) best=l;
        if (r<h->size && cmp(h,h->a[r],h->a[best])) best=r;
        if (best!=i){ swap(&h->a[i],&h->a[best]); i=best; } else break;
    }
}
void insert(Heap* h, int val){
    if (h->size==h->cap) return;
    h->a[h->size]=val; heapify_up(h, h->size); h->size++;
}
int extract_top(Heap* h){
    if (h->size==0) return -1;
    int top=h->a[0]; h->a[0]=h->a[h->size-1]; h->size--; heapify_down(h,0); return top;
}

int main(){
    Heap maxH = makeHeap(20, 1);
    Heap minH = makeHeap(20, 0);
    int arr[] = {10,4,7,20,3,15};
    for (int i=0;i<6;i++){ insert(&maxH, arr[i]); insert(&minH, arr[i]); }

    printf("MaxHeap extract: ");
    while (maxH.size) printf("%d ", extract_top(&maxH));
    printf("\nMinHeap extract: ");
    while (minH.size) printf("%d ", extract_top(&minH));
    printf("\n");
    free(maxH.a); free(minH.a);
    return 0;
}
