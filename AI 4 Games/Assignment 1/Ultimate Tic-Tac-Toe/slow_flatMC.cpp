/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector <short> vi;
typedef vector <ll> vl;
typedef pair <int, int> pi;
typedef pair <ll, ll> pl;
typedef tuple <int, int, int> ti;
typedef tuple <ll, ll, ll> tl;
typedef vector < pl > vpl;
typedef vector < pi > vpi;
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

int check_win_3x3(int x, int y, vector < vi > &BOARD)
{
    x *= 3;
    y *= 3;

    assert(x + 2 < 9 and y + 2 < 9);
    FOR(i, 0, 3)
    {
        if(BOARD[i + x][0 + y] != 0 and BOARD[i + x][0 + y] == BOARD[i + x][1 + y] \
            and BOARD[i + x][1 + y] == BOARD[i + x][2 + y])
            return BOARD[i + x][0 + y];

        if(BOARD[0 + x][i + y] != 0 and BOARD[0 + x][i + y] == BOARD[1 + x][i + y] \
            and BOARD[1 + x][i + y] == BOARD[2 + x][i + y])
            return BOARD[0 + x][i + y];
    }
    if(BOARD[0 + x][0 + y] != 0 and BOARD[0 + x][0 + y] == BOARD[1 + x][1 + y] \
        and BOARD[1 + x][1 + y] == BOARD[2 + x][2 + y])
        return BOARD[0 + x][0 + y];

    if(BOARD[0 + x][2 + y] != 0 and BOARD[0 + x][2 + y] == BOARD[1 + x][1 + y] \
        and BOARD[1 + x][1 + y] == BOARD[2 + x][0 + y])
        return BOARD[0 + x][2 + y];

    return 0;
}


 typedef struct Node{
    pi action;
    int n_games;
    double score;
    Node *parent;
    vector < Node* > children;
    vector < vi > MAP{9, vi(9, 0)};   // global MAP
    vector < vi > who_won{3, vi(3, 0)};  // who won on the certain board

    int check_win(int start_x, int start_y)
    {
        int win_3x3 = check_win_3x3(start_x, start_y, this->MAP);
        if(win_3x3)
        {
            this->who_won[start_x][start_y] = win_3x3;
            int global_win = check_win_3x3(0, 0, this->who_won);
            if(global_win)
                return global_win;
        }

        return 0;
    }

    int end_of_moves()
    {
        int p1_wins = 0, p2_wins = 0;
        FOR(i, 0, 3)
        {
            FOR(j, 0, 3)
            {
                if(this->who_won[i][j] == 1)
                    p1_wins ++;
                if(this->who_won[i][j] == 2)
                    p2_wins ++;
            }
        }
        if(p1_wins == p2_wins)
            return 0;
        if(p1_wins > p2_wins)
            return 1;
        else
            return 2;
    }

    pi make_move(int board_x, int board_y, int player) // selects a random move from the posssible moves
    {
        vpi possible_moves;

        if(this->who_won[board_x][board_y]) // 81 moves
        {
            FOR(x, 0, 9)
            {
                FOR(y, 0, 9)
                {
                    if(this->MAP[x][y] or this->who_won[x / 3][y / 3])
                        continue;
                    possible_moves.pb({x, y});
                }
            }
        }
        else
        {
            FOR(x, board_x * 3, board_x * 3 + 3)
            {
                FOR(y, board_y * 3, board_y * 3 + 3)
                {
                    if(this->MAP[x][y] or this->who_won[x / 3][y / 3])
                        continue;
                    possible_moves.pb({x, y});
                }
            }
        }

        if(possible_moves.size() == 0)
        {
            return {-1, -1};
        }

        int r = rand() % possible_moves.size();
        return possible_moves[r];
    }

    int simulate(double time_start)  // plays the game till the end using random moves
    {
        this->MAP[this->action.first][this->action.second] = 1;
        int player = 2;
        int last_x = this->action.first, last_y = this->action.second;
        int start_x = last_x / 3;
        int start_y = last_y / 3;
        // print_board();

        int act_x, act_y;
        while((clock() - time_start) / CLOCKS_PER_SEC < TIME_THRESHOLD)
        {
            int player_won = check_win(start_x, start_y);
            if(player_won)
            {
                return player_won;
            }

            tie(act_x, act_y) = make_move(last_x % 3, last_y % 3, player);
            if(act_x == -1 and act_y == -1)
                return end_of_moves();

            last_x = act_x;
            last_y = act_y;
            start_x = last_x / 3;
            start_y = last_y / 3;

            this->MAP[act_x][act_y] = player;

            if(player == 2)
                player = 1;
            else
                player = 2;
        }
    }

    void update(int value) // update node and backpropagate to parent
    {

    }

    void add_child(Node *child)
    {
        this->children.pb(child);
    }

    void print_board()
    {
        for(auto row: this->MAP)
        {
            for(auto x: row)
                cerr << x << " ";
            cerr << endl;
        }
    }

    Node(pi action, int n_games, double score, Node *parent)
    {
        this->action = action;
        this->n_games = n_games;
        this->score = score;
        this->parent = parent;
    }
}Node;

Node actual_state({0, 0}, 0, 0, NULL);
void update_actual_state(int x, int y, int player)
{
    actual_state.MAP[x][y] = player;
    int win_3x3 = check_win_3x3(x / 3, y / 3, actual_state.MAP);
    actual_state.who_won[x / 3][y / 3] = win_3x3;
}

void print_actual_state_info()
{
    cerr << "=== MAP ===\n";
    FOR(i, 0, 9)
    {
        FOR(j, 0, 9)
        {
            cerr << actual_state.MAP[i][j] << " ";
        }
        cerr << endl;
    }
    cerr << "=== WHO WON ===\n";
    FOR(i, 0, 3)
    {
        FOR(j, 0, 3)
        {
            cerr << actual_state.who_won[i][j] << " ";
        }
        cerr << endl;
    }
    cerr << "**************\n";
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
    FOR(round, 0, 1000000)
    {
        int opponentRow, opponentCol, validActionCount;
        cin >> opponentRow >> opponentCol; cin.ignore();
        cin >> validActionCount; cin.ignore();

        if(opponentRow != -1)
            update_actual_state(opponentRow, opponentCol, 2);

        if(round == 0)
            assert(validActionCount == 81 or validActionCount == 9 or validActionCount == 8);

        vector < Node > states;
        FOR(i, 0, validActionCount)
        {
            int row;
            int col;
            cin >> row >> col; cin.ignore();

            Node new_node({row, col}, 0, 0, NULL);
            states.pb(new_node);
        }
        double time_start = clock();

        int n_simmulations = 0;
        cerr << "Start simmulating ... \n";
        while((clock() - time_start) / CLOCKS_PER_SEC < TIME_THRESHOLD)
        {
            int r = rand() % validActionCount;
            states[r].who_won = actual_state.who_won;
            states[r].MAP = actual_state.MAP;
            int result = states[r].simulate(time_start);
            if(result == 1) // I won
                states[r].score ++;
            // if(result == 2)
            //     states[r].score --;
            if(result == 0)
                states[r].score += 0.5;
            states[r].n_games ++;

            n_simmulations ++;
        }
        cerr << "Finish simmulating ... \n";
        pi best_action = {-1, -1};
        double best_score = -100000;
        int ibest_score, n_games;
        for(auto s: states)
        {
            double score = (double)(s.score + 1) / (double)(s.n_games + 2);
            if(score > best_score)
            {
                best_score = score;
                best_action = s.action;
                ibest_score = s.score;
                n_games = s.n_games;
            }

        }
        cerr << "Actions: " << validActionCount << endl;
        cerr << "Best score: " << best_score << " | " << ibest_score << " / " << n_games << endl;
        cerr << "n_simmulations: " << n_simmulations << endl;
        cerr << "Time elapsed: " << fixed << setprecision(4) << (clock() - time_start) / CLOCKS_PER_SEC <<endl;
        cout << best_action.first << " " << best_action.second << endl;
        update_actual_state(best_action.first, best_action.second, 1);
        // print_actual_state_info();
    }
}

/*
TODO:
1. Get all moves from parent
2. UCB only when there are no NULLS
3. When following my score and chosing for opponent flip my score....
4. open book

*/
