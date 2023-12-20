#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define N 3

int compare(const void *a, const void *b) {return *(int *)a - *(int *)b;}
int main()
{
    int *tab = malloc(sizeof(int)*N);
    for(int i=0;i<N;i++) scanf("%d", tab+i);
    qsort(tab,N,sizeof(int),compare);
    for(int i=0;i<N;i++) printf("%d ", *(tab+i));
    return 0;
}
