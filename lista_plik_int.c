#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

char *read_string()
{
    char buffor[100];
    scanf("%s",buffor);
    char *p = malloc(sizeof(char)*(strlen(buffor)+1));
    strcpy(p,buffor);
    return p;

}

struct string{
    char *p;
    int n;
};
typedef struct tagListElement {
 struct tagListElement *next;
 void                  *data;
} ListElement;

typedef void (*ConstDataFp)(const void*);
typedef void (*DataFp)(void*);
typedef double  (*CompareDataFp)(const void*,const void*);

typedef struct tagList {
    ListElement *head;
    ListElement *tail;
    int size;
    ConstDataFp dumpData;
    DataFp freeData;
    CompareDataFp compareData;
} List;


double compareInt(const void *e1, const void *e2) {
    return *(double *)e1 - *(double*)e2;
}

double compareList(const void *e1, const void *e2) {
    double val1=0.0;
    double val2=0.0;
    List * plist1 = (List*)e1;
    List * plist2 = (List*)e2;
    ListElement *i;
    for(i=plist1->head;i!=0;i=i->next) val1+=*((double *)i->data);
    val1= val1/plist1->size;
    ListElement *j;
    for(j=plist2->head;j!=0;j=j->next) val2+=*((double *)j->data);
    val2= val2/plist2->size;
    return val1-val2;

}

/* inicjalizacja listy */
void init(List *plist) {
    plist->head=NULL;
    plist->tail=NULL;
    plist->size=0;
    plist->dumpData=NULL;
    plist->freeData=NULL;
    plist->compareData=NULL;
}



void freeList(List *plist) {
    ListElement *current = NULL;
    current = plist->head;
    while(current!=0) {
        ListElement *todelete = current;
        current=current->next;
        if(plist->freeData) plist->freeData(todelete->data);
        free(todelete);
    }
    plist->size=0;
    plist->head=NULL;
    plist->tail=NULL;
}

void free_main_list(void *data)
{
    freeList(data);
}

/* dodaj element na koñcu */
void pushBack(List *plist, void *data) {
    ListElement *element = (ListElement*)malloc(sizeof(ListElement));
    element->data=data;
    element->next=0;
    if(plist->tail) plist->tail->next=element;
    plist->tail=element;
    if(!plist->head)plist->head=plist->tail;
    plist->size++;
}
/* dodaj element na pocz¹tku */
void pushFront(List *plist, void *data) {
    ListElement *element = (ListElement*)malloc(sizeof(ListElement));
    element->data=data;
    element->next=plist->head;
    plist->head=element;
    if(!plist->tail)plist->tail=plist->head;
    plist->size++;
}
ListElement* findInsertionPoint(const List *plist, const ListElement *newElement) {
    ListElement *current = plist->head;
    ListElement *prev = NULL;

    while (current != NULL && plist->compareData(newElement->data, current->data) >=0) {
        prev = current;
        current = current->next;
    }

    return prev;
}


/* dodanie danych do listy */
void add(List *plist,void *data) {
    ListElement *element = (ListElement*)malloc(sizeof(ListElement));
    element->next=0;
    element->data=data;
    if(!plist->compareData) { // bez sortowania
        if(plist->tail==0) {
            plist->head=element;
            plist->tail=element;
        }
        else {
            plist->tail->next=element;
            plist->tail=element;
        }
    }

    else {            // sortowanie podczas wstwiania
        ListElement*insertionPt = findInsertionPoint(plist,element);
        if(insertionPt==0) {
            element->next=plist->head;
            plist->head=element;
            if(plist->tail==0) plist->tail=plist->head;
        }
        else {
            element->next=insertionPt->next;
            insertionPt->next=element;
            if(plist->tail==insertionPt) plist->tail=element;
        }
    }
    plist->size++;

}


/* wypisanie zawartoœci */
void dumpList(const List *plist) {
    ListElement *i;
    for(i=plist->head;i!=0;i=i->next){
        if(plist->dumpData) plist->dumpData(i->data);
        else printf("%p ",i->data);
    }
}


void printInt(const void *data) {
    printf("%0.3f | ", *(double*)data);
}

void print_min_max(const void *data) {
    printf("%0.3f | ",*(double *)(((List*)data)->head->data));
    printf("%0.3f",*(double *)(((List*)data)->tail->data));
    //dumpList(data);
    printf("\n");
}


int main(void) {
    double min=999.0,max=-1.0;
    List main_list;
    init(&main_list);
    main_list.dumpData=print_min_max;
    main_list.freeData=free_main_list;
    main_list.compareData=compareList;
    FILE *file = fopen("liczby.txt","r");
    if (file == NULL) {
        printf("Error");
        return -1;
    }
    char buff[200];
    char *delimiters = " \t\n,";
    printf(" MIN  |  MAX\n");
    while(fgets(buff,200,file)!=0)
    {
        char *token= strtok(buff,delimiters);
        List *record_list = malloc(sizeof(List));
        init(record_list);
        record_list->compareData=compareInt;
        record_list->dumpData=printInt;
        while (token != NULL)
        {
            double *w = malloc(sizeof(double));
            *w=atof(token);
            if(*w < min) min =*w;
            if(*w > max) max =*w;
            add(record_list,w);
            token = strtok(NULL,delimiters);
        }
        add(&main_list,record_list);

    }
    dumpList(&main_list);
    freeList(&main_list);
    printf("\nWartosc najwieksza: %0.3f\n", max);
    printf("Wartosc najmniejsza: %0.3f\n", min);
    int end = fclose(file);


}

