/* Dejwo to ziomal ÃÂ®ÃÂ© */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector <int> vi;
typedef vector <ll> vl;
typedef pair <int, int> pi;
typedef pair <ll, ll> pl;
typedef tuple <int, int, int> ti;
typedef vector < pair< int , int> > vpi;
typedef vector < tuple <int , int, int> > vti;

#define pb push_back
#define FOR0(n) for(int i = 0; i < n; i++)
#define FOR0j(n) for(int j = 0; j < n; j++)
#define FOR1(n) for(int i = 1; i <= n; i++)
#define FOR1j(n) for(int j = 1; j <= n; j++)
#define FOR_REV(n) for(int i = n - 1; i >= 0 ; i--)
#define FOR_REVj(n) for(int j = n - 1; j >= 0 ; j--)
#define SIZE (3 * 1e5 + 42)
#define MAX 1000000 + 42
#define MOD (1000000000 + 7)
#define PI 3.14159265

typedef pair < double, double > pd;
vector < pd > V;

bool sort_x( pd A, pd B){
    return A.first < B.first;
}

bool sort_y( pd A, pd B){
    return A.second < B.second;
}


double dist(pd p1, pd p2){
    return sqrt( (p1.first - p2.first) * (p1.first - p2.first) +
                (p1.second - p2.second) * (p1.second - p2.second) );
}


pair < pd, pd > brute(int p, int k){
    double min_dist = DBL_MAX;
    pd A, B;
    for(int i = p; i <= k; i ++)
        for(int j = i + 1; j <= k; j ++){
            double D = dist(V[ i ], V[ j ]);
            if( D < min_dist ){
                min_dist = D;
                A = V[ i ];
                B = V[ j ];
            }
        }
    return {A, B};
}

pair < double, pair < pd, pd > > do_close(vector < pd > close, double d){
    sort( close.begin(), close.end(), sort_y);
    double min_dist = d;
    pd A, B;

    for(int i = 0; i < close.size(); i ++ ){
        for(int j = i + 1; j < close.size(); j ++ ){
            if( close[ j ].second - close[ i ].second >= min_dist ) break;
            double D = dist( close[ j ] , close[ i ] );
            if( D < min_dist ){
                min_dist = D;
                A = close[ i ];
                B = close[ j];
            }
        }
    }
    return {min_dist, {A,B}};
}

pair < double, pair < pd, pd > > MINN( double d1, double d2, pair < pd, pd > p1, pair < pd, pd > p2){
    if( d1 < d2 ) return {d1, p1};
    return {d2, p2};
}

pair < pd, pd > solve(int p, int k){
    int sz = k - p + 1;
    int m = (k + p) / 2;

    if( sz <= 3 ) return brute(p, k);

    pair < pd, pd > left = solve(p, m), right = solve(m + 1, k);
    double dist_left = dist(left.first, left.second);
    double dist_right = dist(right.first, right.second);

    double d = min( dist_left, dist_right );

    vector < pd > close;
    for( int i = p; i <= k; i ++ ){
        if( abs( V[ i ].first - V[ m ].first ) < d ){
            close.pb( V[ i ]);
        }
    }

    auto closest_strip = do_close(close, d);
    double strip_dist = closest_strip.first;

    auto best_of_left_right = MINN(dist_left, dist_right, left, right);

    //    cout << "l: " << dist_left << " r: " << dist_right << endl;
    //    cout << "best l and r: " << best_of_left_right.first << endl;
    //    cout << "strip: " << strip_dist << endl;

    if( best_of_left_right.first <= strip_dist ) return best_of_left_right.second;
    return closest_strip.second;
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

    FOR0( n ){
        double a,b;
        cin >> a >> b;
        V.pb( {a, b} );
    }

    sort(V.begin(), V.end());

    auto ans = solve(0, n - 1);
    cout << (int)ans.first.first << " " << (int)ans.first.second << endl;
    cout << (int)ans.second.first << " " << (int)ans.second.second << endl;

    return 0;
}
