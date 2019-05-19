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

bool good_move( int x, int y, int xd, int yd, vector < vector < char > > BOARD, vector < vector < char > > ANIMALS, bool player, map < char, int > animal_val[]){
    // cave check
    if( xd == 0 and yd == 3 and player == 1 ) return false;
    if( xd == 8 and yd == 3 and player == 0 ) return false;

    // borders
    if( xd < 0 or xd > 8 or yd < 0 or yd > 6 ) return false;

    // my animal on destination field
    if( my_animal(ANIMALS[ xd ][ yd ], player) ) return false;

    char animal_from = ANIMALS[ x ][ y ];
    char animal_dest = ANIMALS[ xd ][ yd ];

    char board_from = BOARD[ x ][ y ];
    char board_dest = BOARD[ xd ][ yd ];


    // opponent's cave
    if( board_dest == '*' ) return true;


    // empty destination field is good
    if( animal_dest == '.' and board_dest == '.' ) return true;


    // Rat going from lake to ground cannot kill elefant
    if( board_from == '~' and animal_dest != '.' ) return false;


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
                if( player == 0 and ANIMALS[ act_x ][ act_y ] == 'R' ) return false;
                if( player == 1 and ANIMALS[ act_x ][ act_y ] == 'r' ) return false;
                act_x += vx;
                act_y += vy;
            }

            if( ANIMALS[ act_x ][ act_y ] == '.' ) return true;
            int my_power = animal_val[ player ][ animal_from ];
            int opponent_power = animal_val[ player^1 ][ ANIMALS[ act_x ][ act_y ] ];

            return my_power >= opponent_power;
        }
        else return false;
    }


    // animals collision

    // if destination animal stays in trap it dies
    if( BOARD[ xd ][ yd ] == '#' ) return true;


    int my_power = animal_val[ player ][ animal_from ];
    int opponent_power = animal_val[ player^1 ][ animal_dest ];

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

vector < one_move > gen_moves(vector < vector < char > > BOARD, vector < vector < char > > ANIMALS, bool player, map < char, int > animal_val[]){
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

                // cout << animal << endl;
                // cout << "vector " << dx[ i ] << " " << dy[ i ] << endl;
                // cout << "FROM: " << x << " " << y << endl;
                // cout << "TO: " << new_x << " " << new_y << endl << endl;

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
