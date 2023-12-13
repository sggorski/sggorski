#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef int (*cmp_data_fp)(const void*, const void*);


typedef struct tagVector {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
    cmp_data_fp cmp_data;
} Vector;

// Fukcje "uniwersalne":


void init_vector(Vector *v, size_t cap, size_t el_size)
{
    v->size=0;
    v->element_size=el_size;
    v->capacity=cap;
    v->data=malloc(v->capacity* v->element_size);
}

void clear(Vector* vector) {
    free(vector->data);
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


void push_back(Vector* vector, double val) {

    if (vector->size == vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        reserve(vector, new_cap);
    }

    char* dest = (char*)vector->data + (vector->size * vector->element_size);
    memcpy(dest, &val, vector->element_size);
    vector->size++;
}

void push_front(Vector* vector, double val) {
    if (vector->size == vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        reserve(vector, new_cap);
    }
    for (size_t i = vector->size; i > 0; --i) {
        char* dest = (char*)vector->data + i * vector->element_size;
        char* from = (char*)vector->data + (i - 1) * vector->element_size;
        memcpy(dest, from, vector->element_size);
    }

    memcpy(vector->data, &val, vector->element_size);
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
        printf("%0.1f ", *(double*)address);
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
void insert(Vector* vector, size_t position, double val) {
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
            memcpy(dest, from, vector->element_size);
        }

        memcpy((char*)vector->data + position * vector->element_size, &val, vector->element_size);
        vector->size++;


}
void erase(Vector* vector, size_t position) {
    if (position < vector->size) {

        for (size_t i = position; i < vector->size - 1; ++i) {
            char* dest = (char*)vector->data + i * vector->element_size;
            char* src = (char*)vector->data + (i + 1) * vector->element_size;
            memcpy(dest, src, vector->element_size);
        }
        vector->size--;

    }
}
void erase_value(Vector* vector, double value) {
    size_t i = 0;
    while (i < vector->size) {
        void* address = (char*)vector->data + (i * vector->element_size);

        if (*(double*)address == value) {
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
    double a=*(double*)p1, b=*(double*)p2;
    if(b>a) return 1;
    else if(b<a) return -1;
    else return 0;
}

void sort(Vector* vector) {
    qsort(vector->data, vector->size, vector->element_size, cmp);
}


int main(void) {
    Vector my_vector;
    init_vector(&my_vector,5,sizeof(double));
    reserve(&my_vector,8);
    push_front(&my_vector,5.0);
    push_front(&my_vector,6.1);
    push_back(&my_vector,1.1);
    dump_data(&my_vector);
    insert(&my_vector,1,3);
    dump_data(&my_vector);
    erase(&my_vector,1);
    dump_data(&my_vector);
    push_front(&my_vector,5);
    push_front(&my_vector,9);
    push_front(&my_vector,10);
    push_front(&my_vector,5);
    dump_data(&my_vector);
    erase_value(&my_vector,5);
    dump_data(&my_vector);
    sort(&my_vector);
    dump_data(&my_vector);
    clear(&my_vector);
    dump_data(&my_vector);
    return 0;
}
