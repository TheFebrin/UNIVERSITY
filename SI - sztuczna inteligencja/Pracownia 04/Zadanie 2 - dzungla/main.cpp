/* Dejwo to ziomal ®© */
#include <bits/stdc++.h>
#include "jungle.hpp"
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
vector < vector < char > > ANIMALS;
map < char, int > animal_val;

void fill_animal_val();
void prepare_boad();
void prepare_animals();
void print_board();
void print_animals();

/*
rat (R), - 0
cat (C), - 1
dog (D), - 2
wolf (W), - 3
jaguar (J), - 4
tiger (T), - 5
lion (L), - 6
elefant (E) - 7
*/

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(NULL));

    fill_animal_val();
    prepare_boad();
    prepare_animals();

    int player = 0;
    int total_moves = 1000;
    int moves_no = 0;
    int N = 2000;

    // BOT has big letters

    for(int i = 1; i <= total_moves; i ++ ){
        if( player == 1 ) std::this_thread::sleep_for(std::chrono::milliseconds(2));
        system("clear");
        cout <<"Move: " << i << endl;
        print_animals();
        vector < one_move > moves = gen_moves(BOARD, ANIMALS, player, animal_val);

        if( moves.size() == 0 ){
            player ^= 1;
            continue;
        }

        if( moves_no == max_games )
        {
            int result = game_over( ANIMALS, animal_val );
            if( result == 1 ) cout << "Bot won!\n";
            else cout << "Player won!\n";
            break;
        }

        if( player == 0 )
        {
            assert( moves.size() > 0 );
            int random_move = rand() % moves.size();
            one_move m = moves[ random_move ];

            if( ANIMALS[ m.x_to ][ m.y_to ] == '.' ) moves_no ++;
            else moves_no = 0;

            if( m.animal == 't' or m.animal == 'T' or m.animal == 'l' or m.animal == 'L'){
                auto np = move_over_lake( BOARD, m.x_from, m.y_from, m.x_to, m.y_to);
                m.x_to = np.first;
                m.y_to = np.second;
            }

            ANIMALS[ m.x_from ][ m.y_from ] = '.';
            ANIMALS[ m.x_to ][ m.y_to ] = m.animal;

        }
        else
        {
            assert( moves.size() > 0 );
            one_move m = simulate(moves, BOARD, ANIMALS, player, N, animal_val);

            if( ANIMALS[ m.x_to ][ m.y_to ] == '.' ) moves_no ++;
            else moves_no = 0;

            if( m.animal == 't' or m.animal == 'T' or m.animal == 'l' or m.animal == 'L'){
                auto np = move_over_lake( BOARD, m.x_from, m.y_from, m.x_to, m.y_to);
                m.x_to = np.first;
                m.y_to = np.second;
            }

            ANIMALS[ m.x_from ][ m.y_from ] = '.';
            ANIMALS[ m.x_to ][ m.y_to ] = m.animal;
        }


        cout << "-------------------------------\n\n";
        player ^= 1;
    }


    cout << "Duration " << (clock() - t) / CLOCKS_PER_SEC << " sec\n";

    return 0;
}

void prepare_boad(){
    vector < char > row = { '<','O','/' };
    BOARD.assign(9, row);

    vector < char > row1 = {'.', '.', '#', '*', '#', '.', '.' };
    vector < char > row2 = {'.', '.', '.', '#', '.', '.', '.' };
    vector < char > row3 = {'.', '.', '.', '.', '.', '.', '.' };
    vector < char > row4 = {'.', '~', '~', '.', '~', '~', '.' };
    vector < char > row5 = {'.', '~', '~', '.', '~', '~', '.' };
    vector < char > row6 = {'.', '~', '~', '.', '~', '~', '.' };
    vector < char > row7 = {'.', '.', '.', '.', '.', '.', '.' };
    vector < char > row8 = {'.', '.', '.', '#', '.', '.', '.' };
    vector < char > row9 = {'.', '.', '#', '*', '#', '.', '.' };

    BOARD[ 0 ] = row1;
    BOARD[ 1 ] = row2;
    BOARD[ 2 ] = row3;
    BOARD[ 3 ] = row4;
    BOARD[ 4 ] = row5;
    BOARD[ 5 ] = row6;
    BOARD[ 6 ] = row7;
    BOARD[ 7 ] = row8;
    BOARD[ 8 ] = row9;

}

void prepare_animals(){
    vector < char > row = { '<','O','/' };
    ANIMALS.assign(9, row);

    vector < char > row1 = {'L', '.', '.', '.', '.', '.', 'T' };
    vector < char > row2 = {'.', 'D', '.', '.', '.', 'C', '.' };
    vector < char > row3 = {'R', '.', 'J', '.', 'W', '.', 'E' };
    vector < char > row4 = {'.', '.', '.', '.', '.', '.', '.' };
    vector < char > row5 = {'.', '.', '.', '.', '.', '.', '.' };
    vector < char > row6 = {'.', '.', '.', '.', '.', '.', '.' };
    vector < char > row7 = {'e', '.', 'l', '.', 'j', '.', 'r' };
    vector < char > row8 = {'.', 'c', '.', '.', '.', 'd', '.' };
    vector < char > row9 = {'t', '.', '.', '.', '.', '.', 'l' };

    ANIMALS[ 0 ] = row1;
    ANIMALS[ 1 ] = row2;
    ANIMALS[ 2 ] = row3;
    ANIMALS[ 3 ] = row4;
    ANIMALS[ 4 ] = row5;
    ANIMALS[ 5 ] = row6;
    ANIMALS[ 6 ] = row7;
    ANIMALS[ 7 ] = row8;
    ANIMALS[ 8 ] = row9;

}

void print_board(){
    for(int i = 0; i < 9 ; i ++){
        for(int j = 0; j < 7 ; j ++){
            cout << BOARD[ i ][ j ] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print_animals(){
    for(int i = 0; i < 9 ; i ++){
        for(int j = 0; j < 7 ; j ++){
            cout << ANIMALS[ i ][ j ] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void fill_animal_val()
{
    animal_val[ 'R' ] = 0;
    animal_val[ 'r' ] = 0;
    animal_val[ 'C' ] = 1;
    animal_val[ 'c' ] = 1;
    animal_val[ 'D' ] = 2;
    animal_val[ 'd' ] = 2;
    animal_val[ 'W' ] = 3;
    animal_val[ 'w' ] = 3;
    animal_val[ 'J' ] = 4;
    animal_val[ 'j' ] = 4;
    animal_val[ 'T' ] = 5;
    animal_val[ 't' ] = 5;
    animal_val[ 'L' ] = 6;
    animal_val[ 'l' ] = 6;
    animal_val[ 'E' ] = 7;
    animal_val[ 'e' ] = 7;
}
