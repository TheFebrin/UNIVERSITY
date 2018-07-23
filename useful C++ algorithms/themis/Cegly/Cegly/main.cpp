//Dawid to ziomal

#include <bits/stdc++.h>
using namespace std;

#define SIZE 3001
#define inf 10000

int main()
{
    ios_base::sync_with_stdio(0);
    
    int n;
    cin>>n;
    int cegly[n];
    for(int i=0;i<n;i++)cin>>cegly[i];
    
    int tab[2][SIZE];
        for(int i=0 ; i<SIZE ; i++){
        tab[0][i]=inf;
        tab[1][i]=inf;
    }
    tab[0][0]=0;

    for(int c=0; c<n; c++)
    {
        for(int i=0; i<SIZE; i++)
        {
            if(tab[c%2][i] != inf)
            {
                int maks = max(abs(i-cegly[c]), tab[c%2][i]);
                tab[(c+1)%2][abs(i-cegly[c])] = min(tab[(c+1)%2][abs(i-cegly[c])], maks);
                if(i+cegly[c]<SIZE)
                {
                    maks = max(i+cegly[c], tab[c%2][i]);
                    tab[(c+1)%2][i+cegly[c]] = min(tab[(c+1)%2][i+cegly[c]], maks );
                }
            }
        }
         for(int j=0 ; j<SIZE; j++)tab[c%2][j]=inf;
    }
   
    int a = *min_element(tab[0], tab[0]+SIZE);
    int b = *min_element(tab[1], tab[1]+SIZE);
   //  cout<<"\n\n\n"<<a<<" "<<b<<"\n";
    
    cout<<min(a,b)<<"\n";
    
    return 0;
}

