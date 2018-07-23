//
//  main.c
//  Lista
//
//  Created by Dawid on 23/01/2018.
//  Copyright © 2018 Dawid. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct elem {
    int val; //dane właściwe
    struct elem *next; // wskaznik na nastepny element
};


struct elem *utworz(int wart)
{ //utworzenie nowej jednoelementowej listy
    struct elem *pom;
    pom=(struct elem *) malloc(sizeof(struct elem));
    pom->val = wart;
    pom->next = NULL;
    return pom;
}
void wypisz(struct elem *lis)
{
    while (lis!=NULL)
    {
        printf("%d ",lis->val); lis = lis->next;
    }
    
}

void dodaj(struct elem *lis, int w)
{
    struct elem *ostatni = NULL;
    while (lis!=NULL)
    {
        ostatni=lis;
        lis=lis->next;
    }
    struct elem *nowy=utworz(w);
    ostatni->next=nowy;
}

void odwroc(struct elem *list)
{
    struct elem* poprz   = NULL;
    struct elem* akt = list;
    struct elem* nast;
    while (akt != NULL)
    {
        nast  = akt->next;
        akt->next = poprz;
        poprz = akt;
        akt = nast;
    }
 //   list = prev;
}
struct elem *ogon(struct elem *lis)
{
    if (lis!=NULL) return lis->next;
    else return NULL;
    
}

void wypiszodw(struct elem *list)
{
    if(list->next!=NULL)
    wypiszodw(ogon(list));
    printf("%d ",list->val);
}

int main(int argc, const char * argv[])
{
    struct elem *a= utworz(1);
    struct elem *b= utworz(2);
    struct elem *c= utworz(3);
    struct elem *d= utworz(4);
    struct elem *e= utworz(5);
    a->next=b;
    b->next=c;
    c->next=d;
    d->next=e;
    printf("Start\n");
    dodaj(a, 10);
    wypisz(a);
    printf("\n\n");
    //odwroc(a);
    //wypisz(e);
    wypiszodw(a);
    
    
    
    
    return 0;
}
