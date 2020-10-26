/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector <int> vi;
typedef vector <ll> vl;
typedef pair <int, int> pi;
typedef pair <double, double> pd;
typedef pair <ll, ll> pl;
typedef tuple <int, int, int> ti;
typedef tuple <ll, ll, ll> tl;
typedef vector < pl > vpl;
typedef vector < pi > vpi;
typedef vector < pd > vpd;
typedef vector < ti > vti;

//double t = clock();
//cout << (clock() - t) / CLOCKS_PER_SEC <<endl;

#define deb if(debug)
#define pb push_back
#define FOR(i,x,n) for(int i = x; i < n; i++)
#define UNIQUE(x) sort((x).begin(),(x).end()),(x).erase(unique((x).begin(), (x).end()),(x.end()))
#define SORT(x) sort(x.begin(), x.end())
#define SIZE (3 * 100000 + 42)
#define MOD (1000000000 + 9)
#define DRZ (1<<21)
#define PI 3.14159265

bool debug = false;
#define EDGE(x, y) G[x].pb(y)

/*   <o/   */


double TIME_THRESHOLD = 0.1;
int _MAP[9][9] = {};
int _BIG_MAP[3][3] = {};

int _MAP_SIM[9][9] = {};
int _BIG_MAP_SIM[3][3] = {};

vpi valid_actions;

void copy_maps_to_sim()
{
    _BIG_MAP_SIM[0][0] = _BIG_MAP[0][0];
    _BIG_MAP_SIM[0][1] = _BIG_MAP[0][1];
    _BIG_MAP_SIM[0][2] = _BIG_MAP[0][2];
    _BIG_MAP_SIM[1][0] = _BIG_MAP[1][0];
    _BIG_MAP_SIM[1][1] = _BIG_MAP[1][1];
    _BIG_MAP_SIM[1][2] = _BIG_MAP[1][2];
    _BIG_MAP_SIM[2][0] = _BIG_MAP[2][0];
    _BIG_MAP_SIM[2][1] = _BIG_MAP[2][1];
    _BIG_MAP_SIM[2][2] = _BIG_MAP[2][2];

    _MAP_SIM[0][0] = _MAP[0][0];
    _MAP_SIM[0][1] = _MAP[0][1];
    _MAP_SIM[0][2] = _MAP[0][2];
    _MAP_SIM[0][3] = _MAP[0][3];
    _MAP_SIM[0][4] = _MAP[0][4];
    _MAP_SIM[0][5] = _MAP[0][5];
    _MAP_SIM[0][6] = _MAP[0][6];
    _MAP_SIM[0][7] = _MAP[0][7];
    _MAP_SIM[0][8] = _MAP[0][8];
    _MAP_SIM[1][0] = _MAP[1][0];
    _MAP_SIM[1][1] = _MAP[1][1];
    _MAP_SIM[1][2] = _MAP[1][2];
    _MAP_SIM[1][3] = _MAP[1][3];
    _MAP_SIM[1][4] = _MAP[1][4];
    _MAP_SIM[1][5] = _MAP[1][5];
    _MAP_SIM[1][6] = _MAP[1][6];
    _MAP_SIM[1][7] = _MAP[1][7];
    _MAP_SIM[1][8] = _MAP[1][8];
    _MAP_SIM[2][0] = _MAP[2][0];
    _MAP_SIM[2][1] = _MAP[2][1];
    _MAP_SIM[2][2] = _MAP[2][2];
    _MAP_SIM[2][3] = _MAP[2][3];
    _MAP_SIM[2][4] = _MAP[2][4];
    _MAP_SIM[2][5] = _MAP[2][5];
    _MAP_SIM[2][6] = _MAP[2][6];
    _MAP_SIM[2][7] = _MAP[2][7];
    _MAP_SIM[2][8] = _MAP[2][8];
    _MAP_SIM[3][0] = _MAP[3][0];
    _MAP_SIM[3][1] = _MAP[3][1];
    _MAP_SIM[3][2] = _MAP[3][2];
    _MAP_SIM[3][3] = _MAP[3][3];
    _MAP_SIM[3][4] = _MAP[3][4];
    _MAP_SIM[3][5] = _MAP[3][5];
    _MAP_SIM[3][6] = _MAP[3][6];
    _MAP_SIM[3][7] = _MAP[3][7];
    _MAP_SIM[3][8] = _MAP[3][8];
    _MAP_SIM[4][0] = _MAP[4][0];
    _MAP_SIM[4][1] = _MAP[4][1];
    _MAP_SIM[4][2] = _MAP[4][2];
    _MAP_SIM[4][3] = _MAP[4][3];
    _MAP_SIM[4][4] = _MAP[4][4];
    _MAP_SIM[4][5] = _MAP[4][5];
    _MAP_SIM[4][6] = _MAP[4][6];
    _MAP_SIM[4][7] = _MAP[4][7];
    _MAP_SIM[4][8] = _MAP[4][8];
    _MAP_SIM[5][0] = _MAP[5][0];
    _MAP_SIM[5][1] = _MAP[5][1];
    _MAP_SIM[5][2] = _MAP[5][2];
    _MAP_SIM[5][3] = _MAP[5][3];
    _MAP_SIM[5][4] = _MAP[5][4];
    _MAP_SIM[5][5] = _MAP[5][5];
    _MAP_SIM[5][6] = _MAP[5][6];
    _MAP_SIM[5][7] = _MAP[5][7];
    _MAP_SIM[5][8] = _MAP[5][8];
    _MAP_SIM[6][0] = _MAP[6][0];
    _MAP_SIM[6][1] = _MAP[6][1];
    _MAP_SIM[6][2] = _MAP[6][2];
    _MAP_SIM[6][3] = _MAP[6][3];
    _MAP_SIM[6][4] = _MAP[6][4];
    _MAP_SIM[6][5] = _MAP[6][5];
    _MAP_SIM[6][6] = _MAP[6][6];
    _MAP_SIM[6][7] = _MAP[6][7];
    _MAP_SIM[6][8] = _MAP[6][8];
    _MAP_SIM[7][0] = _MAP[7][0];
    _MAP_SIM[7][1] = _MAP[7][1];
    _MAP_SIM[7][2] = _MAP[7][2];
    _MAP_SIM[7][3] = _MAP[7][3];
    _MAP_SIM[7][4] = _MAP[7][4];
    _MAP_SIM[7][5] = _MAP[7][5];
    _MAP_SIM[7][6] = _MAP[7][6];
    _MAP_SIM[7][7] = _MAP[7][7];
    _MAP_SIM[7][8] = _MAP[7][8];
    _MAP_SIM[8][0] = _MAP[8][0];
    _MAP_SIM[8][1] = _MAP[8][1];
    _MAP_SIM[8][2] = _MAP[8][2];
    _MAP_SIM[8][3] = _MAP[8][3];
    _MAP_SIM[8][4] = _MAP[8][4];
    _MAP_SIM[8][5] = _MAP[8][5];
    _MAP_SIM[8][6] = _MAP[8][6];
    _MAP_SIM[8][7] = _MAP[8][7];
    _MAP_SIM[8][8] = _MAP[8][8];
}

void get_valid_actions_MAP(int row_big_map, int col_big_map)
{
    int row = row_big_map * 3;
    int col = col_big_map * 3;

    if(_MAP_SIM[row][col] == 0)         valid_actions.pb({row, col});
    if(_MAP_SIM[row][col + 1] == 0)     valid_actions.pb({row, col + 1});
    if(_MAP_SIM[row][col + 2] == 0)     valid_actions.pb({row, col + 2});
    if(_MAP_SIM[row + 1][col] == 0)     valid_actions.pb({row + 1, col});
    if(_MAP_SIM[row + 1][col + 1] == 0) valid_actions.pb({row + 1, col + 1});
    if(_MAP_SIM[row + 1][col + 2] == 0) valid_actions.pb({row + 1, col + 2});
    if(_MAP_SIM[row + 2][col] == 0)     valid_actions.pb({row + 2, col});
    if(_MAP_SIM[row + 2][col + 1] == 0) valid_actions.pb({row + 2, col + 1});
    if(_MAP_SIM[row + 2][col + 2] == 0) valid_actions.pb({row + 2, col + 2});
}

void get_valid_actions_BIG_MAP(int last_row, int last_col)
{
    valid_actions.clear();
    int row_big_map = last_row % 3;
    int col_big_map = last_col % 3;

    if(_BIG_MAP_SIM[row_big_map][col_big_map])
    {
        if(_BIG_MAP_SIM[0][0] == 0) get_valid_actions_MAP(0, 0);
        if(_BIG_MAP_SIM[0][1] == 0) get_valid_actions_MAP(0, 1);
        if(_BIG_MAP_SIM[0][2] == 0) get_valid_actions_MAP(0, 2);
        if(_BIG_MAP_SIM[1][0] == 0) get_valid_actions_MAP(1, 0);
        if(_BIG_MAP_SIM[1][1] == 0) get_valid_actions_MAP(1, 1);
        if(_BIG_MAP_SIM[1][2] == 0) get_valid_actions_MAP(1, 2);
        if(_BIG_MAP_SIM[2][0] == 0) get_valid_actions_MAP(2, 0);
        if(_BIG_MAP_SIM[2][1] == 0) get_valid_actions_MAP(2, 1);
        if(_BIG_MAP_SIM[2][2] == 0) get_valid_actions_MAP(2, 2);
    }
    else
    {
        get_valid_actions_MAP(row_big_map, col_big_map);
    }
}

int check_win_big_map()
{
    // VERTICAL
    if(_BIG_MAP_SIM[0][0] != 0 and _BIG_MAP_SIM[0][0] == _BIG_MAP_SIM[1][0] and _BIG_MAP_SIM[1][0] == _BIG_MAP_SIM[2][0])
        return _BIG_MAP_SIM[0][0];
    if(_BIG_MAP_SIM[0][1] != 0 and _BIG_MAP_SIM[0][1] == _BIG_MAP_SIM[1][1] and _BIG_MAP_SIM[1][1] == _BIG_MAP_SIM[2][1])
        return _BIG_MAP_SIM[0][1];
    if(_BIG_MAP_SIM[0][2] != 0 and _BIG_MAP_SIM[0][2] == _BIG_MAP_SIM[1][2] and _BIG_MAP_SIM[1][2] == _BIG_MAP_SIM[2][2])
        return _BIG_MAP_SIM[0][2];
    // HORIZONTAL

    if(_BIG_MAP_SIM[0][0] != 0 and _BIG_MAP_SIM[0][0] == _BIG_MAP_SIM[0][1] and _BIG_MAP_SIM[0][1] == _BIG_MAP_SIM[0][2])
        return _BIG_MAP_SIM[0][0];
    if(_BIG_MAP_SIM[1][0] != 0 and _BIG_MAP_SIM[1][0] == _BIG_MAP_SIM[1][1] and _BIG_MAP_SIM[1][1] == _BIG_MAP_SIM[1][2])
        return _BIG_MAP_SIM[1][0];
    if(_BIG_MAP_SIM[2][0] != 0 and _BIG_MAP_SIM[2][0] == _BIG_MAP_SIM[2][1] and _BIG_MAP_SIM[2][1] == _BIG_MAP_SIM[2][2])
        return _BIG_MAP_SIM[2][0];

    // ACROSS
    if(_BIG_MAP_SIM[0][0] != 0 and _BIG_MAP_SIM[0][0] == _BIG_MAP_SIM[1][1] and _BIG_MAP_SIM[1][1] == _BIG_MAP_SIM[2][2])
        return _BIG_MAP_SIM[0][0];
    if(_BIG_MAP_SIM[0][2] != 0 and _BIG_MAP_SIM[0][2] == _BIG_MAP_SIM[1][1] and _BIG_MAP_SIM[1][1] == _BIG_MAP_SIM[2][0])
        return _BIG_MAP_SIM[0][2];

    return 0;
}

void update_big_map_sim(int last_row, int last_col)
{
    int row = last_row - last_row % 3; // current big map
    int col = last_col - last_col % 3;

    int n_wins = 0;
    if(_BIG_MAP_SIM[row / 3][col / 3] != 0)
    {
        cerr << last_row << " " << last_col << " | " << row << " " << col << endl;
        FOR(i, 0, 3)
        {
            FOR(j, 0, 3)
                cerr << _BIG_MAP_SIM[i][j] << " ";
            cerr << endl;
        }
        cout << "-1 -1 ASSERT: 217" << endl;
    }
    // VERTICAL
    if(_MAP_SIM[0 + row][0 + col] != 0 and _MAP_SIM[0 + row][0 + col] == _MAP_SIM[1 + row][0 + col] \
        and _MAP_SIM[1 + row][0 + col] == _MAP_SIM[2 + row][0 + col])
    {
        n_wins ++;
        _BIG_MAP_SIM[row / 3][col / 3] = _MAP_SIM[0 + row][0 + col];
    }
    if(_MAP_SIM[0 + row][1 + col] != 0 and _MAP_SIM[0 + row][1 + col] == _MAP_SIM[1 + row][1 + col] \
        and _MAP_SIM[1 + row][1 + col] == _MAP_SIM[2 + row][1 + col])
    {
        n_wins ++;
        _BIG_MAP_SIM[row / 3][col / 3] = _MAP_SIM[0 + row][1 + col];
    }
    if(_MAP_SIM[0 + row][2 + col] != 0 and _MAP_SIM[0 + row][2 + col] == _MAP_SIM[1 + row][2 + col] \
        and _MAP_SIM[1 + row][2 + col] == _MAP_SIM[2 + row][2 + col])
    {
        n_wins ++;
        _BIG_MAP_SIM[row / 3][col / 3] = _MAP_SIM[0 + row][2 + col];
    }
    // HORIZONTAL

    if(_MAP_SIM[0 + row][0 + col] != 0 and _MAP_SIM[0 + row][0 + col] == _MAP_SIM[0 + row][1 + col] \
        and _MAP_SIM[0 + row][1 + col] == _MAP_SIM[0 + row][2 + col])
    {
        n_wins ++;
        _BIG_MAP_SIM[row / 3][col / 3] = _MAP_SIM[0 + row][0 + col];
    }
    if(_MAP_SIM[1 + row][0 + col] != 0 and _MAP_SIM[1 + row][0 + col] == _MAP_SIM[1 + row][1 + col] \
        and _MAP_SIM[1 + row][1 + col] == _MAP_SIM[1 + row][2 + col])
    {
        n_wins ++;
        _BIG_MAP_SIM[row / 3][col / 3] = _MAP_SIM[1 + row][0 + col];
    }
    if(_MAP_SIM[2 + row][0 + col] != 0 and _MAP_SIM[2 + row][0 + col] == _MAP_SIM[2 + row][1 + col] \
        and _MAP_SIM[2 + row][1 + col] == _MAP_SIM[2 + row][2 + col])
    {
        n_wins ++;
        _BIG_MAP_SIM[row / 3][col / 3] = _MAP_SIM[2 + row][0 + col];
    }

    // ACROSS
    if(_MAP_SIM[0 + row][0 + col] != 0 and _MAP_SIM[0 + row][0 + col] == _MAP_SIM[1 + row][1 + col] \
        and _MAP_SIM[1 + row][1 + col] == _MAP_SIM[2 + row][2 + col])
    {
        n_wins ++;
        _BIG_MAP_SIM[row / 3][col / 3] = _MAP_SIM[0 + row][0 + col];
    }
    if(_MAP_SIM[0 + row][2 + col] != 0 and _MAP_SIM[0 + row][2 + col] == _MAP_SIM[1 + row][1 + col] \
        and _MAP_SIM[1 + row][1 + col] == _MAP_SIM[2 + row][0 + col])
    {
        n_wins ++;
        _BIG_MAP_SIM[row / 3][col / 3] = _MAP_SIM[0 + row][2 + col];
    }
}


void update_big_map(int last_row, int last_col)
{
    int row = last_row - last_row % 3; // current big map
    int col = last_col - last_col % 3;

    if(_BIG_MAP[row / 3][col / 3] != 0)
    {
        cerr << last_row << " " << last_col << " | " << row << " " << col << endl;
        FOR(i, 0, 3)
        {
            FOR(j, 0, 3)
                cerr << _BIG_MAP[i][j] << " ";
            cerr << endl;
        }
        cout << "-1 -1 ASSERT: 280" << endl;

    }
    // VERTICAL
    if(_MAP[0 + row][0 + col] != 0 and _MAP[0 + row][0 + col] == _MAP[1 + row][0 + col] and _MAP[1 + row][0 + col] == _MAP[2 + row][0 + col])
        _BIG_MAP[row / 3][col / 3] = _MAP[0 + row][0 + col];

    if(_MAP[0 + row][1 + col] != 0 and _MAP[0 + row][1 + col] == _MAP[1 + row][1 + col] and _MAP[1 + row][1 + col] == _MAP[2 + row][1 + col])
        _BIG_MAP[row / 3][col / 3] = _MAP[0 + row][1 + col];

    if(_MAP[0 + row][2 + col] != 0 and _MAP[0 + row][2 + col] == _MAP[1 + row][2 + col] and _MAP[1 + row][2 + col] == _MAP[2 + row][2 + col])
        _BIG_MAP[row / 3][col / 3] = _MAP[0 + row][2 + col];

    // HORIZONTAL
    if(_MAP[0 + row][0 + col] != 0 and _MAP[0 + row][0 + col] == _MAP[0 + row][1 + col] and _MAP[0 + row][1 + col] == _MAP[0 + row][2 + col])
        _BIG_MAP[row / 3][col / 3] = _MAP[0 + row][0 + col];

    if(_MAP[1 + row][0 + col] != 0 and _MAP[1 + row][0 + col] == _MAP[1 + row][1 + col] and _MAP[1 + row][1 + col] == _MAP[1 + row][2 + col])
        _BIG_MAP[row / 3][col / 3] = _MAP[1 + row][0 + col];

    if(_MAP[2 + row][0 + col] != 0 and _MAP[2 + row][0 + col] == _MAP[2 + row][1 + col] and _MAP[2 + row][1 + col] == _MAP[2 + row][2 + col])
        _BIG_MAP[row / 3][col / 3] = _MAP[2 + row][0 + col];


    // ACROSS
    if(_MAP[0 + row][0 + col] != 0 and _MAP[0 + row][0 + col] == _MAP[1 + row][1 + col] and _MAP[1 + row][1 + col] == _MAP[2 + row][2 + col])
        _BIG_MAP[row / 3][col / 3] = _MAP[0 + row][0 + col];

    if(_MAP[0 + row][2 + col] != 0 and _MAP[0 + row][2 + col] == _MAP[1 + row][1 + col] and _MAP[1 + row][1 + col] == _MAP[2 + row][0 + col])
        _BIG_MAP[row / 3][col / 3] = _MAP[0 + row][2 + col];
}

int count_big_map_score()
{
        int player1 = 0;
        int player2 = 0;
        if(_BIG_MAP_SIM[0][0] == 1) player1 ++;
        if(_BIG_MAP_SIM[0][1] == 1) player1 ++;
        if(_BIG_MAP_SIM[0][2] == 1) player1 ++;
        if(_BIG_MAP_SIM[1][0] == 1) player1 ++;
        if(_BIG_MAP_SIM[1][1] == 1) player1 ++;
        if(_BIG_MAP_SIM[1][2] == 1) player1 ++;
        if(_BIG_MAP_SIM[2][0] == 1) player1 ++;
        if(_BIG_MAP_SIM[2][1] == 1) player1 ++;
        if(_BIG_MAP_SIM[2][2] == 1) player1 ++;

        if(_BIG_MAP_SIM[0][0] == 2) player2 ++;
        if(_BIG_MAP_SIM[0][1] == 2) player2 ++;
        if(_BIG_MAP_SIM[0][2] == 2) player2 ++;
        if(_BIG_MAP_SIM[1][0] == 2) player2 ++;
        if(_BIG_MAP_SIM[1][1] == 2) player2 ++;
        if(_BIG_MAP_SIM[1][2] == 2) player2 ++;
        if(_BIG_MAP_SIM[2][0] == 2) player2 ++;
        if(_BIG_MAP_SIM[2][1] == 2) player2 ++;
        if(_BIG_MAP_SIM[2][2] == 2) player2 ++;

        if(player1 > player2) return 1;
        if(player1 < player2) return 2;
        return 0;
}


int simmulate(int row, int col) // RETURNS RESULT OF A FULL GAME SIMMULATION
{
    copy_maps_to_sim();
    int player = 1;
    int last_row = row;
    int last_col = col;

    while(true)
    {
        _MAP_SIM[last_row][last_col] = player;
        update_big_map_sim(last_row, last_col);
        int win_on_big_map = check_win_big_map();
        if(win_on_big_map) return win_on_big_map;

        get_valid_actions_BIG_MAP(last_row, last_col);

        if(valid_actions.size() == 0) return count_big_map_score();

        int r = rand() % valid_actions.size();
        tie(last_row, last_col) = valid_actions[r];
        if(player == 1) player = 2;
        else player = 1;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    /*
    1: ME
    2: OPPONENT

    */

    int round = 0;
    while(true)
    {
        round ++;
        double ROUND_TH = TIME_THRESHOLD;
        if(round == 1) ROUND_TH *= 9;

        int opponentRow, opponentCol, validActionCount;
        cin >> opponentRow >> opponentCol; cin.ignore();
        cin >> validActionCount; cin.ignore();

        _MAP[opponentRow][opponentCol] = 2;
        update_big_map(opponentRow, opponentCol);

        vpi valid_actions;
        vpd scores;
        FOR(i, 0, validActionCount)
        {
            int row;
            int col;
            cin >> row >> col; cin.ignore();
            valid_actions.pb({row, col});
            scores.pb({1, 2});
        }
        double time_start = clock();

        int n_simmulations = 0;
        while((clock() - time_start) / CLOCKS_PER_SEC < ROUND_TH)
        {
            int r = rand() % valid_actions.size();
            int result = simmulate(valid_actions[r].first, valid_actions[r].second);
            if(result == 1) scores[r].first += 1;
            if(result == 0) scores[r].first += 0.5;
            scores[r].second ++;
            n_simmulations ++;
        }


        int best_x, best_y;
        double best_score = -10000000;
        int a = 0, b = 0;
        FOR(i, 0, scores.size())
        {
            // cerr << x << " / " << y << endl;
            double score = scores[i].first / scores[i].second;
            if(score > best_score)
            {
                best_score = score;
                tie(best_x, best_y) = valid_actions[i];
                a = scores[i].first, b = scores[i].second;
            }
        }
        cerr << "n_simmulations: " << n_simmulations << endl;
        cerr << "Best score: " << best_score << " >>>> " << a << " / " << b << endl;
        cerr << "Time elapsed: " << fixed << setprecision(4) << (clock() - time_start) / CLOCKS_PER_SEC <<endl;
        cout << best_x << " " << best_y << " #" << n_simmulations << endl;
        _MAP[best_x][best_y] = 1;
        update_big_map(best_x, best_y);
    }
}

/*
TODO:
2. UCB only when there are no NULLS
3. When following my score and chosing for opponent flip my score....
4. open book
5. faster rand() like xorshf96
*/
