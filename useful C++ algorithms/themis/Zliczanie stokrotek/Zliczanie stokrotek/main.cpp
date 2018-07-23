#include <bits/stdc++.h>
using namespace std;



int maxZtrzech(int a, int b, int c)
{
    int wynik=max(a,b);
    wynik=max(wynik,c);
    return wynik;
}


int main()
{
    ios_base::sync_with_stdio(0);
    
    int n,m;
    cin>>n>>m;
    long long droga[n][m];
    int dp[n][m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            droga[i][j]=0;
        }
    
    droga[0][0]=1;
    
    for(int i=0;i<n;i++)
    {
        for(int j=0; j<m; j++)
        {
            cin>>dp[i][j];
        }
    }
    
    
    for(int i=0;i<n;i++)
    {
        int max1=-1;
        int max2=-1;
        int max3=-1;
        for(int j=0; j<m; j++)
        {
            if(j>0)max1=dp[i][j-1];
            if(j>0 and i>0) max2=dp[i-1][j-1];
            if(i>0) max3=dp[i-1][j];
            
            int maks=maxZtrzech(max1,max2,max3);
            if(max1==maks and j>0)droga[i][j]+=droga[i][j-1];
            if(max2==maks and i>0 and j>0)droga[i][j]+=droga[i-1][j-1];
            if(max3==maks and i>0)droga[i][j]+=droga[i-1][j];
            
            dp[i][j]+=maks;
        }
    }
    cout<<droga[n-1][m-1]<<"\n";
    
    
    string jakDojsc;
    //D, P ,C
    
    pair < int , int > akt;
    akt={n-1, m-1};
    
    while(akt.first != 0 or akt.second!=0)
    {
        int max1=-1000000;
        int max2=-1000000;
        int max3=-1000000;
        if(akt.first>0)max1=dp[akt.first-1][akt.second];
        if(akt.first>0 and akt.second>0)max2=dp[akt.first-1][akt.second-1];
        if(akt.second>0)max3=dp[akt.first][akt.second-1];
        
        int najwieksza=maxZtrzech(max1,max2,max3);
        
        if(najwieksza==max2){akt.first--; akt.second--; jakDojsc+='C';}
        else if(najwieksza==max1){akt.first--; jakDojsc+='D';}
        else if(najwieksza==max3){akt.second--; jakDojsc+='P';}
        
    }
    
    reverse(jakDojsc.begin(), jakDojsc.end());
    cout<<jakDojsc<<"\n";
    
    /*
     -1 -1 -1
     -1 9 -1
     -1 -1 -1
     PDC
     
     */
    
    return 0;
}




