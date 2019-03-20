/* Dejwo to ziomal Â®Â© */

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
#define PI 3.14159265


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    
    int arr[ n ];
    ll all = 0;
    
    FOR0( n ) {
        cin >> arr[ i ];
        all += arr[ i ];
    }
    
    int p = 0, k = 0;
    ll akt = arr[ p ], ans = 0;
    
    while ( p < n ) {
        while( akt + arr[ (k + 1) % n ] <= all - akt - arr[ (k + 1) % n ] ){
            k ++;
            akt += arr[ k % n ];
        }
        ans = max( min(akt, all - akt), ans );
        akt -= arr[ p ];
        p ++;
    }
    
    cout << ans << "\n";
    return 0;
}
