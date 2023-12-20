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
 struct tagListElement *prev;
 void                  *data;
} ListElement;

typedef void (*ConstDataFp)(const void*);
typedef void (*DataFp)(void*);
typedef int  (*CompareDataFp)(const void*,const void*);

typedef struct tagList {
    ListElement *head;
    ListElement *tail;
    int size;
    ConstDataFp dumpData;
    DataFp freeData;
    CompareDataFp compareData;
} List;


int compareString(const void *e1, const void *e2) {
    return strcasecmp(((struct string*)e1)->p,((struct string*)e2)->p);
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
/* zwolnienie pamiêci listy */
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
/* dodaj element na koñcu */
void pushBack(List *plist, void *data) {
    ListElement *element = (ListElement*)malloc(sizeof(ListElement));
    element->data=data;
    element->next=NULL;
    element->prev=plist->tail;
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
    element->prev=NULL;
    if(plist->head) plist->head->prev=element;
    plist->head=element;
    if(!plist->tail)plist->tail=plist->head;
    plist->size++;
}
ListElement* findInsertionPoint(const List *plist, const ListElement *newElement) {
    ListElement *currentForward = plist->head;
    ListElement *currentBackward = plist->tail;
    ListElement *prevForward = NULL;
    ListElement *prevBackward = NULL;

    while (currentForward != NULL && currentBackward != NULL){

        if (plist->compareData(newElement->data, currentForward->data) <= 0) return prevForward;
        else
        {
            prevForward = currentForward;
            currentForward = currentForward->next;
        }
        if (plist->compareData(newElement->data, currentBackward->data) >= 0) return currentBackward;
        else
        {
            prevBackward = currentBackward;
            currentBackward = currentBackward->prev;
        }
    }
    return 0;
}


ListElement *bsearch_list(const List *plist,const char *key)
{
    ListElement *currentForward = plist->head;
    ListElement *currentBackward = plist->tail;

    while (currentForward != NULL && currentBackward != NULL){

        if (strcasecmp(((struct string*)(currentForward->data))->p,key)==0) return currentForward;
        else currentForward = currentForward->next;

        if (strcasecmp(((struct string*)(currentBackward->data))->p,key)==0) return currentBackward;
        else currentBackward = currentBackward->prev;

    }
}
/* dodanie danych do listy */
void add(List *plist,void *data) {
    ListElement *element = (ListElement*)malloc(sizeof(ListElement));
    element->next=0;
    element->prev=0;
    element->data=data;
    if(!plist->compareData) { // bez sortowania
        if(plist->tail) plist->tail->next=element;
        element->prev=plist->tail;
        plist->tail=element;
        if(!plist->head)plist->head=plist->tail;
        plist->size++;
    }

    else {            // sortowanie podczas wstwiania
        ListElement*insertionPt = findInsertionPoint(plist,element);
        if(insertionPt==0) {
            element->next=plist->head;

            if(plist->head) plist->head->prev=element;
            plist->head=element;
            if(plist->tail==0) plist->tail=plist->head;
        }
        else {
            element->next=insertionPt->next;
            if(insertionPt->next) insertionPt->next->prev=element;
            insertionPt->next=element;
            element->prev=insertionPt;
            if(plist->tail==insertionPt) plist->tail=element;

        }
    }
    plist->size++;

}


/* czy lista jets pusta */
int isEmpty(const List *plist) {
    return plist->size==0;
}

/* wypisanie zawartoœci */
void dumpList(const List *plist) {
    int counter =1;
    ListElement *i;
    for(i=plist->head;i!=0;i=i->next){
        printf("%d ",counter);
        if(plist->dumpData) plist->dumpData(i->data);
        else printf("%p ",i->data);
        counter++;
    }
}


void printString(const void *data) {
    printf("%d %s\n ",((struct string*)data)->n,((struct string*)data)->p);
}
void print_index(const List *plist, int index)
{
    int k=1;
    ListElement *i;
    if(index < (int)(plist->size)/2)
    {
        for(i=plist->head;i!=0;i=i->next)
        {
            if(k==index)
            {
                plist->dumpData(i->data);
                break;
            }
            k++;
        }
    }
    else{
        k=plist->size;
        for(i=plist->tail;i!=0;i=i->prev)
        {
            if(k==index)
            {
                plist->dumpData(i->data);
                break;
            }
            k--;
        }
    }

}

int main(void) {
    List list;
    init(&list);
    list.compareData=compareString;
    list.dumpData=printString;
    int count=0;
    FILE *file = fopen("tekst_linux.txt","r");
    if (file == NULL) {
        printf("Blad pliku");
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
            ListElement *wsk = bsearch_list(&list,token);
            if(wsk == 0)
            {
                struct string *item = malloc(sizeof(struct string));
                item->n=1;
                item->p=(char *)strdup(token);
                add(&list,item);
            }
            else (((struct string*)(wsk->data))->n)++;
            token = strtok(NULL,delimiters);
        }
    }
    //dumpList(&list);
    print_index(&list,21);
    freeList(&list);
    int end = fclose(file);


}



