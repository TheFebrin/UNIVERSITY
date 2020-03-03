/* Dejwo to ziomal Â®Â© */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;
typedef vector <ll> vl;
typedef pair <int, int> pi;
typedef pair <ll, ll> pl;
typedef tuple <int, int, int> ti;
typedef vector < pl > vpl;
typedef vector < pi > vpi;
typedef vector < ti > vti;

//double t = clock();
//cout << (clock() - t) / CLOCKS_PER_SEC <<endl;
bool debug = false;
#define deb if(debug)
#define pb push_back
#define FOR0(n) for(int i = 0; i < n; i++)
#define FOR0j(n) for(int j = 0; j < n; j++)
#define FOR1(n) for(int i = 1; i <= n; i++)
#define FOR1j(n) for(int j = 1; j <= n; j++)
#define FOR_REV(n) for(int i = n - 1; i >= 0 ; i--)
#define FOR_REVj(n) for(int j = n - 1; j >= 0 ; j--)
#define SIZE (3 * 1e5 + 42)
#define MAX (1000000 + 42)
#define MOD (1000000000 + 7)
#define PI 3.14159265


vi G[ int (MAX) ];
int dp[ int(MAX) ][ 2 ];
bool visited[ int(MAX) ];


void DFS1( int v ){
    visited[ v ] = true;
    for(auto w: G[ v ])
        if( ! visited[ w ] ) {
            DFS1( w );
            break;
        }
}

void DFS( int v ){
    vi ch_val;
    bool leaf = true;
    visited[ v ] = true;

    for(auto w : G [ v ]){
        if( !visited[ w ] ) {
            leaf = false;
            DFS( w );

            ch_val.pb( dp[ w ][ 1 ] - dp[ w ][ 0 ]);
            dp[ v ][ 0 ] += dp[ w ][ 0 ];
            dp[ v ][ 1 ] += dp[ w ][ 0 ];
        }
    }

    if( leaf ){
        dp[ v ][ 0 ] ++;
    }
    else{
        assert( ch_val.size() );
        sort(ch_val.begin(), ch_val.end());
        dp[ v ][ 1 ] += min(0, ch_val[ 0 ]);
        if( ch_val.size() == 1 ) dp[ v ][ 0 ] += min({1, ch_val[ 0 ] + 1});
        if( ch_val.size() >= 2 ) dp[ v ][ 0 ] += min({1, ch_val[ 0 ] + 1, ch_val[ 0 ] + ch_val[ 1 ] + 1 });
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // freopen("input.in","r",stdin);
    // freopen("output.txt","w",stdout);

    int n;
    cin >> n;

    FOR1( n - 1 ){
        int a, b;
        cin >> a >> b;
        G[ a ].pb( b );
        G[ b ].pb( a );
    }

    //FOR1( n ) cout << i << " -> " << dp[ i ][ 0 ] << " " << dp[ i ][ 1 ] << endl;

    int leaf = 0;
    FOR1( n ) if( G[ i ].size() == 1 ){
        leaf = i;
        break;
    }

//    srand(time(NULL));
//    DFS( rand() % n + 1 );

    DFS( 1 );

//    int ans = 1;
//    DFS( leaf );

//    FOR1( n ){
//        if( !visited[ i ] ) {
//            DFS( i );
//            ans ++;
//        }
//    }

    cout << (dp[ 1 ][ 0 ]) << endl;
   // cout << 1 << endl;

    return 0;
}

/*
12
1 3
2 3
3 12
12 6
6 5
6 4
12 11
8 11
7 8
9 11
10 11


7
1 2
1 3
2 4
2 5
3 6
3 7

 */
