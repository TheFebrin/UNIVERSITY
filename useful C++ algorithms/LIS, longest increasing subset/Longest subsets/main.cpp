/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;

vector <int> v;

int search(vector<int>v, int p, int k, int x)
{
    while(k-p > 1)
    {
        int m = (p+k)/2;
        if(v[m] >= x) k = m;
        else p = m;
    }
    return k;
}

int LIS()
{
    if(v.size() == 0)return 0;
    
    int dl = 1;
    vector <int> ogon (v.size());
    ogon[0] = v[0];
    
    for(int i=1; i<v.size(); i++)
    {
        if(v[i] < ogon[0]) ogon[0] = v[i];
        else
            if(v[i] > ogon[dl-1]) ogon[dl++] = v[i];
            else
                ogon[search(ogon, -1, dl, v[i])] = v[i];
        
    }
    return dl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    
    int T, N;
    cin>>T;
    
    for(int j=0; j<T; j++)
    {
        cin>>N;
        v.clear();
        for(int i=0; i<N; i++)
        {
            int a; cin>>a;
            v.push_back(a);
        }
        cout<<LIS()<<"\n";
    }
    
    return 0;
}







/*  to stare
vector<int>V;
set <pair<int,int>> S;

int main()
{
    ios_base::sync_with_stdio(0);
    int n; cin>>n;
    for(int i=0; i<n; i++)
    {
        int a; cin>>a;
        V.push_back(a);
    }
    
    S.emplace(0,0);
    for(auto v:V)
    {
        auto s = S.lower_bound({v+1,0});
        auto t = prev(s);
        if( s != S.end() and (*s).first == v) S.erase(s);
        S.emplace(v,(*t).second+1);
    }
    
    int maxx=0;
    for(auto s:S)maxx=max(maxx, s.second);
    
    cout<<"LIS: "<<maxx<<"\n";
    
    
    
    
    return 0;
}

 moze to jest dobrze:
 
 S.insert({0,0});
 for(auto v:V)
 {
 auto s = S.lower_bound({v,0});
 auto t = prev(s);
 if( s != S.end() and (*s).first == v) S.erase(s);
 S.emplace(v,(*t).second+1);
 if(v <= (*s).first) S.erase(s);
 }
 
 */
