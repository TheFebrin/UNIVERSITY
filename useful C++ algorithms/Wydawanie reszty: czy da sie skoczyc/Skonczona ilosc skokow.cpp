#include "bits/stdc++.h"
using namespace std;

int main()
{
int n;//pola
int k;//liczb

cin>>n>>k;

char tab[n];
tab[0]='X';

for(int i=1;i<n;i++)tab[i]='-';

int tmp;
int ruchy[k];

for(int i=0;i<k;i++)
{
  cin>>tmp;
  ruchy[i]=tmp;
}

for(int j=0;j<k;j++)
{
    for(int i=n-1;i>=0;i--) // leci po wszystkich n
  {
    if(i+ruchy[j]<n and tab[i]=='X') //<=
    {
      tab[i+ruchy[j]]='X'; //stawiam nowe x
    }
  }
}

for(int i=0;i<n;i++)cout<<tab[i];
cout<<endl;
  return 0;
}



// 20 3
// 4 5 7
