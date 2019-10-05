/* Dejwo to ziomal ®© */

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
typedef complex < double > cd;
typedef vector < cd > vcd;

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


void fft(vcd &V, bool invert) {
    int n = (int)V.size();

    int j = 0;
    FOR1( n - 1 ) {
        int bit = n >> 1;
        while( j & bit ){
          j ^= bit;
          bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(V[ i ], V[ j ]);
    }


    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len;
        if( invert ) ang *= -1;

        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w( 1 );
            for (int j = 0; j < len / 2; j++) {
                cd u = V[ i + j ], v = V[ i + j + len / 2 ] * w;
                V[ i + j ] = u + v;
                V[ i + j + len / 2 ] = u - v;
                w *= wlen;
            }
        }
    }

    if( invert ) {
        for(auto & x : V){
            x /= n;
        }
    }
}

vi multiply(vi A, vi B) {
    vcd Va(A.begin(), A.end());
    vcd Vb(B.begin(), B.end());
    int n = 1;

    while (n < (int)A.size() + (int)B.size())
      n <<= 1;

    Va.resize(n);
    Vb.resize(n);

    fft(Va, false);
    fft(Vb, false);

    FOR0( n ) Va[i] *= Vb[i];

    fft(Va, true);

    vi res( n );
    FOR0( n ) res[ i ] = round(Va[ i ].real());
    return res;
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

    int arr[ n ];
    vi T;
    unordered_map < int, int > cnt;
    FOR0( n ) {
      cin >> arr[ i ];
      cnt[ arr[ i ] ] ++;
    }
    int mx = *max_element( arr, arr + n );

    bool fft_arr[ mx + 1 ];
    FOR0( mx + 1 ) fft_arr[ i ] = 0;
    FOR0( n ) fft_arr[ arr[ i ] ] = 1;
    FOR1( mx ) T.pb( fft_arr[ i ] );

    reverse( T.begin(), T.end() );
    auto ans = multiply(T, T);

    // cout << endl;
    // for(auto t: ans) cout << t << " ";
    // cout << endl << endl;

    int no = mx * 2;
    for(auto t: ans){
      if( t != 0 ) cnt[ no ] += t / 2;
      no --;
    }

    vpi final;
    for( auto m: cnt ) if( m.second ) final.pb( {m.first, m.second} );
    final.pb( {0, 1} );
    sort( final.begin(), final.end() );

    for(auto f: final) cout << f.first << " " << f.second << "\n";

    return 0;
}
