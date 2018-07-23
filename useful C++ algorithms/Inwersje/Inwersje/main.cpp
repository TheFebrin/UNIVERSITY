//
//  main.cpp
//  E. Enemy is weak
//
//  Created by Dawid on 30/12/2017.
//  Copyright © 2017 Dawid. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;
typedef long long  ll;
#define MAX 1000007
#define DRZ (2<<21)

ll drz[2*DRZ];
xd

ll suma(ll p,ll k)
{
    ll ret=0;
    p+=DRZ;
    k+=DRZ;
    
    while(p<k)
    {
        if(p%2) ret+=drz[p++];
        p/=2;
        if(k%2)ret+=drz[k++];
        k/=2;
    }
    if(p==k)ret+=drz[p];
    return ret;
}

void dodaj(ll index)
{
    ll m=index+DRZ;
    drz[m]+=1;
    while(m>1)
    {
        m/=2;
        drz[m]=drz[m*2]+drz[m*2+1];
    }
}

void inwersje(int A[], int n)
{
    ll ret=0;
    for(int i=1;i<=n;i++)
    {
        ret=suma(A[i]+1, n+1);
        dodaj(A[i]);
        cout<<ret<<" ";
    }
}


int main()
{
    int n;
    cin>>n;
    int tab[MAX];
    for(int i=1;i<=n;i++)scanf("%d",&tab[i]);
    
    inwersje(tab,n);
    
    
    return 0;
}

