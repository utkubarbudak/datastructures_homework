#include <stdio.h>
#include <stdlib.h>

typedef struct Adj {
    int v;
    struct Adj* next;
} Adj;

typedef struct {
    Adj** head;
    int n;
} Graph;

Graph* create_graph(int n){
    Graph* g=(Graph*)malloc(sizeof(Graph));
    g->n=n; g->head=(Adj**)calloc(n,sizeof(Adj*));
    return g;
}
void add_edge(Graph* g, int u, int v){
    Adj* a=(Adj*)malloc(sizeof(Adj)); a->v=v; a->next=g->head[u]; g->head[u]=a;
    Adj* b=(Adj*)malloc(sizeof(Adj)); b->v=u; b->next=g->head[v]; g->head[v]=b; // undirected
}

void dfs_util(Graph* g, int u, int* vis){
    vis[u]=1; printf("%d ", u);
    for (Adj* p=g->head[u]; p; p=p->next) if(!vis[p->v]) dfs_util(g,p->v,vis);
}
void dfs(Graph* g, int start){
    int *vis=(int*)calloc(g->n,sizeof(int));
    dfs_util(g,start,vis);
    free(vis); printf("\n");
}

void bfs(Graph* g, int start){
    int *vis=(int*)calloc(g->n,sizeof(int));
    int *q=(int*)malloc(sizeof(int)*g->n); int f=0,r=0;
    vis[start]=1; q[r++]=start;
    while (f<r){
        int u=q[f++]; printf("%d ", u);
        for (Adj* p=g->head[u]; p; p=p->next){
            if (!vis[p->v]){ vis[p->v]=1; q[r++]=p->v; }
        }
    }
    free(q); free(vis); printf("\n");
}

int main(){
    Graph* g=create_graph(6);
    add_edge(g,0,1); add_edge(g,0,2);
    add_edge(g,1,3); add_edge(g,2,4);
    add_edge(g,4,5);

    printf("DFS from 0: "); dfs(g,0);
    printf("BFS from 0: "); bfs(g,0);

    // free
    for (int i=0;i<g->n;i++){
        Adj* p=g->head[i]; while (p){ Adj* t=p; p=p->next; free(t); }
    }
    free(g->head); free(g);
    return 0;
}
