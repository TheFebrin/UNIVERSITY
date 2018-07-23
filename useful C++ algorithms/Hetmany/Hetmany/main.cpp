/* Dejwo to ziomal */

#include <bits/stdc++.h>
using namespace std;
#define SIZE 1000000

vector < int > Wieze;

void wypisz(vector <int> Wieze)
{
    for(auto h:Wieze)cout<<h<<" ";
    cout<<"\n";
}

bool odw[SIZE];
int ilosc;
 void UstawieniaWiez(int k, int n, int ile)
{
    odw[k] = true;
    Wieze.push_back(k);
    if(ile == 1)
    {
        ilosc ++;
        wypisz(Wieze);
        odw[k] = false;
        return;
    }
    for(int i=1; i<=n; i++)
    {
        if(!odw[i])
        {
            UstawieniaWiez(i, n, ile-1);
            Wieze.pop_back();
        }
    }
    odw[k] = false;
}

/******************************************************* HETMANY  **********/

vector< int >Hetmany;

bool isFree(int i, int n)
{
    int pozI = (int)Hetmany.size()+1;
    int poz = 1;
    for(auto h:Hetmany)
    {
        if(h+poz == pozI + i or poz - h == pozI - i)return false;
        poz++;
    }
    return true;
}


bool odw2[SIZE];
int ilosc2;
void UstawieniaHetmanow(int k, int n)
{
    odw2[k] = true;
    Hetmany.push_back(k);

    if(Hetmany.size() == n)
    {
        ilosc2 ++;
        wypisz(Hetmany);
        odw2[k] = false;
        return;
    }
    for(int i=1; i<=n; i++)
    {
        if(!odw2[i] and isFree(i,n))
        {
            UstawieniaHetmanow(i, n);
            Hetmany.pop_back();
        }
    }
    odw2[k] = false;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n;
    cin>>n;
//    for(int i=1; i<=n; i++){
//        UstawieniaWiez(i, n, n);
//        for(int i=0 ; i<=n; i++)odw[i]=false;
//        Wieze.clear();
//    }
//    cout<<"\n"<<ilosc<<"\n\n";
    
    for(int i=1; i<=n; i++){
        UstawieniaHetmanow(i, n);
        for(int i=0 ; i<=n; i++)odw2[i]=false;
        if(!Hetmany.empty())Hetmany.clear();
    }
    cout<<"\n"<<ilosc2<<"\n";
    
    
    
    return 0;
}

