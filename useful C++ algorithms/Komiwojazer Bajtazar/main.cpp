// Compiled with: g++ -Wall -std=c++14 -pthread
/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>

using namespace std;
#define SIZE 30042

vector<int>G[SIZE];

//ojcowie
//pre i post
//poziomy

int pre[SIZE], post[SIZE], level[SIZE];
int tablicaOjcow[20][SIZE];
bool odw[SIZE];

int czas = 0;
void DFS(int v)
{
    assert(v > 0);
    odw[v] = true;
    pre[v] = ++czas;
    for(auto w: G[v])
    {
        assert(w > 0);
        if(!odw[w])
        {
            tablicaOjcow[0][w] = v;
            level[w] = level[v] + 1;
            DFS(w);
        }
    }
    
    post[v] = ++czas;
    assert(pre[v] < post[v]);
}

//skip pointers

int k_tyOjciec(int v,int k)
{
    int start = 1;
    while(k > 0)
    {
        assert(start - 1 < 20);
        assert(v < SIZE);
        if(k%2)v = tablicaOjcow[start-1][v];  //zapalony bit
        start ++;
        k /= 2;
    }
    assert(v > 0);
    return v;
}

bool Czy_jest_przodkiem(int syn, int ojciec)
{
    assert(syn > 0 and ojciec > 0);
    int wchodze_do_Ojca = pre[ojciec], wychodze_z_ojca = post[ojciec];
    int wchodze_do_Syna = pre[syn], wychodze_z_syna = post[syn];
    
    if (wchodze_do_Syna >= wchodze_do_Ojca and wychodze_z_syna <= wychodze_z_ojca) return true;
    
    return false;
}

int LCA(int a, int b)
{
    assert(a > 0 and b > 0);
    int poziomA = level[a];
    int poziomB = level[b];
    
    int start = 0, sprawdzam_ojca = 0, poziom = 0, wierzcholek = 0, pozW = 0, drugi = 0;;
    
    if(poziomA < poziomB)
    {
        poziom = poziomA;
        wierzcholek = a;
        pozW = poziomA;
        drugi = b;
    }
    else
    {
        poziom = poziomB;
        wierzcholek = b;
        pozW = poziomB;
        drugi = a;
    }
    
    while (poziom >= start)
    {   assert(poziom >= 0 and start >= 0);
        int m = (start + poziom) / 2;
        sprawdzam_ojca = k_tyOjciec(wierzcholek, pozW - m);
        if(Czy_jest_przodkiem(drugi, sprawdzam_ojca)) start = m + 1;
        else poziom = m - 1;
    }
    
    return k_tyOjciec(wierzcholek, pozW - (poziom + start) / 2);
}


int ObliczDroge(int a, int b)
{
    assert(a > 0 and b > 0);
    int WspolnyPrzodek = LCA(a, b);
    
    int drogaA = abs(level[a] - level[WspolnyPrzodek]);
    int drogaB = abs(level[b] - level[WspolnyPrzodek]);
    
    int wynik =  drogaA + drogaB;
    assert(wynik >= 0);
    return wynik;
}


int main()
{
    ios_base::sync_with_stdio(0);
    int n; cin>>n;
    for(int i=0; i<n-1; i++)
    {
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int m;
    cin>>m;
    int miasta[m];
    for(int i=0; i<m; i++)cin>>miasta[i];
    
    DFS(1);
    
    for(int i=1; i < 20; i++) ///<- tablica przodkow
    {
        for(int j=1; j <= n; j++)
            tablicaOjcow[i][j] = tablicaOjcow[i-1][tablicaOjcow[i-1][j]];
    }
    
    int aktualne  = 1;
    long long ile = 0;
    for(int i=0; i<m; i++)
    {
        int cel = miasta[i];
        if(Czy_jest_przodkiem(cel, aktualne) or Czy_jest_przodkiem(aktualne, cel))
        {
            int roznica = abs(level[aktualne] - level[cel]);
            ile += roznica;
            //cout<<aktualne<<" -->>  "<<cel<<" :  "<< roznica<<endl;
        }
        else
        {
            //   cout<<aktualne<<"  -->>  "<<cel<<" :  "<< ObliczDroge(aktualne, cel)<<endl;
            ile += ObliczDroge(aktualne, cel);
        }
        aktualne = cel;
    }
    
    cout<<ile<<endl;
    return 0;
    }
