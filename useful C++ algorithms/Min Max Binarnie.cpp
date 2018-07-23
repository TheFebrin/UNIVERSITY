#include<bits/stdc++.h>

using namespace std;

void MinMax(int t[20],int p,int k,int minimum,int maximum)
{
    if(p==k)
    {
        maximum=minimum=t[p];
    }
    else if(k-p==1)
    {
        if(t[k-1]>t[p])
        {
            maximum=t[k-1]; minimum=t[p];
        }
        else
        {
            maximum=t[p]; minimum=t[k-1];
        }
    }
    else
    {
        int max1,max2,min1,min2;
        int s=(p+k)/2;

        MinMax(t, p,  s,  min1,  max1);
        MinMax(t,s, k,  min2,  max2);

        if(min1<min2) minimum=min1;
        else minimum=min2;

        if(max1>max2) maximum=max1;
        else maximum=max2;
    }
}

int main()
{
   int t[20];
   int p=0;
   int k=20;
   int minimum=0;
   int maximum=0;
   for(int i=0;i<20;i++) t[i]=i;
   MinMax(t,p,k,minimum,maximum);

   cout<<"Max to: "<<maximum<<"  Min to: "<<minimum<<endl;


   return 0;
}

