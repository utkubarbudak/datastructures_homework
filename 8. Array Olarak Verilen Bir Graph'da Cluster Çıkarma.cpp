#include <stdio.h>

#define NMAX 10

void dfs(int n, int G[NMAX][NMAX], int u, int visited[]){
    visited[u]=1;
    for (int v=0; v<n; v++)
        if (G[u][v] && !visited[v]) dfs(n, G, v, visited);
}

int main(){
    int n=7;
    int G[NMAX][NMAX]={0}; // adjacency matrix
    // Component 1: 0-1-2
    G[0][1]=G[1][0]=1; G[1][2]=G[2][1]=1;
    // Component 2: 3-4
    G[3][4]=G[4][3]=1;
    // Component 3: 5-6
    G[5][6]=G[6][5]=1;

    int visited[NMAX]={0};
    int compId[NMAX]; int compCount=0;

    for (int i=0;i<n;i++){
        if (!visited[i]){
            compCount++;
            dfs(n,G,i,visited);
            for (int j=0;j<n;j++) if (visited[j]==1){ compId[j]=compCount; visited[j]=2; }
        }
    }

    for (int i=0;i<n;i++) printf("Node %d -> cluster %d\n", i, compId[i]);
    return 0;
}
