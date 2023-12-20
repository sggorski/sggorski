#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


void swap(int *a, int *b)
{
    int temp = *a;
    *a =*b;
    *b=temp;
}
void sort(int *p, int n)
{
    int *wsk2 = &p[n-1];
    int *wsk1 = p;
    int *tmp;
    while(wsk1<wsk2)
    {
        tmp =wsk1+1;
        while(tmp<=wsk2)
        {
            if(*wsk1<*tmp) swap(wsk1,tmp);
            tmp++;
        }
        wsk1++;
    }



}
int main()
{
    FILE *file;
    file=fopen("liczby.txt","r");
    char buf[50];
    int *tmp=malloc(sizeof(int)*20);
    int i=0;
    while(fgets(buf,50,file)!=NULL)
    {
        tmp[i]= atoi(buf);
        i++;

    }
    sort(tmp,i);
    for(int j=0;j<i;j++) printf("%d\n",tmp[j]);



    free(tmp);
    int end = fclose(file);






    return 0;
}
