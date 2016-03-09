#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct zoznam{
    char nick[30];
    unsigned long long int id;
    struct zoznam *dalsi;
};

struct zoznam* vytvor()
{
    struct zoznam *pointer = (struct zoznam*)malloc(sizeof(struct zoznam));
    pointer->dalsi = NULL;
    return pointer;
}

void nacitaj(struct zoznam* head)
{
    FILE *fr;
    if ((fr=fopen("input.txt", "r"))==NULL)
        {
        printf("Zaznamy neboli nacitane\n");
        return 0;
        }
    struct zoznam *actual;
    actual=head;
    char check;
    while ((check=getc(fr))!=EOF)
        {
          ungetc(check,fr);
          fscanf(fr,"%s\t%llu",&actual->nick,&actual->id);
          if((check=getc(fr))!=EOF)
                {
                    ungetc(check,fr);
                    actual->dalsi= (struct zoznam*)malloc(sizeof(struct zoznam));
                    actual=actual->dalsi;
                }
          else
              actual->dalsi=NULL;


        }


}

void vypis(struct zoznam *pointer){
    struct zoznam *act;
    act=pointer;
    FILE *fw = fopen("output.txt", "w");
    if (fw == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    while(act!=NULL){
        fprintf(fw,"<member id=\"%llu\" nick=\"%s\">\n\t<name>N/A</name>\n\t<email>N/A</email>\n\t<icq>N/A</icq>\n\t<remark>N/A</remark>\n</member>",act->id,act->nick);
    act=act->dalsi;
    }
    fclose(fw);
}

int main(void)
{
    struct zoznam *head;
    head=vytvor();
    nacitaj(head);
    vypis(head);
    return 0;
}

