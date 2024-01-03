#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int (*cmp_data_fp)( void*,  void*);
typedef void (*dmp_data_fp)( void*);

struct word
{
    char *p;
    int counter;
};

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

void reserve(Vector* vector, size_t new_cap) {
    if (new_cap > vector->capacity) {

        vector->data = realloc(vector->data, new_cap * vector->element_size);
        vector->capacity = new_cap;
    }
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


int find(FILE *plik, char *klucz)
{
    char line[100];
    int counter = 0;
    char *znaleziony;
    while (fgets(line, sizeof(line), plik) != NULL)
    {
        znaleziony=strstr(line,klucz);
        while(znaleziony!=NULL)
        {
            counter++;
            znaleziony=strstr(znaleziony+1,klucz);
        }
    }
    return counter;
}

int compare(void *a, void *b)
{
    char *tekst1 = (*(struct word**)(a))->p;
    char *tekst2 = ((struct word*)(b))->p;
    int n1 =  (*(struct word**)(a))->counter;
    int n2 =  ((struct word*)(b))->counter;
    if(n1==n2) return strcmp(tekst1,tekst2);
    else return n2-n1;
}
void print_data(void *a)
{
    printf("%s: %d \n",(*(struct word**)(a))->p,(*(struct word**)(a))->counter);
}
int main()
{
    FILE *file;
    FILE *file2;
    Vector my_vector;
    init_vector(&my_vector,20,sizeof(struct word*));
    my_vector.cmp_data=compare;
    my_vector.dmp_data=print_data;
    int n = 0;

    file = fopen("keywords.txt", "r");
    if (file == NULL)
    {
        printf("Brak pliku!");
        return 1;
    }

    file2 = fopen("test2.txt", "r");
    if (file2 == NULL)
    {
        printf("Brak pliku!");
        fclose(file);
        return 1;
    }

    char key[100];
    while (fscanf(file, "%s", key) != EOF)
    {
        fseek(file2, 0, SEEK_SET);
        int licznik = find(file2, key);

        if (licznik != 0)
        {
            struct word *item = (struct word*)malloc(sizeof(struct word));
            item->p=(char *)strdup(key);
            item->counter=licznik;
            insert_sorted(&my_vector,item);
            n++;
        }
    }

    int end = fclose(file);
    int end2 = fclose(file2);
    dump_data(&my_vector);
    clear(&my_vector);



    return 0;
}
