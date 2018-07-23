#include <bits/stdc++.h>
using namespace std;
#define INF 1000000

int main()
{
    ios_base::sync_with_stdio(0);
    
    
    int n;
    int m;
    cin>>n>>m;
    vector <pair <int, bool> > G[n+1];
    
    for(int i=1; i<=m; i++)
    {
        int a,b;
        cin>>a>>b;
        G[a].push_back({b,true});
        G[b].push_back({a,false});
    }
    
    queue < int > Q[n+1];
    
    int wKtorejW[n+1]; for(int i=0; i<n+1; i++)wKtorejW[i] = INF;
    
    
    Q[1].push(1);
    
    for(int i=1; i<=n; i++)
        while(!Q[i].empty())
        {
            int akt = Q[i].front();
            Q[i].pop();
            
            if(akt == n)
            {
                cout<<wKtorejW[akt] - 1<<"\n";
                return 0;
            }
            
            for(auto w:G[akt])
            {
                if(w.second == true)
                {
                    if(wKtorejW[w.first] > i)
                    {
                        wKtorejW[w.first] = i;
                        Q[i].push(w.first);
                    }
                    
                }
                else
                {
                    if(wKtorejW[w.first] > i)
                    {
                        wKtorejW[w.first] = i+1;
                        Q[i+1].push(w.first);
                    }
                }
            }
            
        }
    
    
    
    
    
    return 0;
}


