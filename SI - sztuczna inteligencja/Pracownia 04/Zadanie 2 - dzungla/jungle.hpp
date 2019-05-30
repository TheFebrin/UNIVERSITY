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

int dx[ 4 ] = {0, 0, 1, -1};
int dy[ 4 ] = {1, -1, 0, 0};
int max_games = 100;

bool my_animal(char a, bool player ){
    if( player == 0 ){
        if( a == 'r' or a == 'c' or a == 'd' or a == 'w' or a == 'j' or a == 't' or a == 'l' or a == 'e')
            return true;
        return false;
    }
    else{
        if( a == 'R' or a == 'C' or a == 'D' or a == 'W' or a == 'J' or a == 'T' or a == 'L' or a == 'E')
            return true;
        return false;
    }
}

bool good_move( int x, int y, int xd, int yd, vector < vector < char > > BOARD, vector < vector < char > > ANIMALS, bool player, map < char, int > animal_val){
    // cave check

    if( xd == 0 and yd == 3 and player == 1 ) return false;
    if( xd == 8 and yd == 3 and player == 0 ) return false;

    // borders
    if( xd < 0 or xd > 8 or yd < 0 or yd > 6 ) {
        return false;
    }

    char animal_from = ANIMALS[ x ][ y ];
    char animal_dest = ANIMALS[ xd ][ yd ];

    char board_from = BOARD[ x ][ y ];
    char board_dest = BOARD[ xd ][ yd ];

    // my animal on destination field
    if( my_animal(ANIMALS[ xd ][ yd ], player) ) {
        return false;
    }

    // opponent's cave
    if( board_dest == '*' ) return true;


    // empty destination field is good
    if( animal_dest == '.' and board_dest == '.' ) return true;


    // Rat going from lake to ground cannot kill elefant
    if( board_from == '~' and animal_dest != '.' ) {
        return false;
    }

    // going into lake
    if( board_dest == '~' ){
        // rat
        if( animal_from == 'r' or animal_from == 'R' ) // rat
        {
            if( animal_dest != '.' ) // enemy rat
                return false;

            return true;
        }

        // jump over
        if( animal_from == 'L' or animal_from == 'l' or animal_from == 't' or animal_from == 'T' )
        {
            int vx = xd - x;
            int vy = yd - y;

            int act_x = xd, act_y = yd;
            while( BOARD[ act_x ][ act_y ] == '~' ){
                if( ANIMALS[ act_x ][ act_y ] == 'R' or ANIMALS[ act_x ][ act_y ] == 'r' ) return false;
                act_x += vx;
                act_y += vy;
            }

            if( ANIMALS[ act_x ][ act_y ] == '.' ) return true;
            int my_power = animal_val[ animal_from ];
            int opponent_power = animal_val[ ANIMALS[ act_x ][ act_y ] ];

            return my_power >= opponent_power;
        }
        else return false;
    }

    // animals collision
    // if destination animal stays in trap it dies
    if( BOARD[ xd ][ yd ] == '#' ) return true;


    int my_power = animal_val[ animal_from ];
    int opponent_power = animal_val[ animal_dest ];

    // rat killing elefant
    if( my_power == 0 and opponent_power == 7 ) return true;

    return my_power >= opponent_power;
}

typedef struct{
    int x_from;
    int y_from;

    int x_to;
    int y_to;

    char animal;

}one_move;

vector < one_move > gen_moves(vector < vector < char > > BOARD, vector < vector < char > > ANIMALS, bool player, map < char, int > animal_val){
    vector < pair < char, pi > > players_animals;
    vector < one_move > answer;

    if( player == 0 ){
        for(int i = 0; i < 9 ; i ++){
            for(int j = 0; j < 7 ; j ++){
                if( ANIMALS[ i ][ j ] > 96 ) //player 0 has small letters
                {
                    players_animals.pb( {ANIMALS[ i ][ j ], {i, j} } );
                }
            }
        }
    }
    else{
        for(int i = 0; i < 9 ; i ++){
            for(int j = 0; j < 7 ; j ++){
                if( ANIMALS[ i ][ j ] < 96 and ANIMALS[ i ][ j ] > 64 ) // player 1 - big letters
                {
                    players_animals.pb( { ANIMALS[ i ][ j ], {i, j} } );
                }
            }
        }
    }

    for(auto a: players_animals){
        char animal = a.first;
        int x = a.second.first;
        int y = a.second.second;
        for(int i = 0; i < 4; i ++){
            int new_x = x + dx[ i ];
            int new_y = y + dy[ i ];
            if( good_move(x, y, new_x, new_y, BOARD, ANIMALS, player, animal_val) ){
                one_move om;
                om.x_from = x;
                om.y_from = y;
                om.x_to = new_x;
                om.y_to = new_y;
                om.animal = animal;
                answer.pb( om );
            }
        }
    }

    return answer;
}


int game_over( vector < vector < char > > ANIMALS, map < char, int > animal_val){
    // returns -1 if player 0 won, 1 if player 1 won
    int best_0 = 0;
    int best_1 = 0;

    for(int i = 0; i < 9 ; i ++){
        for(int j = 0; j < 7 ; j ++){
            if( ANIMALS[ i ][ j ] < 96 and ANIMALS[ i ][ j ] > 64 ) // player 1 - big letters
            {
                //best_1 = max(best_1, animal_val[ ANIMALS[ i ][ j ] ]);
                best_1 += animal_val[ ANIMALS[ i ][ j ] ];
            }
            if( ANIMALS[ i ][ j ] > 96 ) //player 0 has small letters
            {
                //best_0 = max(best_0, animal_val[ ANIMALS[ i ][ j ] ]);
                best_0 += animal_val[ ANIMALS[ i ][ j ] ];
            }
        }
    }

    return best_1 - best_0;

    // if( best_0 == best_1 ) return -1;

    // if( best_0 > best_1 ) return -1;
    // else return 1;
}

pi move_over_lake(vector < vector < char > > BOARD, int x, int y, int x_to, int y_to){

    int vx = x_to - x;
    int vy = y_to - y;

    int act_x = x_to, act_y = y_to;
    while( BOARD[ act_x ][ act_y ] == '~' ){
        act_x += vx;
        act_y += vy;
    }

    return {act_x, act_y};
}


int play( vector < vector < char > > ANIMALS, vector < vector < char > > BOARD, map < char, int > animal_val, bool player){
    int moves_no = 0;
    int score = 0;
    int moves_without_kill = 0;

    srand(time(NULL));

    while( true ){
        vector < one_move > moves = gen_moves(BOARD, ANIMALS, player, animal_val);

         if( moves_without_kill == max_games or moves.size() == 0){
            score = game_over( ANIMALS, animal_val );
            return score;
        }

        int random_move = rand() % moves.size();
        one_move m = moves[ random_move ];

        if( ANIMALS[ m.x_to ][ m.y_to ] == '.' ) moves_without_kill ++;
        else moves_without_kill = 0;

     if( m.animal == 't' or m.animal == 'T' or m.animal == 'l' or m.animal == 'L'){
            auto np = move_over_lake( BOARD, m.x_from, m.y_from, m.x_to, m.y_to);
            m.x_to = np.first;
            m.y_to = np.second;
        }

        ANIMALS[ m.x_from ][ m.y_from ] = '.';
        ANIMALS[ m.x_to ][ m.y_to ] = m.animal;

        player ^= 1;
        moves_no ++;
    }

    return score;
}

one_move simulate( vector < one_move > moves , vector < vector < char > > BOARD, vector < vector < char > > ANIMALS, bool player, int N, map < char, int > animal_val){
    int number_of_moves = (int)moves.size();
    vi score( number_of_moves, 0);
    vector < vector < vector < char > > > States;

    for(auto move: moves){
        auto New_Animals = ANIMALS;
        New_Animals[ move.x_from ][ move.y_from ] = '.';
        New_Animals[ move.x_to ][ move.y_to ] = move.animal;
        States.pb( New_Animals );
    }

    // int act_state = 0;

    // while( N > 0 ){
    //     act_state %= number_of_moves;

    //     int result = play(States[ act_state ], BOARD, animal_val, player^1);
    //     N --;
    //     score[ act_state ] += result;

    //     act_state ++;
    // }

    // // if few moves have similar score we move random one

    // int best_score = *max_element(score.begin(), score.end());
    // vi possibilities;

    // for(int i = 0; i < number_of_moves; i ++){
    //     if(score[ i ] == best_score){
    //         possibilities.pb( i );
    //     }
    // }
    // srand(time(NULL));
    // int choice = rand() % possibilities.size();

    // for(int i = 0 ; i < score.size(); i ++) cout << moves[ i ].animal << " ";
    // cout << endl;
    // for(int i = 0 ; i < score.size(); i ++) cout << score[ i ] << " ";
    // cout << endl;

    // cout << "Best move: \n";
    // cout << moves[ possibilities[ choice ] ].animal << endl;
    // cout << moves[ possibilities[ choice ] ].x_from << " " << moves[ possibilities[ choice ] ].y_from << endl;
    // cout << moves[ possibilities[ choice ] ].x_to << " " << moves[ possibilities[ choice ] ].y_to << endl << endl;


    //return moves[ possibilities[ choice ] ];


    int ans = 0;
    for(int i = 0; i < (int)States.size(); i ++){
        score[ i ] = game_over(States[i], animal_val);
    }
    int best_score = *max_element(score.begin(), score.end());
    vi possibilities;

    // for(int i = 0; i < (int)States.size(); i ++) cout << moves[ i ].animal << " ";
    // cout << endl;

    for(int i = 0; i < (int)States.size(); i ++){
       // cout << score[ i ] << " ";
        if( score[ i ] == best_score ) possibilities.pb( i );
    }
    //cout << endl;

    ans = rand() % possibilities.size();

    // cout << "Best " << best_score << endl;
    // cout << moves[ ans ].animal << endl;
    // cout << moves[ ans ].x_from << " " << moves[ ans ].y_from << endl;
    // cout << moves[ ans ].x_to << " " <<moves[ ans ].y_to << endl << endl;

    return moves[ possibilities[ ans ] ];
}
