#include <stdio.h>

#define CAP 15
// Komple binary aðaç dizi temsili: parent i, left 2*i+1, right 2*i+2

void set_root(int tree[], int val){ tree[0]=val; }
void set_left(int tree[], int parentIndex, int val){
    int li=2*parentIndex+1; tree[li]=val;
}
void set_right(int tree[], int parentIndex, int val){
    int ri=2*parentIndex+2; tree[ri]=val;
}

void preorder(int tree[], int i){
    if (i>=CAP || tree[i]==-1) return;
    printf("%d ", tree[i]);
    preorder(tree, 2*i+1);
    preorder(tree, 2*i+2);
}
void inorder(int tree[], int i){
    if (i>=CAP || tree[i]==-1) return;
    inorder(tree, 2*i+1);
    printf("%d ", tree[i]);
    inorder(tree, 2*i+2);
}
void postorder(int tree[], int i){
    if (i>=CAP || tree[i]==-1) return;
    postorder(tree, 2*i+1);
    postorder(tree, 2*i+2);
    printf("%d ", tree[i]);
}

int main(){
    int tree[CAP]; for (int i=0;i<CAP;i++) tree[i]=-1;
    set_root(tree, 10);
    set_left(tree, 0, 5);
    set_right(tree, 0, 15);
    set_left(tree, 1, 3);
    set_right(tree, 1, 7);
    set_left(tree, 2, 12);
    set_right(tree, 2, 18);

    printf("Preorder: "); preorder(tree,0); printf("\n");
    printf("Inorder:  "); inorder(tree,0);  printf("\n");
    printf("Postorder:"); postorder(tree,0); printf("\n");
    return 0;
}
