#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct string
{
    char *addres;
    int counter;

};

int compareSearch (const void *key, const void *element)
{
    return strcmp((char*)key,((struct string*)element)->addres);
}
int compareStrings(const void *a, const void *b) {
    //int v1 = (*(struct string *)a).counter;
    int v1 = ((struct string *)a)->counter;
    int v2 = (*(struct string *)b).counter;
    char *p1=  (*(struct string *)a).addres;
    char *p2=  (*(struct string *)b).addres;
    if(v1 < v2) return 1;
    else if(v1>v2) return -1;
    else return strcmp(p1,p2);

}
int compareStrings2(const void*a, const void*b)
{
    char *p1=  (*(struct string *)a).addres;
    char *p2=  (*(struct string *)b).addres;
    return strcmp(p1,p2);
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

    int n;
    scanf("%d",&n);
    const int N=n;
    struct string tab[N];
    int elements =0;
    for(int i=0;i<N;i++)
    {
        char *text = read_string();
        struct string *wsk = bsearch(text,tab,elements,sizeof(struct string),compareSearch);
        if(wsk == NULL)
        {
            struct string item;
            item.addres=text;
            item.counter=1;
            tab[elements]=item;
            elements++;
            free(wsk);
        }
        else
        {
            wsk->counter++;
            free(text);
        }
        qsort(tab,elements,sizeof(struct string),compareStrings2);
    }
    qsort(tab,elements,sizeof(struct string),compareStrings);
    print(tab,elements);
    return 0;
}
