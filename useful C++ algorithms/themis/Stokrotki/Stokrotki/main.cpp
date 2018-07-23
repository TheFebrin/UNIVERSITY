//Dawid to ziomal

#include <bits/stdc++.h>
using namespace std;


int main()
{
    ios_base::sync_with_stdio(0);
    int c; //ilosc zestawow
    cin>>c;
    for(int i=0;i<c;i++)
    {
        int n,m;
        cin>>n>>m;
        int dp[n][m];
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<m;k++)
            {
                cin>>dp[j][k];
            }
            //wiersz wczytany //
        }
        
        for(int k=1;k<m;k++)
        {
            for(int l=0;l<n;l++) // dodaje min z poprzedniej
            {
                int minimum=INT_MAX;
                for(int o=l-1;o<=l+1;o++)
                {   if(o<0 or o>=n)continue;
                     minimum=min(minimum,dp[o][k-1]);
                }
                dp[l][k]+=minimum;
            }
        }
        /*
        cout<<"\n\n";
        for(int ii=0;ii<n;ii++)
        {
            for(int jj=0; jj<m;jj++)
            {
                cout<<dp[ii][jj]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n\n";
        */
        int wynik=INT_MAX;
        for(int k=0;k<n;k++)
        {
            wynik=min(wynik,dp[k][m-1]);
        }
        cout<<wynik<<"\n";
    }
    
    return 0;
}

