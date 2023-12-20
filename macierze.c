#include <stdio.h>
#include <malloc.h>

void wpisz(int *p,int w,int k)
{
    for(int i=0;i<w*k;i++)
    {
        scanf("%d",p);
        p++;
    }

}

void wpisz2(int w,int k,int (*tab)[k]) // Przekazujemy nazwe tablice dwuwymiarowej - wsk do podtablic
{
    for(int i=0;i<w;i++)
    {
      for(int j=0;j<k;j++)
      {
          scanf("%d",*(tab+i)+j);
      }
    }

}

void wypisz(int *p, int w, int k)
{
    for(int i=0;i<w*k;i++)
    {
        printf("%d ",*p);
        if((i+1)%k ==0) printf("\n");
        p++;

    }
}

void dodaj(int *suma,int *p1, int *p2, int w, int k)
{
    for(int i=0;i<w*k;i++)
    {
        *suma = *p1 + *p2;
        suma++;
        p1++;
        p2++;

    }
}

void pomnoz(int *iloczyn,int *p1, int *p2, int w1, int k1,int w2, int k2)
{
    for(int i=0;i<w1;i++)
    {
        for(int j=0;j<k2;j++)
        {
            *(iloczyn +i*k2 +j) =0;
            for(int k=0;k<k1;k++)
            {
                *(iloczyn +i*k2 +j) += *(p1 + i*k1 +k) * *(p2 + k*k2 +j);
            }
        }
    }

}
int main()
{
    // mozna z tablica int�w z malloc albo wsk do tablicy k elementowej
    // int *m1 = malloc(sizoof(int)*w*k) i przekazujemy nazwe - wsk do 1 elementu!
    /*
    int w=2;
    int k=2;
    int tab[w][k];
    wpisz(tab[0],w,k);
    wypisz(tab[0],w,k); */


    int w1,k1,w2,k2;
    scanf("%d%d%d%d",&w1,&k1,&w2,&k2);


    int *m1= malloc(w1*k1*sizeof(int));
    int *m2= malloc(w2*k2*sizeof(int));
    wpisz(m1,w1,k1);
    wpisz(m2,w2,k2);
    if(w1==w2 && k1==k2)
    {
        int *sum= malloc(w1*k1*sizeof(int));
        dodaj(sum,m1,m2,w1,k1);
        wypisz(sum,w1,k1);
    }

    if(k1==w2)
    {
        int *mult= malloc(w1*k2*sizeof(int));
        pomnoz(mult,m1,m2,w1,k1,w2,k2);
        wypisz(mult,w1,k2);
    }

    free(m1);
    free(m2);



    return 0;
}
