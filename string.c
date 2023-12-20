#include <stdio.h>
#include <string.h>
#include <malloc.h>

void cenzura(char tekst[],char slowo[],char zamiennik[])
{
    char wynik[200];
    char *p=strstr(tekst,slowo);
    strncpy(wynik,tekst,p-tekst);
    wynik[p-tekst]='\0';
    strcat(wynik,zamiennik);
    strcat(wynik,p+strlen(slowo));
    p=strstr(wynik,slowo);
    if(p!=NULL) cenzura(wynik,slowo,zamiennik);
    else printf("%s",wynik);

}


int main()
{

    char tekst1[100];
    char slowo[50]="kurwa";
    char tekst2[10]="****";
    scanf("%s",tekst1);
    cenzura(tekst1,slowo,tekst2);
    printf("\n");

    return 0;
}
