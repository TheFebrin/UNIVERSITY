#include <bits/stdc++.h>
using namespace std;

map < char, string > M;
map < string, char > M2;

typedef struct node
{
    char litera;
    struct node *left;  ///<-
    struct node *right;
} Node;


Node* newNode(char lit)
{
    Node *nowy = (Node*)malloc(sizeof(Node));
    nowy->litera = lit;
    nowy->left = NULL;
    nowy->right = NULL;
    
    return nowy;
}
Node *root = newNode(' ');

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
    string w,wynik;
    for(auto s:S)
    {
        if(s == '/')
        {
            cout<<" "; continue;
        }
        if(s == ' ')
        {
            /* mam jakiegos string w w morsie i chce go zamienic na literke */
            Node *search = root;
            for(auto i:w)
            {
                if(i == '.') search = search->left;
                else search = search->right;
            }
            wynik+=search->litera;
            w="";
           continue;
        }
        w+=s;
    }
    cout<<wynik<<"\n";
}

void fillMap();
void BudujDrzewo();
int main()
{
    ios_base::sync_with_stdio(0);
    fillMap(); BudujDrzewo();
    string s;
    cout<<"Insert text: ";
    getline(cin, s);
    if(s[0] == '.' or s[0] == '-'){ s+=" "; decode(s);}
    else encode(s);
    
    return 0;
}
void BudujDrzewo()
{
    Node *A = newNode('A');
    Node *B = newNode('B');
    Node *C = newNode('C');
    Node *D = newNode('D');
    Node *E = newNode('E');
    Node *F = newNode('F');
    Node *G = newNode('G');
    Node *H = newNode('H');
    Node *I = newNode('I');
    Node *J = newNode('J');
    Node *K = newNode('K');
    Node *L = newNode('L');
    Node *M = newNode('M');
    Node *N = newNode('N');
    Node *O = newNode('O');
    Node *P = newNode('P');
    Node *Q = newNode('Q');
    Node *R = newNode('R');
    Node *S = newNode('S');
    Node *T = newNode('T');
    Node *U = newNode('U');
    Node *V = newNode('V');
    Node *W = newNode('W');
    Node *X = newNode('X');
    Node *Y = newNode('Y');
    Node *Z = newNode('Z');
    
    root->left = E;
    E->left = I;
    E->right = A;
    I->left = S;
    I->right = U;
    S->left = H;
    S->right = V;
    U->left = F;
    A->left = R;
    A->right = W;
    R->left = L;
    W->left = P;
    W->right = J;
    
    root->right = T;
    T->left = N;
    T->right = M;
    N->left = D;
    N->right = K;
    M->left = G;
    M->right = O;
    G->left = Z;
    G->right = Q;
    D->left = B;
    D->right = X;
    K->left = C;
    K->right = Y;
    
}

void fillMap() //M2 jest niepotrzebne
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

