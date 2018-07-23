//
//  main.c
//  Labirynt zalewany woda
//
//  Created by Dawid on 10/12/2017.
//  Copyright © 2017 Dawid. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

struct pair
{
    int first;
    int second;
};

struct pair kolejka[10000000];    //mozna mallocowac pamiec ale jestem glupi
int p=0; //poczatek kolejki
int k=0; //koniec kolejki

void push(int m, int n) //dodaje pare do kolejki
{
    struct pair para;
    para.first=m;
    para.second=n;
    kolejka[k]=para;
    k=(k+1)%10000000;
    //k++;
}

struct pair front()  //zwraca i usuwa pierwsza pare z kolejki
{
    struct pair ret=kolejka[p];
    p=(p+1)%10000000;
    return ret;
}

bool notEmpty() //sprawdza czy kolejka jest pusta czy pelna
{
    if(p<k) return true;
    else return false;
}

int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};

int main(void)
{
    int n,m;  //n dl     m szerokosc
    scanf("%d %d",&n,&m);
    
    char tab[n][m];
    int x=0;int y=0; //wspolrzedne zrodla wody
    int PustePole=0;
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf(" %c",&tab[i][j]);
            if(tab[i][j]=='!')
            {
                x=i;
                y=j;
            }
            if(tab[i][j]=='-')PustePole++;
        }
    }
    
    push(x, y);
    int nj,ni;
    int ile=0;
    int zapelnione=0;
    bool wyszedl=true;
    struct pair tmp;
    
    
while(notEmpty())
{
    struct pair para=front();
    
    if(tmp.first==para.first && tmp.second==para.second){ile++;wyszedl=true;}
    int a=para.first;
    int b=para.second;
    
    
    for(int k=0;k<4;k++)
    {
        ni=a+dx[k];
        nj=b+dy[k];
       if(nj <0 || ni<0 || ni>=n || nj>=m) continue;
        if(tab[ni][nj]=='-')
        {
            push(ni,nj);
            tab[ni][nj]='!';
            zapelnione++;
            
            if(wyszedl)
            {
            tmp.first=ni;
            tmp.second=nj;
            wyszedl=false;
            }
        }
    }
}
    /*
    printf("\n\n WYNIK \n\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)printf("%c",tab[i][j]);
        printf("\n");
    }
    */
   // printf("\n\nilosc %d, zapelnionych jest, %d,  wykonalo sie razy %d\n",PustePole,zapelnione,ile);
    
    if(zapelnione==PustePole)
    {
        printf("%d",ile);
    }
    else printf("-1");
    
    return 0;
}
