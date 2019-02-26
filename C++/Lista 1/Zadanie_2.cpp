/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector < int > vi;
typedef pair <int, int> pi;
typedef vector <pair< int , int > > vpi;

#define pb push_back
#define FOR0(n) for(int i = 0; i < n; i++)
#define FOR0j(n) for(int j = 0; j < n; j++)
#define FOR1(n) for(int i = 1; i <= n; i++)
#define FOR1j(n) for(int j = 1; j <= n; j++)
#define FOR_REV(n) for(int i = n - 1; i >= 0 ; i--)
#define FOR_REVj(n) for(int j = n - 1; j >= 0 ; j--)
#define SIZE 3 * 1e5 + 42
#define MAX 1e6 + 42
#define MOD 1e9 + 7


void Zadanie_2(){
    clog << "Podaj pole figury: ";
    double pole;
    cin >> pole;

    if( pole < 0 ){
        clog << "Podano ujemne pole! \n";
        return;
    }

    assert( pole >= 0 );

    clog << endl;
    cout << "Promien kola o takim samym polu powierzchni wynosi: ";
    cout << sqrt( pole / M_PI ) << endl;
}



int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // snitch nigga thats that shit I dont like
    
    Zadanie_2();
    
    // g++ Lista1.cpp -o lista
    // ./lista <promien.in> promien.out

    return 0;
}
