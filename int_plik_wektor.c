#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
typedef int (*cmp_data_fp)( void*,  void*);
typedef void (*dmp_data_fp)( void*);


typedef struct tagVector {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
    double av;
    cmp_data_fp cmp_data;
    dmp_data_fp dmp_data;
} Vector;

// Fukcje "uniwersalne":


void init_vector(Vector *v, size_t cap, size_t el_size)
{
    v->size=0;
    v->element_size=el_size;
    v->capacity=cap;
    v->data=malloc(v->capacity* v->element_size);
    v->av=0.0;
}

void clear(Vector* vector) {
    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;
}
void clear_vector(Vector* vector) {
    for (size_t i = 0; i < vector->size; ++i) {
        void* address = (char*)vector->data + i*vector->element_size;
        clear(address);
    }
}
void reserve(Vector* vector, size_t new_cap) {
    if (new_cap > vector->capacity) {

        vector->data = realloc(vector->data, new_cap * vector->element_size);
        vector->capacity = new_cap;
    }
}


void push_back(Vector* vector, void* val) {

    if (vector->size == vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        reserve(vector, new_cap);
    }

    char* dest = (char*)vector->data + (vector->size * vector->element_size);
    memcpy(dest, &val, vector->element_size);
    vector->size++;
}

void insert_sorted(Vector* vector, void* val) {
    if (vector->size == vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        reserve(vector, new_cap);
    }

    char* dest = (char*)vector->data;
    size_t i = 0;

    while (i < vector->size && vector->cmp_data(dest + i * vector->element_size, val) < 0) {
        i++;
    }

    memmove(dest + (i + 1) * vector->element_size, dest + i * vector->element_size, (vector->size - i) * vector->element_size);
    memcpy(dest + i * vector->element_size, &val, vector->element_size);

    vector->size++;
}


void dump_data(Vector* vector) {
    if (vector->size == 0) {
        printf("Vector is empty.\n");
        return;
    }


    for (size_t i = 0; i < vector->size; ++i) {
        void* address = (char*)vector->data + i*vector->element_size;
        vector->dmp_data(address);
    }

}



void resize_vector(Vector* vector) {

    if (vector->size == 0) clear(vector);
    else {
        void* new_data = realloc(vector->data, vector->size * vector->element_size);
        vector->data = new_data;
        vector->capacity = vector->size;
    }
}

void print_double(void *address)
{
    printf(" %0.3f ",**((double **)address));
}

int cmp_double(void *a, void *adr)
{
    if(**((double **)a) > *((double *)adr)) return 1;
    else if(**((double **)a) < *((double *)adr)) return -1;
    else return 0;
}

int cmp_vector_double(void *a, void *adr)
{
    if((*(Vector **)a)->av > ((Vector *)adr)->av) return 1;
    else if((*(Vector **)a)->av < ((Vector *)adr)->av) return -1;
    else return 0;
}
void print_vector_double(void *address)
{
    print_double((*(Vector **)address)->data);
    print_double((*(Vector **)address)->data + ((*(Vector **)address)->size - 1) *  (*(Vector **)address)->element_size);
    //printf(" %f ", (*((Vector **)address))->av);
    printf("\n");
}

int main(void) {
    double min=999.0,max=-1.0;
    double sum=0.0;
    Vector main_vector;
    init_vector(&main_vector,20,sizeof(Vector*));
    main_vector.dmp_data=print_vector_double;
    main_vector.cmp_data=cmp_vector_double;
    FILE *file = fopen("liczby2.txt","r");
    if (file == NULL) {
        printf("Error");
        return -1;
    }
    char buff[200];
    char *delimiters = " \t\n,";
    printf(" MIN  |  MAX\n");
    while(fgets(buff,200,file)!=0)
    {
        sum=0.0;
        char *token= strtok(buff,delimiters);
        Vector *record_vector = malloc(sizeof(Vector));
        init_vector(record_vector,20,sizeof(double*));
        record_vector->dmp_data=print_double;
        record_vector->cmp_data=cmp_double;
        while (token != NULL)
        {
            double *w = malloc(sizeof(double));
            *w=atof(token);
            if(*w < min) min =*w;
            if(*w > max) max =*w;
            sum+=*w;
            insert_sorted(record_vector,w);
            token = strtok(NULL,delimiters);
        }
        record_vector->av= sum/(double)record_vector->size;
        //printf( "%f ",record_vector->av);
        //dump_data(record_vector);
        //printf("\n");
        insert_sorted(&main_vector,record_vector);

    }
    dump_data(&main_vector);
    clear_vector(&main_vector);
    printf("\nWartosc najwieksza: %0.3f\n", max);
    printf("Wartosc najmniejsza: %0.3f\n", min);
    int end = fclose(file);



}

