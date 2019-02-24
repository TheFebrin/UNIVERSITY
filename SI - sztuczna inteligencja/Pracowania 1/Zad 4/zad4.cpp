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


int solve(string s, int D){

    int n = (int)s.size();

    vi pref;
    pref.assign(n, 0);

    if( s[ 0 ] == '1' ) pref[ 0 ] = 1;
    FOR1( n - 1 ){
        pref[ i ] = pref[ i - 1 ];
        pref[ i ] += s[ i ] == '1';
    }

    int first_1 = 0, last_1 = n - 1;
    FOR0( n ){
        if( s[ i ] == '1'){
            first_1 = i;
            break;
        }
    }

    FOR_REV( n ){
        if(s[ i ] == '1'){
            last_1 = i;
            break;
        }
    }

//    for(auto a: pref) cout << a;
//    cout << endl;

    int ans = INT_MAX;
    while (first_1 + D - 1 < n and first_1 < last_1) {
        int ones_before = 0;
        if( first_1 > 0) ones_before = pref[ first_1 - 1];

        int ones_after = pref[ n - 1 ];
        if( last_1 > 0) ones_after -= pref[ first_1 + D - 1 ];

        int ones_in_range = pref[ first_1 + D - 1 ] - ones_before;

        int changes_need = ones_before + ones_after + D - ones_in_range;
        //cout << first_1 << " -> " << first_1 + D - 1<< " changes: " << changes_need << " b4: " << ones_before << " aft: " << ones_after << endl;
        ans = min(ans, changes_need);
        first_1 ++;
    }

    return ans;
}

void test(){
    string s1 = "0010001000";
    FOR_REV( 6 ) printf("%s D = %d  --> %d \n", s1.c_str(), i, solve(s1, i));

}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    test();
    
    string s;
    cin >> s;
    
    int D;
    cin >> D;
    
    cout << solve(s, D) << endl;

    return 0;
}
