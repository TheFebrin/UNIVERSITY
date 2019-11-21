#include <bits/stdc++.h>

using namespace std;


void ONP(string s)
{
    queue < char > Q;
    for(auto a: s)
    {
        if(a == '(') Q.push(a);
        if(a == ')') Q.push(a);
        if(a == '+') Q.push(a);
        if(a == '-') Q.push(a);
        if(a == '/') Q.push(a);
        if(a == '*') Q.push(a);
        if(a >= '0' and a <= '9') Q.push(a);
    }
}
int main()
{



    return 0;
}