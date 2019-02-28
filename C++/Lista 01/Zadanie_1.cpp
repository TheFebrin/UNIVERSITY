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

void Zadanie_1(){
    clog << "Podaj 3 boki trojkata: ";
    double a, b, c;
    cin >> a >> b >> c;
    if( a <= 0 or b <= 0 or c <= 0){
        clog << "Bok musi miec dodatnia dlugosc! \n";
        return;
    }

    assert( a > 0 and b > 0 and c > 0);

    if( c >= a + b or a >= c + b or b >= a + c){
        clog << "Warunek budowy trojkata niespelniony! \n";
        return;
    }
    
    clog << endl;
    cout << "Pole trojkata wynosi: ";
    double p = (a + b + c) / 2;
    cout << setprecision(3) << sqrt(p * (p - a) * (p - b) * (p - c)) << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    Zadanie_1();
    
    // g++ Lista1.cpp -o lista
    // ./lista <boki> boki.out

    return 0;
}
