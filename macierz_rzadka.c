#include <stdio.h>
#include <stdlib.h>

#define SIZE_MAX 30

typedef struct tagTuple {
    size_t row;
    size_t column;
    double value;
} Tuple;

int cmp_row_col(const void *p1, const void *p2)
{
    Tuple *item1 = (Tuple *)p1;
    Tuple *item2 = (Tuple *)p2;

    if (item1->row < item2->row) return -1;
    if (item1->row > item2->row) return 1;
    if (item1->column < item2->column) return -1;
    if (item1->column > item2->column) return 1;
    return 0;

}

int cmp_col_row(const void *p1, const void *p2)
{
    Tuple *item1 = (Tuple *)p1;
    Tuple *item2 = (Tuple *)p2;

    if (item1->column < item2->column) return -1;
    if (item1->column > item2->column) return 1;
    if (item1->row < item2->row) return -1;
    if (item1->row > item2->row) return 1;
    return 0;

}

void print_sparse_matrix(size_t rows, size_t cols, Tuple ts[])
{
    Tuple *wsk = ts;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(i==ts->row && j==ts->column)
            {
                printf(" %0.1f ",ts->value);
                ts++;
            }
            else printf(" 0.0 ");

        }
        printf("\n");
    }
}

void convert_to_sparse(size_t rows, size_t cols, double t2D[][cols], Tuple tsp[], int *n)
{
    int licznik=0;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(t2D[i][j]!=0)
            {
                Tuple new_item;
                new_item.row = i;
                new_item.column = j;
                new_item.value=t2D[i][j];
                tsp[licznik] =new_item;
                licznik++;
            }
        }
    }
    *n = licznik;
}

void multiply(size_t n1, Tuple t1[], size_t n2, Tuple t2[], Tuple t3[], int *n)
{
    int licznik = 0; // Initialize the count of elements in the result matrix to 0

    // Multiply the matrices
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (t1[i].column == t2[j].row)
            {
                Tuple new_item;
                new_item.row = t1[i].row;
                new_item.column = t2[j].column;
                new_item.value = 0;

                // Find matching elements and accumulate the result
                for (int k = 0; k < n1; k++)
                {
                    if (t1[k].column == t1[i].column && t2[k].row == t2[j].row)
                    {
                        new_item.value += t1[k].value * t2[k].value;
                    }
                }

                // Add the result to the output matrix
                t3[licznik] = new_item;
                licznik++;
            }
        }
    }
    *n=licznik;
}

int main(void) {
    double t2D1[4][5]={1,2,3,4,5,6,7,8};
    double t2D2[5][6]={{1,2},{1,5},{0,1},{0,0,2},{3,4}};
    Tuple t_sparse1[SIZE_MAX], t_sparse2[SIZE_MAX], t_sparse3[SIZE_MAX];
    size_t n1, n2, n3;

    convert_to_sparse(4, 5, t2D1, t_sparse1,&n1);
    convert_to_sparse(5, 6, t2D2, t_sparse2,&n2);
    qsort(t_sparse1,n1,sizeof(Tuple),cmp_row_col);
    qsort(t_sparse2,n2,sizeof(Tuple),cmp_col_row);
    multiply(n1,t_sparse1,n2,t_sparse2,t_sparse3,&n3);
    qsort(t_sparse3,n3,sizeof(Tuple),cmp_row_col);
    print_sparse_matrix(4, 6, t_sparse3);

    return 0;
}
