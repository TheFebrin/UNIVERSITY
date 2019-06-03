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
typedef vector < vector < char > > vvc;

int dx[ 4 ] = {0, 0, 1, -1};
int dy[ 4 ] = {1, -1, 0, 0};
int max_games = 30;

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

bool good_move( int x, int y, int xd, int yd, vvc BOARD, vvc ANIMALS, bool player, map < char, int > animal_val){
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
    // TODO: my trap shouldn't weaken my animals
    if( BOARD[ xd ][ yd ] == '#' ) return true;


    int my_power = animal_val[ animal_from ];
    int opponent_power = animal_val[ animal_dest ];

    // rat killing elefant
    if( my_power == 0 and opponent_power == 7 ) return true;
    if( my_power == 7 and opponent_power == 0 ) return false;

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


int game_over( vvc ANIMALS, map < char, int > animal_val){
    // returns -1 if player 0 won, 1 if player 1 won
    vi A1, A2;
    for(int i = 0; i < 9 ; i ++){
        for(int j = 0; j < 7 ; j ++){
            if( ANIMALS[ i ][ j ] < 96 and ANIMALS[ i ][ j ] > 64 ) // player 1 - big letters
            {
              A1.pb( animal_val[ ANIMALS[ i ][ j ] ] );
            }
            if( ANIMALS[ i ][ j ] > 96 ) //player 0 has small letters
            {
              A2.pb( animal_val[ ANIMALS[ i ][ j ] ] );
            }
        }
    }
    sort( A1.rbegin(), A1.rend() );
    sort( A2.rbegin(), A2.rend() );

    for(int i = 0; i < (int)min(A1.size(), A2.size()); i ++){
      if( A1[ i ] > A2[ i ] ) return 1;
      if( A2[ i ] > A1[ i ] ) return -1;
    }

    return 1;
}

pi move_over_lake(vvc BOARD, int x, int y, int x_to, int y_to){

    int vx = x_to - x;
    int vy = y_to - y;

    int act_x = x_to, act_y = y_to;
    while( BOARD[ act_x ][ act_y ] == '~' ){
        act_x += vx;
        act_y += vy;
    }

    return {act_x, act_y};
}


int play(vvc ANIMALS, vvc BOARD, map < char, int > animal_val, bool player){
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

one_move simulate(vector < one_move > moves , vvc BOARD, vvc ANIMALS, bool player, int N, map < char, int > animal_val){
    int number_of_moves = (int)moves.size();
    vi score( number_of_moves, 0);
    vector < vvc > States;

    for(auto move: moves){
        auto New_Animals = ANIMALS;
        New_Animals[ move.x_from ][ move.y_from ] = '.';
        New_Animals[ move.x_to ][ move.y_to ] = move.animal;
        States.pb( New_Animals );
    }

    int act_state = 0;

    while( N > 0 ){
        act_state %= number_of_moves;

        int result = play(States[ act_state ], BOARD, animal_val, player^1);
        N --;
        score[ act_state ] += result;

        act_state ++;
    }

    // if few moves have similar score we move random one

    int best_score = *max_element(score.begin(), score.end());
    vi possibilities;

    for(int i = 0; i < number_of_moves; i ++){
        if(score[ i ] == best_score){
            possibilities.pb( i );
        }
    }
    srand(time(NULL));
    int choice = rand() % possibilities.size();

    for(int i = 0 ; i < (int)score.size(); i ++) cout << moves[ i ].animal << " ";
    cout << endl;
    for(int i = 0 ; i < (int)score.size(); i ++) cout << score[ i ] << " ";
    cout << endl;

    // cout << "Best move: \n";
    // cout << moves[ possibilities[ choice ] ].animal << endl;
    // cout << moves[ possibilities[ choice ] ].x_from << " " << moves[ possibilities[ choice ] ].y_from << endl;
    // cout << moves[ possibilities[ choice ] ].x_to << " " << moves[ possibilities[ choice ] ].y_to << endl << endl;


    return moves[ possibilities[ choice ] ];
}

/* ---- MCTS ---- */

typedef struct{
    int node_no;
    int father;

    vvc ANIMALS;

    bool leaf;
    int player;

    double games_won;
    double games_total;

}MCTS;

int end_rollout( vvc ANIMALS, map < char, int > animal_val){
    // returns -1 if player 0 won, 1 if player 1 won
    vi A1, A2;
    int P1 = 0, P2 = 0;
    for(int i = 0; i < 9 ; i ++){
        for(int j = 0; j < 7 ; j ++){
            if( ANIMALS[ i ][ j ] < 96 and ANIMALS[ i ][ j ] > 64 ) // player 1 - big letters
            {
              A1.pb( animal_val[ ANIMALS[ i ][ j ] ] );
              P1 += animal_val[ ANIMALS[ i ][ j ] ];
            }
            if( ANIMALS[ i ][ j ] > 96 ) //player 0 has small letters
            {
              A2.pb( animal_val[ ANIMALS[ i ][ j ] ] );
              P2 += animal_val[ ANIMALS[ i ][ j ] ];
            }
        }
    }
    sort( A1.rbegin(), A1.rend() );
    sort( A2.rbegin(), A2.rend() );

    for(int i = 0; i < (int)min(A1.size(), A2.size()); i ++){
      if( A1[ i ] > A2[ i ] ) return 1;
      if( A2[ i ] > A1[ i ] ) return 0;
    }
    return 0;
  //  return P1 - P2;
}

int rollout(vvc ANIMALS, vvc BOARD, map < char, int > animal_val, bool player){
    int moves_no = 0;
    int score = 0;
    int moves_without_kill = 0;

    vector < one_move > moves = gen_moves(BOARD, ANIMALS, player, animal_val);

    if( player == 1 ){
      int best_score = 0;
      int some_move = 0;
      for(int i = 0; i < int(moves.size()); i ++){
        auto m = moves[ i ];
        if( ANIMALS[ m.x_to ][ m.y_to ] != '.' ){
          int act_score = animal_val[ ANIMALS[ m.x_to ][ m.y_to ] ];
          if( act_score > best_score ){
            best_score = act_score;
            some_move = i;
          }
        }
      }
      one_move m = moves[ some_move ];
      if( m.animal == 't' or m.animal == 'T' or m.animal == 'l' or m.animal == 'L'){
             auto np = move_over_lake( BOARD, m.x_from, m.y_from, m.x_to, m.y_to);
             m.x_to = np.first;
             m.y_to = np.second;
         }

      ANIMALS[ m.x_from ][ m.y_from ] = '.';
      ANIMALS[ m.x_to ][ m.y_to ] = m.animal;
      if( best_score ) return ( end_rollout( ANIMALS, animal_val ));
    }

    while( true ){
        moves = gen_moves(BOARD, ANIMALS, player, animal_val);

         if( moves_without_kill == max_games or moves.size() == 0){
            score = end_rollout( ANIMALS, animal_val );
            return score;
        }

        int best_move = rand() % moves.size();

        int best_score = 0;
        if( player == 1 ){
          for(int i = 0; i < int(moves.size()); i ++){
            auto m = moves[ i ];
            if( ANIMALS[ m.x_to ][ m.y_to ] != '.' ){
              int act_score = animal_val[ ANIMALS[ m.x_to ][ m.y_to ] ];
              if( act_score > best_score ){
                best_score = act_score;
                best_move = i;
              }
            }
          }
        }

        one_move m = moves[ best_move ];

        if( ANIMALS[ m.x_to ][ m.y_to ] == '.' ) moves_without_kill ++;
        else moves_without_kill = 0;

     if( m.animal == 't' or m.animal == 'T' or m.animal == 'l' or m.animal == 'L'){
            auto np = move_over_lake( BOARD, m.x_from, m.y_from, m.x_to, m.y_to);
            m.x_to = np.first;
            m.y_to = np.second;
        }

        ANIMALS[ m.x_from ][ m.y_from ] = '.';
        ANIMALS[ m.x_to ][ m.y_to ] = m.animal;

        if( best_score ) return ( end_rollout( ANIMALS, animal_val ));

        player ^= 1;
        moves_no ++;
    }
    return 0;
}

void DFS( vi G[], int v, int anc, map < int, MCTS > M ) {
    cout << "act: " << v << " score:  " << M[ v ].games_won << " / " << M[ v ].games_total << endl;
    for(auto w: G[ v ]){
      if( w != anc ) DFS( G, w, v, M);
    }
}

double UCB(double won, double node_visited, double parent_visited, int player ){
  if( player == 0 ) won = node_visited - won;
  double ans = won / node_visited * 2 * sqrt( log( parent_visited ) / node_visited );
  return ans;
}

one_move simulate2(vvc BOARD, vvc ANIMALS, bool player, map < char, int > animal_val, double time_limit){
    cout << "MCTS:\n";
    double act_time = clock();
    int TreeSize = 100000;

    map < int, MCTS > M;
    vector < int > G[ TreeSize ];
    bool visited[ TreeSize ];
    int all_nodes = 1;
    for(int i = 0; i < TreeSize; i ++ ){
      visited[ i ] = false;
      G[ i ].clear();
    }

    MCTS root;
    root.node_no = 1;
    root.father = -1;
    root.ANIMALS = ANIMALS;
    root.leaf = true;
    root.games_won = 0;
    root.games_total = 0;
    root.player = player;

    M[ 1 ] = root;

    vector < one_move > moves_from_root = gen_moves(BOARD, ANIMALS, player, animal_val);

    int move = 0;
    while ( (clock() - act_time) / CLOCKS_PER_SEC < time_limit ) {
      int act_node = 1;
      MCTS vals = M[ act_node ];
      move ++;

      while( !vals.leaf ){
        int best_son = G[ act_node ][ rand() % G[ act_node ].size() ];
        double score = -1;

        for(auto w: G[ act_node ]){
          MCTS w_vals = M[ w ];
          if( w_vals.games_total == 0 ){
            best_son = w;
            break;
          }

          double w_score = UCB(w_vals.games_won, w_vals.games_total, vals.games_total, vals.player);

          if( w_score > score ){
            score = w_score;
            best_son = w;
          }
        }

        act_node = best_son;
        vals = M[ best_son ];
      }

      // IN LEAF AT THIS POINT

      if( visited[ act_node ] ){
        // GENERATE STATES

        M[ act_node ].leaf = false;
        vector < one_move > moves = gen_moves(BOARD, vals.ANIMALS, vals.player, animal_val);

        vector < vvc > States;
        for(auto move: moves){
            auto New_Animals = vals.ANIMALS;
            New_Animals[ move.x_from ][ move.y_from ] = '.';
            New_Animals[ move.x_to ][ move.y_to ] = move.animal;
            States.pb( New_Animals );
        }

        for(auto s: States){
          all_nodes ++;
          G[ act_node ].pb( all_nodes );

          MCTS tmp;
          tmp.node_no = all_nodes;
          tmp.ANIMALS = s;
          tmp.father = act_node;
          tmp.leaf = true;
          tmp.games_won = 0;
          tmp.games_total = 0;
          tmp.player = !vals.player;

          M[ all_nodes ] = tmp;
        }
      }
      else{

        visited[ act_node ] = true;
        // ROLLOUT
        int score = rollout(vals.ANIMALS, BOARD, animal_val, vals.player);
        if( score == -1 ) score = 0;
        // BACKTRACK

        while( act_node != -1 ){
          auto it = M.find( act_node );
          it->second.games_won += score;
          it->second.games_total ++;
          act_node = it->second.father;
        }

    //    cout << " Ended: " << act_node << endl;
      }
    }

    cout << "Nodes explored: " << all_nodes << "\n";
    cout << "MCTS duration: " << (clock() - act_time) / CLOCKS_PER_SEC << " sec\n";

    cout << "Scores: \n";
    // for(auto w: G[ 1 ]){
    //   cout << M[ w ].node_no << " ";
    // } cout << "\n";
    for(auto w: G[ 1 ]){
      cout << M[ w ].games_won << " ";
    } cout << "\n";
    for(auto w: G[ 1 ]){
      cout << M[ w ].games_total << " ";
    } cout << "\n";
    cout << "Possible moves: \n";
    for(auto a: moves_from_root) cout << a.animal << " ";
    cout << "\n";

    double best_score = 0;
    int answer = 0;
    for(int i = 0 ; i < (int)G[ 1 ].size(); i ++){
      MCTS m = M[ G[ 1 ][ i ] ];
      if( m.games_total == 0 ) continue;
      double act_score = double(m.games_won) / double(m.games_total);
      if( act_score > best_score ){
        best_score = act_score;
        answer = i;
      }
    }

    // cout << "Explore tree: \n";
    // cout << all_rols << endl;
    // DFS( G, 1, -1, M);

    return moves_from_root[ answer ];
}
