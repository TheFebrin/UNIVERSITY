//
//  main.c
//  Plecak
//
//  Created by Dawid on 16/01/2018.
//  Copyright © 2018 Dawid. All rights reserved.
//

int max(int a, int b)
{
    if(a>b)return a;
    else return b;
}

#include <stdio.h>

int main(int argc, const char * argv[])
{
    int n,Wmax;
    scanf("%d",&n);
    scanf("%d",&Wmax);
    int rzeczy[2][n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&rzeczy[0][i]);
        scanf("%d",&rzeczy[1][i]);
    }
    int wynik[Wmax+1];
    wynik[0]=0;
    for(int i=1;i<=Wmax;i++)wynik[i]=-1;
    
    for(int i=0;i<n;i++)
    {
        int aktW=rzeczy[0][i];
        printf("biore: %d, o wartosci: %d \n",rzeczy[0][i],rzeczy[1][i]);
        for(int j=Wmax; j-aktW>=0;j--)
        {
            if(wynik[j-aktW]>=0)
            {
                wynik[j]=max(wynik[j-aktW]+rzeczy[1][i],wynik[j]);
            }
        }
    }
    printf("\n");
    for(int i=0;i<=Wmax;i++)printf("%d ",wynik[i]);
    
    return 0;
}
