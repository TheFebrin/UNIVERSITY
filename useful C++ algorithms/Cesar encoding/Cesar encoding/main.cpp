//
//  main.cpp
//  Cesar encoding
//
//  Created by Dawid on 23/12/2017.
//  Copyright © 2017 Dawid. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;

    
    string code(string x, int k)
    {
        k %= 26;
        for(int i=0;i<x.size();i++)
        {
            x[i]=((x[i]+k));
        }
        
        return x;
    }
    
    string encode(string x,int k)
    {
        return code(x, k);
    }

    int main()
    {
        string n;
        cin>>n;
        int k;
        cin>>k;
        cout<<encode(n,k)<<endl;
        
    }

