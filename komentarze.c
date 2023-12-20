#include <stdio.h>

int main()
{
    FILE *file;
    file=fopen("nowy_plik.txt","r");
    char znak;
    int state =0;
    char temp='0';
    int ent_err=0;
    while((znak=fgetc(file))!=EOF)
    {


        switch(state)
        {
            case 0:
                if(ent_err==1 && znak=='\n')
                {
                    ent_err=0;
                    break;
                }
                if(znak=='/') state=1;
                else printf("%c",znak);
                break;
            case 1:
                if(znak=='/')
                {
                    state =2;
                    break;
                }
                else if(znak=='*')
                {
                    state=3;
                    break;
                }

                else
                {
                    printf("/%c",znak);
                    state=0;
                    break;
                }
            case 2:
                if(znak=='\n')
                {
                    state=0;
                    break;
                }
            case 3:
                if(znak=='*')
                {
                    temp=znak;
                    break;
                }
                else if(znak=='/' && temp=='*'){
                    state=0;
                    ent_err=1;
                    break;
                }
                else
                {
                    temp='0';
                    break;
                }




        }
    }

    int koniec = fclose(file);





    return 0;
}
