#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows, cols, nnz;
    int *rowPtr; // size rows+1
    int *colInd; // size nnz
    int *val;    // size nnz
} CSR;

typedef struct {
    int nnz;
    int *r, *c, *v; // ьзlь form
} Triplet;

Triplet dense_to_triplet(int **A, int rows, int cols) {
    int count = 0;
    for (int i=0;i<rows;i++)
        for (int j=0;j<cols;j++)
            if (A[i][j]!=0) count++;

    Triplet T;
    T.nnz = count;
    T.r = (int*)malloc(sizeof(int)*count);
    T.c = (int*)malloc(sizeof(int)*count);
    T.v = (int*)malloc(sizeof(int)*count);

    int k=0;
    for (int i=0;i<rows;i++)
        for (int j=0;j<cols;j++)
            if (A[i][j]!=0) {
                T.r[k]=i; T.c[k]=j; T.v[k]=A[i][j]; k++;
            }
    return T;
}

CSR triplet_to_csr(Triplet T, int rows, int cols) {
    CSR S;
    S.rows = rows; S.cols = cols; S.nnz = T.nnz;
    S.rowPtr = (int*)calloc(rows+1, sizeof(int));
    S.colInd = (int*)malloc(sizeof(int)*T.nnz);
    S.val    = (int*)malloc(sizeof(int)*T.nnz);

    // count per row
    for (int k=0;k<T.nnz;k++) S.rowPtr[T.r[k]+1]++;

    // prefix sum
    for (int i=0;i<rows;i++) S.rowPtr[i+1]+=S.rowPtr[i];

    int *counter = (int*)malloc(sizeof(int)*rows);
    for (int i=0;i<rows;i++) counter[i]=S.rowPtr[i];

    for (int k=0;k<T.nnz;k++) {
        int r = T.r[k];
        int idx = counter[r]++;
        S.colInd[idx] = T.c[k];
        S.val[idx]    = T.v[k];
    }
    free(counter);
    return S;
}

int main() {
    int rows=3, cols=4;
    int **A = (int**)malloc(rows*sizeof(int*));
    for (int i=0;i<rows;i++){
        A[i]=(int*)calloc(cols,sizeof(int));
    }
    A[0][1]=5; A[1][2]=8; A[2][0]=3; A[2][3]=7;

    Triplet T = dense_to_triplet(A, rows, cols);
    CSR S = triplet_to_csr(T, rows, cols);

    printf("CSR rowPtr: ");
    for (int i=0;i<=rows;i++) printf("%d ", S.rowPtr[i]);
    printf("\nCSR colInd: ");
    for (int i=0;i<S.nnz;i++) printf("%d ", S.colInd[i]);
    printf("\nCSR val:    ");
    for (int i=0;i<S.nnz;i++) printf("%d ", S.val[i]);
    printf("\n");

    // cleanup
    for (int i=0;i<rows;i++) free(A[i]); free(A);
    free(T.r); free(T.c); free(T.v);
    free(S.rowPtr); free(S.colInd); free(S.val);
    return 0;
}
