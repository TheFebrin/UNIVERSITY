#include <bits/stdc++.h>
using namespace std;


bool odw[1000000];
vector <int> V;


void wypisz()
{
    for(int i=0; i<(int)V.size(); i++)
    {
        if(odw[i])cout<<V[i]<<" ";
    }
    cout<<"\n";
}


void P(int k)
{
    if(k == V.size())
    {
        wypisz();
        return;
    }
    odw[k] = true;
    P(k+1);
    odw[k] = false;
    P(k+1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n=5;
    for(int i=0; i<n; i++)
    {
        V.push_back(i);
    }

    P(0);

    
    return 0;
}


