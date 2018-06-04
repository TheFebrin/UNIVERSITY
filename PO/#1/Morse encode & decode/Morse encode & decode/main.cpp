#include <bits/stdc++.h>
using namespace std;

map < char, string > M;
map < string, char > M2;
void encode(string S)
{
    cout<<"Encoded: ";
    for(auto s:S){
    s=toupper(s);
    cout<<M[s]<<" ";
    }
    cout<<"\n";
}

void decode(string S)
{
    cout<<"Decoded: ";
    string w;
    for(auto s:S)
    {
        if(s == '/')
        {
            cout<<" "; continue;
        }
        if(s == ' ')
        {
            cout<<M2[w];
            w="";
            continue;
        }
        w+=s;
    }
    cout<<"\n";
}

void fillMap();

int main()
{
    ios_base::sync_with_stdio(0);
    fillMap();
    string s;
    cout<<"Insert text: ";
    getline(cin, s);
    if(s[0] == '.' or s[0] == '-'){ s+=" "; decode(s);}
    else encode(s);
    
    return 0;
}

void fillMap()
{
    M['A'] =  ".-";     M2[".-"]='A';
    M['B'] =  "-...";   M2["-..."]='B';
    M['C'] =   "-.-.";  M2["-.-."]='C';
    M['D'] =   "-..";   M2["-.."]='D';
    M['E'] =   ".";     M2["."]='E';
    M['F'] =  "..-.";   M2["..-."]='F';
    M['G'] =  "--.";    M2["--."]='G';
    M['H'] =  "....";   M2["...."]='H';
    M['I'] =  "..";     M2[".."]='I';
    M['J'] =  ".---";   M2[".---"]='J';
    M['K'] =  "-.-";    M2["-.-"]='K';
    M['L'] =  ".-..";   M2[".-.."]='L';
    M['M'] =   "--";    M2["--"]='M';
    M['N'] =   "-.";    M2["-."]='N';
    M['O'] =   "---";   M2["---"]='O';
    M['P'] =   ".--.";  M2[".--."]='P';
    M['Q'] =   "--.-";  M2[ "--.-"]='Q';
    M['R'] =   ".-.";   M2[".-."]='R';
    M['S'] =   "...";   M2["..."]='S';
    M['T'] =   "-";     M2["-"]='T';
    M['U'] =   "..-";   M2["..-"]='U';
    M['V'] =   "...-";  M2["...-"]='V';
    M['W'] =   ".--";   M2[".--"]='W';
    M['X'] =   "-..-";  M2["-..-"]='X';
    M['Y'] =   "-.--";  M2["-.--"]='Y';
    M['Z'] =   "--..";  M2["--.."]='Z';
    M[' '] = "/";       M2["/"] = ' ';

}
