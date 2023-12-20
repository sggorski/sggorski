#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void swap(char **a, char **b)
{
    char *tmp = *a;
    *a=*b;
    *b=tmp;
}

void sort( char **p, int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(strncasecmp(p[i],p[j])>0) swap(&p[i],&p[j]);
        }
    }
}

int main()
{
    FILE *file;
    file=fopen("slowa.txt","r");
    char buf[100];
    char **tmp=malloc(sizeof(char*)*20);
    int i=0;
    while(fgets(buf,100,file)!=0)
    {
        char *p = malloc(sizeof(char)*(strlen(buf)+1));
        strcpy(p,buf);
        tmp[i]= p;
        i++;

    }
    sort(tmp,i);
    for(int j=0;j<i;j++) printf("%s",tmp[j]);



    free(tmp);
    int end = fclose(file);






    return 0;
}

