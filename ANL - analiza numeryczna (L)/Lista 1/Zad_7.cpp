/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define SIZE 1000000
ll n,m,t,q,p,r,wynik;


float calka(int n){
    if(n == 0) return log(6.0f / 5.0f);
    return 1.0f / n - 5.0f * calka(n-1);
}
int main()
{
    for(int i = 0; i <= 20; i++) cout<<i<<" "<<calka(i)<<endl;
    return 0;
}

