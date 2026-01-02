#include <stdio.h>

void insert_at(int a[], int *n, int cap, int pos, int val){
    if (*n>=cap || pos<0 || pos>*n) return;
    for (int i=*n; i>pos; i--) a[i]=a[i-1];
    a[pos]=val; (*n)++;
}
void delete_at(int a[], int *n, int pos){
    if (pos<0 || pos>=*n) return;
    for (int i=pos; i<*n-1; i++) a[i]=a[i+1];
    (*n)--;
}

int main(){
    int a[10]={1,2,3,4,5}; int n=5;
    insert_at(a,&n,10,2,99); // 1 2 99 3 4 5
    for (int i=0;i<n;i++) printf("%d ", a[i]); printf("\n");
    delete_at(a,&n,3); // remove 3
    for (int i=0;i<n;i++) printf("%d ", a[i]); printf("\n");
    return 0;
}
