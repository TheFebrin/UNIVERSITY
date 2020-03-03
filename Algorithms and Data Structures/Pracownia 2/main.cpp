/* Dejwo to ziomal Â®Â© */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector < int > vi;
typedef pair <int, int> pi;
typedef vector < pair< int , int > > vpi;
typedef vector < tuple < int , int, int > > vti;

#define pb push_back
#define FOR0(n) for(int i = 0; i < n; i++)
#define FOR0j(n) for(int j = 0; j < n; j++)
#define FOR1(n) for(int i = 1; i <= n; i++)
#define FOR1j(n) for(int j = 1; j <= n; j++)
#define FOR_REV(n) for(int i = n - 1; i >= 0 ; i--)
#define FOR_REVj(n) for(int j = n - 1; j >= 0 ; j--)
#define SIZE 3 * 1e5 + 42
#define MAX 1000000 + 42
#define MOD 1000000000 + 7
#define PI 3.14159265


tuple < ll, int, int > heap[ 500000 ];
int sz;

void push( tuple < ll, int, int > T){
    heap[ ++ sz ] = T;
    int act = sz;
    
    while ( act > 1 and get<0>(heap[ act ]) > get<0>(heap[ act / 2 ])) {
        swap(heap[ act / 2 ], heap[ act ]);
        act /= 2;
    }
}

ll lewy = -1, prawy = -1;

tuple < ll, int, int > pop(){
    auto ret = heap[ 1 ];
    heap[ 1 ] = heap[ sz -- ];
    int act = 1;
    
    if(2 * act <= sz) lewy = get<0>(heap[ 2 * act ]);
    else lewy = -1;
    if(2 * act + 1 <= sz) prawy = get<0>(heap[ 2 * act + 1 ]);
    else prawy = -1;
    
    ll a = get<0>(heap[ act ]);
    
    while (act <= sz and (a < lewy or a < prawy)) {
        
        if( a < lewy and a < prawy ){
            if( lewy > prawy ){
                swap(heap[ act ], heap[ 2 * act ]);
                act = act * 2;
            }
            else{
                swap(heap[ act ], heap[ 2 * act + 1]);
                act = act * 2 + 1;
            }
            if(2 * act <= sz) lewy = get<0>(heap[ 2 * act ]);
            else lewy = -1;
            if(2 * act + 1 <= sz) prawy = get<0>(heap[ 2 * act + 1 ]);
            else prawy = -1;
            continue;
        }
        
        if( a < lewy ){
            swap(heap[ act ], heap[ 2 * act]);
            act = act * 2;
        }
        else if( a < prawy ){
            swap(heap[ act ], heap[ 2 * act + 1]);
            act = act * 2 + 1;
        }
        if(2 * act <= sz) lewy = get<0>(heap[ 2 * act ]);
        else lewy = -1;
        if(2 * act + 1 <= sz) prawy = get<0>(heap[ 2 * act + 1 ]);
        else prawy = -1;
    }
    
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    // freopen("input.in","r",stdin);
    // freopen("output.txt","w",stdout);
    
    
    int n, k;
    cin >> n >> k;
    
    push( {1LL * n * n,n,n} );
    
    ll last = 0;
    while (k > 0) {
        ll all, a, b;
        auto f = pop();
        tie(all, a, b) = f;
        
        if(all != last ){
            cout << all << "\n";
            k --;
        }
        last = all;
        
        if( b >= a){
            if(a > 1 and b == n) push( {(a - 1) * b, a - 1, b});
            if( b - 1 >= a ) push( {(b - 1) * a, a, b - 1} );
        }
        
    }
    
    
    return 0;
}
