//
//  main.c
//  Zliczanie sasiednich 1
//
//  Created by Dawid on 05/12/2017.
//  Copyright © 2017 Dawid. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
//#include <queue>


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



int main()
{
    int dx[8]={0,0,-1,1,1,-1,-1,1};
    int dy[8]={1,-1,0,0,1,-1,1,-1};
    
    
    char plik[3];
    scanf("%s",plik);
    
    int n,m;
    scanf("%d %d",&m,&n);
    
    //n to wysokosc
    //m to szerokosc
    
    int tab[n][m];
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&tab[i][j]);
        }
    }
    
    int ile=0;
    int nj,ni;
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(tab[i][j]==1) //jak znajde 1 to wrzucam ja do kolejki
            {
                ile++;
                push(i,j);
                tab[i][j]=0;// wrzucilem 1 do kolejki to zmieniam na 0
                
                while (notEmpty()) //dopoki cos jest w kolejce
                {
                    /* biore pierwsza pare z kolejki*/
                    struct pair para=front();
                    int a=para.first;
                    int b=para.second;
                    
                    for(int k=0;k<8;k++)
                    {
                        ni=a+dx[k];
                        nj=b+dy[k];
                        if(nj <0 || ni<0 || ni==n || nj==m) continue;
                        if(tab[ni][nj]==1) //jak sasiad jest 1 to wrzucam go do kolejki
                        {
                            push(ni,nj);
                            tab[ni][nj]=0;
                        }
                    }
                    
                    //  printf("p to %d, k to%d \n",p,k);
                    
                }
                
                
            }
            
        }
    }
    printf("%d",ile);
    return 0;
}

