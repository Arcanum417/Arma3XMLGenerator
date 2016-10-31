#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct zoznam{
    char nick[30];
	char remark[30];
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
        printf("Error opening file!\n");
        exit(1);
        }
    struct zoznam *actual;
    actual=head;
    char check;
    while ((check=getc(fr))!=EOF)
        {
          ungetc(check,fr);
          fscanf(fr,"%[^\t]\t%llu\t%[^\n]\n",&actual->nick,&actual->id,&actual->remark);
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
        fprintf(fw,"<member id=\"%llu\" nick=\"%s\">\n\t<name>N/A</name>\n\t<email>contact@417rct.org</email>\n\t<icq>N/A</icq>\n\t<remark>%s</remark>\n</member>",act->id,act->nick,act->remark);
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
