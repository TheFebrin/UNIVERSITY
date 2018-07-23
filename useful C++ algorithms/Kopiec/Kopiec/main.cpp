//
//  main.cpp
//  Kopiec
//
//  Created by Dawid on 04/12/2017.
//  Copyright © 2017 Dawid. All rights reserved.
//

// <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

#define INF 1000000000

int kopiec[1000000];
int dlugosc=0;
/*
 pair<int,int> lewySyn=make_pair(INF,0);
 pair <int,int> prawySyn=make_pair(INF,0);
 */
int prawySyn=INF;
int lewySyn=INF;

int  minimum()
{
    return kopiec[1];
}

void usunMinimum()
{
    kopiec[1]=kopiec[dlugosc];
    dlugosc--;
    int i=1;
    int tmp=0;
    if(2*i<=dlugosc) lewySyn=kopiec[2*i];
    if(2*i+1<=dlugosc) prawySyn=kopiec[2*i+1];
    
    while(kopiec[i]>prawySyn and kopiec[i]>lewySyn)
    {
        if(kopiec[i]>prawySyn)
        {
           // swap(kopiec[i],kopiec[i*2]);
            tmp=kopiec[i];
            kopiec[i]=kopiec[i*2];
            kopiec[i*2]=tmp;
            i*=2;
        }
        else
        {
            swap(kopiec[i],kopiec[i*2+1]); i=2*i+1;
        }
        
        if(2*i<=dlugosc) lewySyn=kopiec[2*i];
        if(2*i+1<=dlugosc) prawySyn=kopiec[2*i+1];
    }
}

void dodaj(int a)
{
    dlugosc++;
    kopiec[dlugosc]=a;
    int index=dlugosc;
    
    while(kopiec[index]<kopiec[index/2] and index>1)
    {
        swap(kopiec[index],kopiec[index/2]);
        index/=2;
    }
}

int main()
{
    for(int i=0;i<20;i++)
    {
        dodaj(i);
    }
    usunMinimum();
    cout<<kopiec[1]<<endl;
    return 0;
}
