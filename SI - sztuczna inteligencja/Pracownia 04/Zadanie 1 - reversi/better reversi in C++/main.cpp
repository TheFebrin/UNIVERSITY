/* Dejwo to ziomal ®© */
#include <bits/stdc++.h>
#include "functions.hpp"
using namespace std;
#define pb push_back
typedef long long ll;
typedef vector <int> vi;
typedef vector <ll> vl;
typedef pair <int, int> pi;
typedef pair <ll, ll> pl;
typedef tuple <int, int, int> ti;
typedef vector < pair< int , int> > vpi;
typedef vector < tuple <int , int, int> > vti;

double t = clock();
vector < vector < char > > BOARD;
void prepare_boad();
void print_board(int p);

int main()
{
    ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);

    srand(time(NULL));
    int white_score = 0;
    int games_no = 1;
    bool debug = false;
    int depth = 0;
    int strategy = 0;

    cout << "\nHow many games? ";
    cin >> games_no;
    assert( games_no > 0 );

    cout << "What strategy?\n";
    cout << "1. Random\n";
    cout << "2. Alpha Beta pruning\n";
    cin >> strategy;

    assert( strategy == 1 or strategy == 2);

    if( strategy == 2 ){
        cout << "\nDepth of search? (it's always 1 time bigger): ";
        cin >> depth;
    }

    for(int g = 0; g < games_no; g ++){

        prepare_boad();
        int player = 0;
        int end_game = 0;

        while( true ){
            // both players couldn't make a move
            if( end_game == 2 ){
                if( debug ) {
                    cout << "GAME OVER!\n";
                    print_board(player);
                    cout << "\n--------------------------------------------\n";
                }
                cout << "Game : " << g + 1 << "  ->  ";
                white_score += game_summary( BOARD );
                break;
            }

            if( debug ) print_board(player);
            map < pi, vpi > moves = find_moves(BOARD,player);

            // skip if player has no move to make
            if( moves.size() == 0 ){
                end_game ++;
                player ^= 1;
                if( debug ) cout << "\n--------------------------------------------\n";
                continue;
            }

            if( player == 0 ) // random player
            {
                // random player
                int random_move = rand() % moves.size();
                auto iter = moves.begin();
                advance(iter, random_move);
                make_move(BOARD, iter->second, iter->first, player);

                //min max player
                // pair < pi, vpi > best_move = use_minimax(BOARD, moves, player, depth);
                // make_move(BOARD, best_move.second, best_move.first, player);
            }
            else // bot
            {
                if( strategy == 1)
                {
                    int random_move = rand() % moves.size();
                    auto iter = moves.begin();
                    advance(iter, random_move);
                    make_move(BOARD, iter->second, iter->first, player);
                }
                else
                {
                    pair < pi, vpi > best_move = use_minimax(BOARD, moves, player, depth);
                    make_move(BOARD, best_move.second, best_move.first, player);
                }
            }


            if( debug ) cout << "\n--------------------------------------------\n";
            player ^= 1;
            end_game = 0;
        }
    }
    cout << "\n--------------------------------------------\n";
    cout << "Whites won: " << white_score << endl;
    cout << "Whites winning % : " << (double)white_score / (double)games_no * 100 << "% !\n";
    cout << "Duration " << (clock() - t) / CLOCKS_PER_SEC << " sec\n";

    return 0;
}

void prepare_boad(){
    vector < char > row = { '.', '.', '.', '.', '.', '.', '.', '.' };
    BOARD.assign(8, row);

    BOARD[ 3 ][ 3 ] = 'W';
    BOARD[ 3 ][ 4 ] = 'B';
    BOARD[ 4 ][ 3 ] = 'B';
    BOARD[ 4 ][ 4 ] = 'W';
}

void print_board(int p){
    if( p == 0 ) cout << "White move.\n";
    else cout << "Black move.\n";

    for(int i = 0; i < 8 ; i ++){
        for(int j = 0; j < 8 ; j ++){
            cout << BOARD[ i ][ j ] << " ";
        }
        cout << endl;
    }
}
