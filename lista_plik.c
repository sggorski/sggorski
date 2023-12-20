#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
typedef int (*cmp_data_fp)(const void*, const void*);

struct string
{
    char *addres;
    int counter;

};

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


void push_back(Vector* vector, void* val) {

    if (vector->size == vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        reserve(vector, new_cap);
    }

    char* dest = (char*)vector->data + (vector->size * vector->element_size);
    memcpy(dest, &val, vector->element_size);
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
        printf("%d %s ",(*(struct string**)address)->counter, (*(struct string**)address)->addres);
        printf("\n");
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



int compareSearch (const void *key, const void *element)
{
    return strcasecmp((char*)key,(*(struct string**)element)->addres);
}
int compareStrings(const void *a, const void *b) {
    //int v1 = (*(struct string *)a).counter;
    int v1 = (*(struct string **)a)->counter;
    int v2 = (*(struct string **)b)->counter;
    char *p1=  (*(struct string **)a)->addres;
    char *p2=  (*(struct string **)b)->addres;
    if(v1 < v2) return 1;
    else if(v1>v2) return -1;
    else return strcasecmp(p1,p2);

}
int compareStrings2(const void*a, const void*b)
{
    char *p1=  (*(struct string **)a)->addres;
    char *p2=  (*(struct string **)b)->addres;
    return strcasecmp(p1,p2);
}

void sort1(Vector* vector) {
    qsort(vector->data, vector->size, vector->element_size, compareStrings2);
}

void sort2(Vector* vector) {
    qsort(vector->data, vector->size, vector->element_size, compareStrings);
}
char *read_string()
{
    char buffor[100];
    scanf("%s",buffor);
    char *p = malloc(sizeof(char)*(strlen(buffor)+1));
    strcpy(p,buffor);
    return p;

}

void print(struct string *text, int n)
{
    for(int i=0;i<n;i++) printf("%s\n",(text+i)->addres);
}
int main(void) {

    int count=0;
    Vector my_vector;
    init_vector(&my_vector,20,sizeof(struct string*));
    FILE *file = fopen("tekst_linux.txt","r");
    if (file == NULL) {
        printf("Nie uda³o siê otworzyæ pliku");
        return 1;
    }
    char buff[200];
    char *delimiters = " \t\n.,():?!\"";
    while(fgets(buff,200,file)!=0)
    {
        char *token= strtok(buff,delimiters);
        while (token != NULL)
        {
            count++;
            sort1(&my_vector);
            struct string **wsk = bsearch(token,my_vector.data,my_vector.size,my_vector.element_size,compareSearch);
            if(wsk == NULL)
            {
                struct string *item = malloc(sizeof(struct string));
                item->counter=1;
                item->addres=strdup(token);
                push_back(&my_vector,item);
            }
            else (*wsk)->counter++;
            token = strtok(NULL,delimiters);
        }
    }
    sort2(&my_vector);
    dump_data(&my_vector);
    printf("Liczba unikalnych slow: %d \n",my_vector.size);
    printf("Liczba wszystkich  slow: %d \n",count);
    clear(&my_vector);

    int end = fclose(file);

    return 0;
}

