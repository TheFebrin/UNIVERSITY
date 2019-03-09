/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector < int > vi;
typedef pair <int, int> pi;
typedef vector < pair< int , int > > vpi;

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
#define PI 3.14159265


 const vector < pair<int, string> > rzym = {
        {1000, "M"},
        {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"},
        {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

string bin2rzym( int x ){
    string ans;
    while( x > 0 ){
        int p = 0;
        while( x < rzym[ p ].first ) p ++;
        ans += rzym[ p ].second;
        x -= rzym[ p ].first;
    }
    return ans;
}

bool check( string s ){
    for(auto c: s) if( !isdigit(c) ){
        clog << s << " is not a valid number! \n";
        return false;
    }

    int number = stoi( s );
    if( number < 1 ){
        clog << s << " is less than 1! \n";
        return false;
    }

    if( number > 3999 ){
        clog << s << " is greater than 3999! \n";
        return false;
    }

    if( s[ 0 ] == '0' ){
        clog << s << " is not a valid number! \n";
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{

    cout << "You have entered " << argc - 1 << " numbers:" << "\n\n";

    vi candidates;
    FOR1( argc - 1 ) if( check( argv[ i ] ) ) candidates.pb( stoi( argv[ i ] ) );

    cout << "\n\nYour numbers in Roman system are: \n";
    for(auto c: candidates ) cout << c << " -> " << bin2rzym( c ) << endl;

    return 0;
}
