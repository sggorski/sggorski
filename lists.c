#include <stdio.h>
#include <malloc.h>

struct list1
{
    double x;
    struct list1 *nast;
};


void wstaw(struct list1 **pocz, double war)
{
    struct list1 *nowy, *ww=*pocz;
    nowy = malloc(sizeof(struct list1));
    nowy->x=war;
    nowy->nast=0;
    if(*pocz==0) *pocz = nowy;
    else{
        while(ww->nast) ww=ww->nast;
        ww->nast=nowy;
    }

};

void wypisz(struct list1 *pocz)
{
    while(pocz)
    {
        printf("%f\n",pocz->x);
        pocz=pocz->nast;
    }
}

void wstaw_sort(struct list1 **pocz, double war)
{
    struct list1 *nowy, *ww=*pocz;
    nowy = malloc(sizeof(struct list1));
    nowy->x=war;
    if(ww==0 || war < ww->x)
    {
        nowy->nast=ww;
        *pocz = nowy;
    }
    else{
        while(ww->nast!=0 && war > ww->nast->x) ww= ww->nast;
        nowy->nast=ww->nast;
        ww->nast=nowy;

    }
}

void usun(struct list1 **pocz,double war)
{
    struct list1 *pom, *ww=*pocz;
    if(ww==0) return;
    if(war== ww->x)
    {
        *pocz = ww->nast;
        free(ww);
    }
    else{

        while(ww->nast!=0 && war!=ww->nast->x) ww= ww->nast;
        if(ww->nast!=0 && war==ww->nast->x)
        {
            pom = ww->nast;
            ww->nast=ww->nast->nast;
            free(pom);
        }

    }


}

struct list1* find(struct list1 *pocz, double war)
{
    while(pocz && pocz->x!=war) pocz=pocz->nast;
    return pocz;

};

struct list1* copy(struct list1 *pocz)
{
  struct list1 *nowy, *poprzedni, *list2=0;
  while(pocz)
  {
      nowy = malloc(sizeof(struct list1));
      nowy ->x = pocz->x;
      if(list2==0) list2 = nowy;
      else
      {
          poprzedni->nast=nowy;
      }
      poprzedni =nowy;
      pocz=pocz->nast;
  }
  if(list2) nowy->nast=0;
  return list2;
}

struct list1 *add(struct list1 *pocz1,struct list1 *pocz2 )
{
    struct list1 *cop1, *cop2, *pom;
    cop1= copy(pocz1);
    cop2= copy(pocz2);
    if(cop1==0) return cop2;
    pom = cop1;
    while(pom->nast) pom = pom->nast;
    pom->nast=cop2;
    return cop1;
}

void free_list(struct list1 *pocz)
{
    struct list1 *pom, *ww=pocz;
    while(ww)
    {
        pom =ww;
        ww=ww->nast;
        free(pom);
    }
}
int main()
{
    struct list1 *pocz =0,*ws1,*pocz2,*pocz3;
    wstaw_sort(&pocz,5);
    wstaw_sort(&pocz,6);
    wstaw_sort(&pocz,2);
    wypisz(pocz);
    usun(&pocz,5);
    wypisz(pocz);
    ws1= find(pocz,2);
    printf("%f",(*ws1).x); // jesli wsk = 0 to brak elementu
    pocz2 = copy(pocz);
    printf("\n");
    wypisz(pocz2);
    pocz3 =add(pocz,pocz2);
    printf("\n");
    wypisz(pocz3);
    free_list(pocz);
    free_list(pocz2);
    free_list(pocz3);






    return 0;
}
