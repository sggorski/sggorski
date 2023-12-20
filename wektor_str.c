#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef int (*cmp_data_fp)(const void*, const void*);
typedef void (*print_data_f)(void*);
#define MAX_LEN 5

char *read_string()
{
    char buffor[100];
    scanf("%s",buffor);
    char *p = malloc(sizeof(char)*(strlen(buffor)+1));
    strcpy(p,buffor);
    return p;

}

typedef struct tagVector {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
    cmp_data_fp cmp_data;
    print_data_f dump_it;
} Vector;

// Fukcje "uniwersalne":


void init_vector(Vector *v, size_t cap, size_t el_size)
{
    v->size=0;
    v->element_size= el_size;
    v->capacity=cap;
    v->data=malloc(v->capacity* v->element_size);
}

void clear(Vector* vector) {
    for (size_t i = 0; i < vector->size; ++i) free((char *)vector->data +i*vector->element_size);
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;
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
    memmove(dest, &val, vector->element_size);
    vector->size++;
}

void push_front(Vector* vector, void *val) {
    if (vector->size == vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        reserve(vector, new_cap);
    }
    for (size_t i = vector->size; i > 0; --i) {
        char* dest = (char*)vector->data + i * vector->element_size;
        char* from = (char*)vector->data + (i - 1) * vector->element_size;
        memmove(dest, from, vector->element_size);
    }

    memmove(vector->data, &val, vector->element_size);
    vector->size++;
}
void dump_data(Vector* vector) {
    if (vector->size == 0) {
        printf("Vector is empty.\n");
        return;
    }

    printf("Vector data:\n");

    for (size_t i = 0; i < vector->size; ++i) {
        void* address = (char*)vector->data + i*vector->element_size;
        vector->dump_it(address);
    }
    printf("\n");
}

int search_in_vector(const void *pkey, const Vector V) {
    int res;
    for(int i=0; i<V.size; ++i) {
        res = V.cmp_data(pkey, (char*)V.data+i*V.element_size);
        if(res == 0) return i;
    }
    return -1;
}
void insert(Vector* vector, size_t position, void *val) {
    if (position > vector->size) {
        printf("Zla pozycja\n");
        return;
    }

    if (vector->size == vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        reserve(vector, new_cap);
    }

    for (size_t i = vector->size; i > position; i--) {
            char* dest = (char*)vector->data + i * vector->element_size;
            char* from = (char*)vector->data + (i - 1) * vector->element_size;
            memmove(dest, from, vector->element_size);
        }

        memmove((char*)vector->data + position * vector->element_size, &val, vector->element_size);
        vector->size++;


}
void erase(Vector* vector, size_t position) {
    if (position < vector->size) {

        for (size_t i = position; i < vector->size - 1; ++i) {
            char* dest = (char*)vector->data + i * vector->element_size;
            char* src = (char*)vector->data + (i + 1) * vector->element_size;
            memmove(dest, src, vector->element_size);
        }
        vector->size--;

    }
}
void erase_value(Vector* vector, void *value) {
    size_t i = 0;
    while (i < vector->size) {
        void* address = (char*)vector->data + (i * vector->element_size);
        char * tekst = *(char**)address;

        if (strcmp(tekst,value)==0) {
            erase(vector, i);
        } else {
            i++;
        }
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

// Funksje "specjalizowane" dla typu danych double:
int cmp(const void *p1, const void *p2) {
    char *a = *(char **)p1;
    char *b = *(char **)p2;
    return strcmp(a,b);
}

void sort(Vector* vector) {
    qsort(vector->data, vector->size, vector->element_size, cmp);
}

void print_data(void *a)
{
    printf("%s ",*(char**)a);
}


int main(void) {
    Vector my_vector;
    init_vector(&my_vector,5,sizeof(char*));
    my_vector.cmp_data=cmp;
    my_vector.dump_it=print_data;
    reserve(&my_vector,8);
    push_front(&my_vector,read_string());
    push_front(&my_vector,read_string());
    push_front(&my_vector,read_string());
    dump_data(&my_vector);
    push_back(&my_vector,read_string());
    dump_data(&my_vector);
    insert(&my_vector,2,read_string());
    dump_data(&my_vector);
    erase(&my_vector,1);
    dump_data(&my_vector);
    sort(&my_vector);
    dump_data(&my_vector);
    clear(&my_vector);
     return 0;
}

