//Dawid to ziomal
#include <bits/stdc++.h>
using namespace std;

int minimum3(int a, int b, int c)
{
    int wynik=min(a,b);
    wynik=min(wynik,c);
    return wynik;
}
int main()  //   ---------nie zrobione
{
    ios_base::sync_with_stdio(0);
    int n;
    cin>>n;
    int tab[n][3];
    int dp[2][2];
    for(int i=0;i<n;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        tab[i][0]=a;
        tab[i][1]=b;
        tab[i][2]=c;
    }
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<3;j++)
        {
            int min3=INT_MAX;
            for(int k=0;k<3;k++)
            {
                if(k!=j) min3=min(min3,dp[i-1][k]);
            }
            dp[i][j]+=min3;
        }
    }
    cout<<minimum3(dp[n-1][0],dp[n-1][1],dp[n-1][2])<<"\n";
    
    return 0;
}




