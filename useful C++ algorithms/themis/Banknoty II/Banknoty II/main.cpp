//Dawid to ziomal

#include <bits/stdc++.h>
using namespace std;


int main()
{
    int n;
    cin>>n;
    int tab[n];
    for(int i=0;i<n;i++)cin>>tab[i];
    int kwota;
    cin>>kwota;
    
    int wynik[kwota+1];
    wynik[0]=0;
    for (int i=1; i<=kwota; i++) {
        wynik[i]=INT_MAX-1;
    }
    for (int i=0; i<n; i++)
    {
        int aktNominal=tab[i];
        for (int j=aktNominal; j<=kwota; j++)
        {
            if(wynik[j-aktNominal]>=0)
            {
                wynik[j]=min(wynik[j-aktNominal]+1,wynik[j]);
            }
        }
    }
    
    if(wynik[kwota]!=INT_MAX-1)cout<<wynik[kwota]<<endl;
    else cout<<"NIE"<<endl;
    return 0;
}


