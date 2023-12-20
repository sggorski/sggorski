#include <stdio.h>
#include <malloc.h>

struct tree
{
    double w;
    struct tree *lewy, *prawy;
};

void wstaw(struct tree **pocz, double war)
{
    struct tree *nowy, *ws = *pocz, *nastepny;
    nowy = malloc(sizeof(struct tree));
    nowy->w=war;
    nowy->lewy= nowy->prawy =0;
    if(ws==0) *pocz=nowy;
    else{
        while(1)
        {
            if(war<ws->w)
            {
                if(ws->lewy==0) { ws->lewy=nowy; break; }
                else ws=ws->lewy;
            }
            else
            {
                if(ws->prawy==0) { ws->prawy=nowy; break; }
                else ws=ws->prawy;
            }
        }
    }
}

void wypisz(struct tree *pocz)
{
    if(pocz==0) return;
    else{
        wypisz(pocz->lewy);
        printf("%f\n",pocz->w);
        wypisz(pocz->prawy);
    }
}
int main()
{
    struct tree *pocz =0;
    wstaw(&pocz,1);
    wstaw(&pocz,5);
    wstaw(&pocz,2);
    wstaw(&pocz,3);
    wstaw(&pocz,6);
    wypisz(pocz);



    return 0;
}
