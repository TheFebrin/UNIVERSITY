#include "bits/stdc++.h"
using namespace std;

int main()
{
int n;//pola
int k;//liczb

cin>>n>>k;

char tab[n];
tab[0]='X';

for(int i=1;i<n;i++)tab[i]='0';

int tmp;
int ruchy[k];

for(int i=0;i<k;i++)
{
  cin>>tmp;
  ruchy[i]=tmp;
}

for(int i=0;i<n;i++) // leci po wszystkich n
{
   for(int j=0;j<k;j++) //skacze
   {
     int skok=i-ruchy[j];//<-
     if(skok>=0 and tab[skok]=='X')
     {
       tab[i]='X';
     }
   }
  cout<<tab[i];
}
  cout << "\n";



  return 0;
}



// 20 3
// 4 5 7
