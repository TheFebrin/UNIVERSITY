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

int dx[ 8 ] = {-1, 1, 1, -1, 1, -1, 0, 0};
int dy[ 8 ] = {1, 1, -1, -1, 0, 0, 1, -1};


map < pi, vpi > find_moves( vector < vector < char > > BOARD, bool player ){
    map < pi, vpi >  moves;
    vector < pi > my_pieces;

    char bad_piece, good_piece;
    if( player == 0 ){
        good_piece = 'W';
        bad_piece = 'B';
    }
    else{
        good_piece = 'B';
        bad_piece = 'W';
    }

    // find players pieces
    for(int i = 0; i < 8 ; i ++){
        for(int j = 0; j < 8 ; j ++){
            if( BOARD[ i ][ j ] == good_piece ) my_pieces.pb( { i, j } );
        }
    }

    // for each piece find move that you can make
    for(auto p: my_pieces){
        for(int i = 0; i < 8; i ++){
            int x = p.first + dx[ i ];
            int y = p.second + dy[ i ];
            bool opponent_killed = false;

            if( x < 0 or x >= 8 or y < 0 or y >= 8 ) continue;
            if( BOARD[ x ][ y ] == good_piece or BOARD[ x ][ y ] == '.' ) continue;

            int best_x = x, best_y = y;

            while( x + dx[ i ] >= 0 and x + dx[ i ] < 8 and y + dy[ i ] >= 0 and y + dy[ i ] < 8 ){
                if( BOARD[ x ][ y ] == bad_piece ) opponent_killed = true;
                x += dx[ i ];
                y += dy[ i ];
                best_x = x;
                best_y = y;
                if( BOARD[ x ][ y ] == good_piece or BOARD[ x ][ y ] == '.' ) break;
            }
            if( BOARD[ x ][ y ] == bad_piece ) opponent_killed = true;
            if( BOARD[ best_x ][ best_y ] == '.' and opponent_killed) moves[ {best_x, best_y} ].pb( p );
        }
    }

    // for(auto m : moves) cout << m.first.first << " " <<m.first.second << endl;
    // cout << endl;

    return moves;
}

int GCD(int a, int b){
    if( b == 0 ) return a;
    return GCD( b, a % b );
}

void make_move( vector < vector < char > > &BOARD , vpi moves, pi goal, int player){
    for(auto start: moves){
        int gcd = GCD( abs(start.first - goal.first), abs(start.second - goal.second) );
        int vx = ( goal.first - start.first ) / gcd;
        int vy = ( goal.second - start.second ) / gcd;

        // cout << start.first << " " << start.second << endl;
        // cout << "VECTOR : " << vx << " " << vy << endl;
        // cout << goal.first << " " << goal.second << endl << endl;

        do{
            if( player == 0 ) BOARD[ start.first ][ start.second ] = 'W';
            if( player == 1 ) BOARD[ start.first ][ start.second ] = 'B';
            start.first += vx;
            start.second += vy;
            if( player == 0 ) BOARD[ start.first ][ start.second ] = 'W';
            if( player == 1 ) BOARD[ start.first ][ start.second ] = 'B';
        }while( start.first != goal.first or start.second != goal.second );
    }
}

bool gg( vector < vector < char > >  BOARD ){
    for(int i = 0; i < 8 ; i ++){
        for(int j = 0; j < 8 ; j ++){
            if( BOARD[ i ][ j ] == '.' ) return false;
        }
    }
    return true;
}

int heuristic( vector < vector < char > >  BOARD  ){
    int ans = 0;
    for(int i = 0; i < 8 ; i ++){
        for(int j = 0; j < 8 ; j ++){
            if( BOARD[ i ][ j ] == 'W' ) ans ++;
            if( BOARD[ i ][ j ] == 'B' ) ans --;
        }
    }
    return ans;
}

int minimax( vector < vector < char > >  BOARD, int depth, int alpha, int beta, int player ){
    if(depth == 0 or gg( BOARD )){
        return heuristic(BOARD);
    }

    map < pi, vpi > moves = find_moves( BOARD, player );

    if(moves.size() == 0){
        return heuristic(BOARD);
    }

    if(player == 0){
        int maxEval = -1e9;
        for(auto m: moves){
            auto New_Board = BOARD;
            make_move( New_Board, m.second, m.first, player);
            int eval_child = minimax(New_Board, depth - 1, alpha, beta, 1);
            maxEval = max(maxEval, eval_child);
            alpha = max(alpha, eval_child);

            if(beta <= alpha) break;
        }
        return maxEval;
    }
    else{
        int minEval = +1e9;
        for(auto m: moves){
            auto New_Board = BOARD;
            make_move( New_Board, m.second, m.first, player);
            int eval_child = minimax(New_Board, depth - 1, alpha, beta, 0);
            minEval = min(minEval, eval_child);
            alpha = max(alpha, eval_child);

            if(beta <= alpha) break;
        }
        return minEval;
    }
}

pair < pi, vpi > use_minimax(vector < vector < char > >  BOARD, map < pi, vpi > moves, int player, int depth){
    int best_score = -1e9;
    pair < pi, vpi > ans;

    for(auto m: moves){
        auto New_Board = BOARD;
        make_move( New_Board, m.second, m.first, player);
        int act = minimax(New_Board, depth, -1e9, 1e9, player^1 );

        if( act > best_score ){
            best_score = act;
            ans = { m.first, m.second };
        }
    }
    return ans;
}

int game_summary( vector < vector < char > >  BOARD ){
    int white = 0, black = 0;
    for(int i = 0; i < 8 ; i ++){
        for(int j = 0; j < 8 ; j ++){
            if( BOARD[ i ][ j ] == 'W' ) white ++;
            if( BOARD[ i ][ j ] == 'B' ) black ++;
        }
    }

    if( white == black ){
        cout << "Draw " << white << " : " << black << endl;
        return 0;
    }

    if( white > black ){
        cout << "White won! " << white << " : " << black << endl;
        return 1;
    }

    if( white < black ){
        cout << "Black won " << white << " : " << black << endl;
        return 0;
    }

    return 0;
}
