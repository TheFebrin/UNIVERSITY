/* Dejwo to ziomal ®© */
#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#pragma GCC option("arch=native","tune=native","no-zero-upper")
#pragma GCC target("avx")
#include <x86intrin.h>
#include <bits/stdc++.h>


using namespace std;

#define FOR(i,x,n) for(int i = x; i < n; i++)
#define pb push_back
typedef long long ll;
typedef vector < int > vi;
typedef vector < pair < int, int > > vpi;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

vector < vi > MAP(15, vi(15, 0));

void adjust_map(vector < vi > &M)
{
    vector < vi > Mcopy1 = M;
    unordered_set < int > del;
    // for(int k = M.size() - 1; k >= 0; k --)
    FOR(k, 0, M.size())
    {
        auto &v = M[k];
        vi tmp(15, -1);
        int idx = 14;
        int empty = 0;
        for(int i = 14; i >= 0 ; i --)
        {
            if(v[i] != -1)
            {
                tmp[idx] = v[i];
                idx --;
            }
            else empty ++;
        }
        v = tmp;
        if(empty == 15) del.insert(k);
    }
    vector < vi > Mcopy = M;

    vector < vi > new_M;
    int sizeb4 = M.size();
    FOR(i, 0, M.size())
    {
        if(del.find(i) == del.end())
            new_M.pb(M[i]);
    }
    M = new_M;
    assert(M.size() == sizeb4 - del.size());
}

vector < vpi > get_moves(vector < vi > &M)
{
    vector < vector < int > > visited(15, vector < int >(15, 0));
    vector < vpi > ans;

    int x = 1;
    FOR(i, 0, M.size())
    {
        FOR(j, 0, M[i].size())
        {
            if(visited[i][j] == 0 and M[i][j] != -1)
            {
                bool b1 = i + 1 < M.size() and M[i + 1][j] == M[i][j];
                bool b2 = i - 1 >= 0 and M[i - 1][j] == M[i][j];
                bool b3 = j + 1 < M[i].size() and M[i][j + 1] == M[i][j];
                bool b4 = j - 1 >= 0 and M[i][j - 1] == M[i][j];

                if(!(b1 or b2 or b3 or b4)) continue;

                queue < pair < int, int > > Q;
                Q.push({i , j});
                visited[i][j] = x;
                int color = M[i][j];

                vpi actual_ting;

                while(!Q.empty())
                {
                    auto act = Q.front();
                    Q.pop();
                    actual_ting.pb(act);
                    FOR(k, 0, 4)
                    {
                        int new_x = get<0>(act) + dx[k];
                        int new_y = get<1>(act) + dy[k];
                        if (new_x >= 0 and new_x < M.size() and new_y >= 0 and new_y < M[i].size() \
                            and visited[new_x][new_y] == 0 and M[new_x][new_y] == color)
                        {
                            visited[new_x][new_y] = x;
                            Q.push({new_x, new_y});
                        }
                    }
                }
                x ++;
                ans.pb(actual_ting);
            }
        }
    }
    return ans;
}


void BFS(vector < vi > M)
{
    double start_time = clock();
    double MAX_TIME = 19;

    tuple <ll, vpi, vector < vi >> State = {0, vpi(), M};
    priority_queue < tuple <ll, vpi, vector < vi > > > P;
    P.push(State);

    int states_visited = 0;
    int best_board = 0;
    vpi best_history;
    vector < vector < vi > > map_history;

    while(!P.empty() and (clock() - start_time) / CLOCKS_PER_SEC <= MAX_TIME)
    {
        auto act = P.top();
        P.pop();
        states_visited ++;

        ll score = get<0>(act);

        // cerr << "Score: " << score << endl;

        vpi history = get<1>(act);

        // cerr << "His: " << history.size() << endl;

        vector < vi > act_map = get<2>(act);

        if(act_map.size() == 0)
        {
            cerr << "GG! " << endl;
            cerr << "Visited: " << states_visited << " states." << endl;
            cerr << "Best board: " << best_board << endl;
            cerr << "Time: " << (clock() - start_time) / CLOCKS_PER_SEC << endl;
            cerr << "Long: " << best_history.size() << endl;

            for(auto [x, y]: history)
            {
                cout << x << " " << y << endl;
            }
            return;
        }

        // cerr << "Map size: " << act_map.size() << endl;

        vector < vpi > moves = get_moves(act_map);

        // cerr << "Moves size: " << moves.size() << endl;

        if(score >= best_board)
        {
            best_board = score;
            best_history = history;
        }

        for(auto V: moves)
        {
            auto new_map = act_map;
            for(auto [x, y]: V) new_map[x][y] = -1;
            adjust_map(new_map);
            vpi new_history = history;
            new_history.pb({V[0].first, act_map[V[0].first].size() - 1 - V[0].second});

            int bonus = 0;
            FOR(i, 0, new_map.size())
            {
                FOR(j, 0, new_map[0].size())
                {
                    FOR(k, 0, 4)
                    {
                        if(i + dx[k] >= 0 and i + dx[k] < new_map.size() \
                            and j + dy[k] >= 0 and j + dy[k] < new_map[i].size() \
                            and new_map[i + dx[k]][j + dy[k]] == new_map[i][j])
                        {
                            bonus += 4;
                        }
                    }
                }
            }
            P.push({score + V.size() * V.size() + bonus * bonus, new_history, new_map});
        }
    }
    cerr << "Visited: " << states_visited << " states." << endl;
    cerr << "Best board: " << best_board << endl;
    cerr << "Time: " << (clock() - start_time) / CLOCKS_PER_SEC << endl;
    cerr << "Long: " << best_history.size() << endl;

    // for(auto [x, y]: best_history)
    // {
    //     cerr << "(" << x << " " << y << ")" << endl;
    // }

    for(auto [x, y]: best_history)
    {
        cout << x << " " << y << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (1) {
        FOR(i, 0, 15) {
            FOR(j, 0, 15) {
                cin >> MAP[j][i]; cin.ignore();
            }
        }


        FOR(i, 0, 15)
        {
            FOR(j, 0, 15) cerr << MAP[i][j] << " ";
            cerr << endl;
        }

        cerr << endl << endl;

        BFS(MAP);
    }
}
