#include <bits/stdc++.h>

using namespace std;


string ONP(string s)
{
    queue < string > Q;
    string num;
    if(s[0] >= '0' and s[0] <= '9') num += s[0];

    for(int i = 0; i < (int)s.size(); i ++)
    {
        bool b1 = i - 1 >= 0 and s[i - 1] >= '0' and s[i - 1] <= '9';
        bool b2 = s[i] >= '0' and s[i] <= '9';
        if(b1 and b2)
        {
            num += s[i];
            continue;
        }
        else if(b1)
        {
            Q.push(num);
            num = "";
            continue;
        }
        char a = s[i];
        string x;
        x += s[i];

        if(a == '(') Q.push(x);
        if(a == ')') Q.push(x);
        if(a == '+') Q.push(x);
        if(a == '-') Q.push(x);
        if(a == '/') Q.push(x);
        if(a == '*') Q.push(x);
        if(a >= 'a' and a <= 'z') Q.push(x);
    }

    map < char, int > prec;
    prec['*'] = 3;
    prec['/'] = 3;
    prec['+'] = 2;
    prec['-'] = 2;
    prec['('] = 1;

    string ans;
    stack < string > S;
    while(!Q.empty())
    {
        string act = Q.front();
        Q.pop();
        
        bool b1 = (act >= "0" and act <= "9");
        bool b2 = (act.size() == 1 and act >= "a" and act <= "z");

        if(b1 or b2 or act.size() > 1) 
            ans += act;
        else if(act == "(")
            S.push("(");
        else if(act == ")")
        {
            assert(!S.empty());
            string top = S.top();
            S.pop();
            while(top != "(")
            {
                ans += top;
                top = S.top();
                S.pop();
            }
        }
        else
        {
            while(!S.empty() and prec[act[0]] <= prec[S.top()[0]])
            {
                ans += S.top();
                S.pop();
            }
            S.push(act);
        }
    }
    while(!S.empty())
    {
        ans += S.top();
        S.pop();
    }
    return ans;
}


int main()
{
    string infix = "a+b*c/d";
    string infix1 = "123 + 2 * 3 / (4 - 5) * 6 / a + b + c * d";
    string onp =  ONP(infix1);
    for(auto a: onp) cout << a << " ";
    cout << endl;

    return 0;
}