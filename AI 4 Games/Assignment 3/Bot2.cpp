/* Dejwo to ziomal ®© */
#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#pragma GCC option("arch=native","tune=native","no-zero-upper")
#pragma GCC target("avx")
#include <x86intrin.h>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <queue>
#include <algorithm>
#include <math.h>
#include <bitset>

using namespace std;

#define FOR(i,x,n) for(int i = x; i < n; i++)
#define pb push_back

typedef tuple<int, int, int, int, int> t5;
typedef tuple<int, int, int, int, int, int> t6;
typedef tuple<int, int, int, int, int, int, int> t7;
typedef tuple<int, int, int, int, int, int, int, int> t8;


double MAX_TIME = 0.038;


int LAYER_SIZE = 2000;
int MAX_DEPTH = 20;
unsigned int MAX_SPELLS = 20;

int MAX_ONE_LAYER = 300;
double POTION_COEFF = 10.0;
double GAMMA = 0.9;
double FREE_SPELL_BONUS = 10;
bool arena = true;


typedef struct State{
    double score = 0.0;
    int first_move = -1; // XABC, where X is the action and ABC is id
    int ingredients[4] = {0, 0, 0, 0};
    bitset <4> potions;
    bitset <64> Spells;
    bitset <64> usedSpells;
    bitset<64> learn_actions;
}State;

bitset <64> baseSpells; // TODO GLOBAL BITSET WITH BASE SPELLS

int current_spell_id = 0;
vector < int > spell_to_hash;
vector < int > hash_to_spell;
vector < t7 > SPELLS;
vector < State* > LAYER[50];

inline bool structCompare(State *A, State *B){
    int A_score = A->score + A->ingredients[0] \
        + A->ingredients[1] * 2 + A->ingredients[2] * 3 \
        + A->ingredients[3] * 4 + 0.01 * A->Spells.count();
    int B_score = B->score + B->ingredients[0] \
        + B->ingredients[1] * 2 + B->ingredients[2] * 3 \
        + B->ingredients[3] * 4 + 0.01 * B->Spells.count();
    return A_score > B_score;
}

bitset <64> CASTED_SPELLS;
int my_brew = 0, opp_brew = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    spell_to_hash.resize(200, -1);
    hash_to_spell.resize(200, -1);
    SPELLS.resize(200, {-1, -1, -1, -1, -1, -1, -1});

    FOR(turn, 0, 1000)
    {
        double start_time = clock();
        current_spell_id = 0;

        vector < t6 > brew_actions;
        brew_actions.reserve(5);

        State* actual_state = new State;

        int actionCount;
        scanf("%d", &actionCount);
        vector < t8 > learn_actions;
        learn_actions.reserve(6);

        FOR(i, 0, actionCount) {
            int actionId; // the unique ID of this spell or recipe
            char actionType_[21]; // in the first league: BREW; later: CAST, OPPONENT_CAST, LEARN, BREW
            int delta0; // tier-0 ingredient change
            int delta1; // tier-1 ingredient change
            int delta2; // tier-2 ingredient change
            int delta3; // tier-3 ingredient change
            int price; // the price in rupees if this is a potion
            int tomeIndex; // in the first two leagues: always 0; later: the index in the tome if this is a tome spell, equal to the read-ahead tax; For brews, this is the value of the current urgency bonus
            int taxCount; // in the first two leagues: always 0; later: the amount of taxed tier-0 ingredients you gain from learning this spell; For brews, this is how many times you can still gain an urgency bonus
            int castable; // in the first league: always 0; later: 1 if this is a castable player spell
            int repeatable; // for the first two leagues: always 0; later: 1 if this is a repeatable player spell

            scanf("%d%s%d%d%d%d%d%d%d%d%d", &actionId, actionType_, &delta0, &delta1, &delta2, &delta3, &price, &tomeIndex, &taxCount, &castable, &repeatable);
            string actionType = actionType_;

            // cerr << actionId << " " << actionType << " " << delta0 << " " << delta1 << " " << delta2 << " " << delta3 << " ";
            // cerr << price << " " << tomeIndex << " " << taxCount << " " << castable << " " << repeatable << endl;

            if(actionType == "BREW") brew_actions.pb({actionId, delta0, delta1, delta2, delta3, price});
            if(actionType == "LEARN")
            {
                spell_to_hash[actionId] = current_spell_id;
                hash_to_spell[current_spell_id] = actionId;
                current_spell_id ++;
                SPELLS[spell_to_hash[actionId]] = {delta0, delta1, delta2, delta3, tomeIndex, taxCount, repeatable};
                actual_state->learn_actions[spell_to_hash[actionId]] = 1;
                if(turn <= 6 and taxCount - tomeIndex >= -3) learn_actions.pb({actionId, delta0, delta1, delta2, delta3, tomeIndex, taxCount, repeatable});
            }
            if(actionType == "CAST")
            {
                spell_to_hash[actionId] = current_spell_id;
                hash_to_spell[current_spell_id] = actionId;
                current_spell_id ++;
                SPELLS[spell_to_hash[actionId]] = {delta0, delta1, delta2, delta3, tomeIndex, taxCount, repeatable};
                actual_state->Spells[spell_to_hash[actionId]] = 1;
            }
        }

        int my_score;
        scanf("%d%d%d%d%d", &actual_state->ingredients[0], &actual_state->ingredients[1],\
            &actual_state->ingredients[2], &actual_state->ingredients[3], &my_score
        );

        int opp_inventory[4], opp_score;
        scanf("%d%d%d%d%d", &opp_inventory[0], &opp_inventory[1],\
            &opp_inventory[2], &opp_inventory[3], &opp_score
        );


        int nodes_visited = 0, best_action_id = 0, best_action_int = 0, depth = 0, best_depth = 0;
        double best_score = 0.0;
        string best_action_str = "";

        actual_state->usedSpells = CASTED_SPELLS;

        if(turn == 0){
            MAX_TIME = 0.98;
            cerr << "CREATING STATES ...\n";
            FOR(i, 0, 50)
            {
                LAYER[i].reserve(100000);
                FOR(j, 0, 100000)
                {
                    State* empty_state = new State;
                    LAYER[i].pb(empty_state);
                }
            }
        }
        else MAX_TIME = 0.038;

        /* FIRST 6 TURNS ARE USED TO LEARN RECEPIES */
        if(turn < 6){
            cerr << "CONSIDERING: " << learn_actions.size() << " learn_actions." << endl;
            int best_rev = -10;
            int best_learn_action = -1;
            for(auto t8: learn_actions)
            {
                if(get<5>(t8) <= actual_state->ingredients[0] and get<6>(t8) - get<5>(t8) > best_rev)
                {
                    best_rev = get<6>(t8) - get<5>(t8);
                    best_learn_action = get<0>(t8);
                }
            }
            cerr << "Best revenue: " << best_rev << " action: " << best_learn_action << endl;
            if(best_rev > -10)
            {
                cout << "LEARN " << best_learn_action << " RĘKA JAK MŁOTEK NO TO CO ..." << endl;
                continue;
            }
        }

        LAYER[0][0] = actual_state;

        int actual_layer_size = 1;
        while((clock() - start_time) / CLOCKS_PER_SEC <= MAX_TIME)
        {
            int id_in_next_layer = 0, tmp = 0;
            FOR(index, 0, actual_layer_size)
            {
                State *actual_state = LAYER[depth][index];

                if(index == MAX_ONE_LAYER) {cerr << "break 1\n"; break;}

                /* 1. CHECK IF I CAN BUY SOMETHING */
                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 2\n"; break;}
                int potion_id = 0;
                for(auto &[actionId, delta0, delta1, delta2, delta3, price]: brew_actions){
                    if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 3\n"; break;}
                    if(actual_state->potions[potion_id]) continue;

                    bool can_afford = true;
                    int d1 = delta0 + actual_state->ingredients[0], d2 = delta1 + actual_state->ingredients[1];
                    int d3 = delta2 + actual_state->ingredients[2], d4 = delta3 + actual_state->ingredients[3];

                    if(d1 < 0) { can_afford = false; }
                    if(d2 < 0) { can_afford = false; }
                    if(d3 < 0) { can_afford = false; }
                    if(d4 < 0) { can_afford = false; }
                    if(delta0 + delta1 + delta2 + delta3 \
                        + actual_state->ingredients[0] + actual_state->ingredients[1] \
                        + actual_state->ingredients[2] + actual_state->ingredients[3] > 10
                    ) can_afford = false;

                    if(can_afford)
                    {
                        int potion_bonus = price;
                        if(price < 10) potion_bonus /= 2;
                        if(price > 15) potion_bonus *= 2;
                        actual_state->score += POTION_COEFF * (potion_bonus) * pow(GAMMA, depth);

                        actual_state->potions[potion_id] = 1;
                        if(actual_state->first_move == -1) actual_state->first_move = 1000 + actionId;
                        LAYER[depth + 1][id_in_next_layer]->score = actual_state->score;
                        LAYER[depth + 1][id_in_next_layer]->first_move = actual_state->first_move;
                        LAYER[depth + 1][id_in_next_layer]->Spells = actual_state->Spells;
                        LAYER[depth + 1][id_in_next_layer]->usedSpells = actual_state->usedSpells;
                        LAYER[depth + 1][id_in_next_layer]->learn_actions = actual_state->learn_actions;
                        LAYER[depth + 1][id_in_next_layer]->potions = actual_state->potions;

                        LAYER[depth + 1][id_in_next_layer]->ingredients[0] = actual_state->ingredients[0];
                        LAYER[depth + 1][id_in_next_layer]->ingredients[1] = actual_state->ingredients[1];
                        LAYER[depth + 1][id_in_next_layer]->ingredients[2] = actual_state->ingredients[2];
                        LAYER[depth + 1][id_in_next_layer]->ingredients[3] = actual_state->ingredients[3];

                        id_in_next_layer ++;
                        if(id_in_next_layer >= LAYER_SIZE) {cerr << "break 4\n"; break;}
                        if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 5\n"; break;}
                        // if(!arena){
                        //     cerr << "BREW " << actionId << " PRICE: " << price << " ==> " << actual_state->score << endl;
                        //     cerr << "FOUND SOLUTION: " << actual_state->first_move / 1000 << " " << actual_state->first_move % 1000;
                        //     cerr << " || NODES: " <<  nodes_visited << " || DEPTH: " << depth << endl << endl;
                        // }
                    }
                    potion_id ++;
                }
                if(id_in_next_layer >= LAYER_SIZE) {cerr << "break 6\n"; break;}
                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 7\n"; break;}

                int actual_state_score = actual_state->score + actual_state->ingredients[0] \
                    + actual_state->ingredients[1] * 2 + actual_state->ingredients[2] * 3 \
                    + actual_state->ingredients[3] * 4 + 0.01 * actual_state->Spells.count();

                if(actual_state_score > best_score){
                    // cerr << "BEST: " << actual_state->score << " " << actual_state->first_move_str << endl;
                    best_score = actual_state_score;
                    best_action_int = actual_state->first_move;
                    best_depth = depth;
                }

                /* 2. CAST SPELLS */
                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 8\n"; break;}
                for (
                    int actionId = actual_state->Spells._Find_first();
                    actionId < (int)actual_state->Spells.size();
                    actionId = actual_state->Spells._Find_next(actionId)
                ){

                    if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 9\n"; break;}

                    if(actual_state->usedSpells[actionId]) continue;

                    int delta0, delta1, delta2, delta3, tomeIndex, taxCount, repeatable;
                    tie(delta0, delta1, delta2, delta3, tomeIndex, taxCount, repeatable) = SPELLS[actionId];

                    bool can_afford = true;
                    int d1 = delta0 + actual_state->ingredients[0], d2 = delta1 + actual_state->ingredients[1];
                    int d3 = delta2 + actual_state->ingredients[2], d4 = delta3 + actual_state->ingredients[3];

                    if(d1 < 0) { can_afford = false; }
                    if(d2 < 0) { can_afford = false; }
                    if(d3 < 0) { can_afford = false; }
                    if(d4 < 0) { can_afford = false; }
                    if(delta0 + delta1 + delta2 + delta3 \
                        + actual_state->ingredients[0] + actual_state->ingredients[1] \
                        + actual_state->ingredients[2] + actual_state->ingredients[3] > 10
                    ) can_afford = false;

                    if(can_afford)
                    {
                        if(actual_state->first_move == -1)
                            LAYER[depth + 1][id_in_next_layer]->first_move = 2000 + actionId;
                        else
                            LAYER[depth + 1][id_in_next_layer]->first_move = actual_state->first_move;

                        LAYER[depth + 1][id_in_next_layer]->Spells = actual_state->Spells;
                        LAYER[depth + 1][id_in_next_layer]->usedSpells = actual_state->usedSpells;
                        LAYER[depth + 1][id_in_next_layer]->usedSpells[actionId] = 1;

                        LAYER[depth + 1][id_in_next_layer]->ingredients[0] = actual_state->ingredients[0] + delta0;
                        LAYER[depth + 1][id_in_next_layer]->ingredients[1] = actual_state->ingredients[1] + delta1;
                        LAYER[depth + 1][id_in_next_layer]->ingredients[2] = actual_state->ingredients[2] + delta2;
                        LAYER[depth + 1][id_in_next_layer]->ingredients[3] = actual_state->ingredients[3] + delta3;
                        LAYER[depth + 1][id_in_next_layer]->potions = actual_state->potions;

                        LAYER[depth + 1][id_in_next_layer]->score = actual_state->score;
                        id_in_next_layer ++;
                        if(id_in_next_layer >= LAYER_SIZE) {cerr << "break 10\n"; break;}
                        if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 11\n"; break;}

                        if(repeatable)
                        {
                            can_afford = true;
                            if(d1 + delta0 < 0) { can_afford = false; }
                            if(d2 + delta1 < 0) { can_afford = false; }
                            if(d3 + delta2 < 0) { can_afford = false; }
                            if(d4 + delta3 < 0) { can_afford = false; }
                            if(delta0 * 2 + delta1 * 2 + delta2 * 2 + delta3 * 2 \
                                + actual_state->ingredients[0] + actual_state->ingredients[1] \
                                + actual_state->ingredients[2] + actual_state->ingredients[3] > 10
                            ) can_afford = false;

                            if(can_afford)
                            {
                                if(actual_state->first_move == -1)
                                    LAYER[depth + 1][id_in_next_layer]->first_move = 5000 + actionId;
                                else
                                    LAYER[depth + 1][id_in_next_layer]->first_move = actual_state->first_move;

                                LAYER[depth + 1][id_in_next_layer]->Spells = actual_state->Spells;
                                LAYER[depth + 1][id_in_next_layer]->usedSpells = actual_state->usedSpells;
                                LAYER[depth + 1][id_in_next_layer]->usedSpells[actionId] = 1;

                                LAYER[depth + 1][id_in_next_layer]->ingredients[0] = actual_state->ingredients[0] + 2 * delta0;
                                LAYER[depth + 1][id_in_next_layer]->ingredients[1] = actual_state->ingredients[1] + 2 * delta1;
                                LAYER[depth + 1][id_in_next_layer]->ingredients[2] = actual_state->ingredients[2] + 2 * delta2;
                                LAYER[depth + 1][id_in_next_layer]->ingredients[3] = actual_state->ingredients[3] + 2 * delta3;
                                LAYER[depth + 1][id_in_next_layer]->potions = actual_state->potions;

                                LAYER[depth + 1][id_in_next_layer]->score = actual_state->score;
                                id_in_next_layer ++;
                                if(id_in_next_layer >= LAYER_SIZE) {cerr << "break 10\n"; break;}
                                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 11\n"; break;}
                            }
                        }
                    }
                }

                /* 3. LEARN */
                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 12\n"; break;}
                if(actual_state->Spells.count() < MAX_SPELLS){
                    for (
                        int actionId = actual_state->learn_actions._Find_first();
                        actionId < (int)actual_state->learn_actions.size();
                        actionId = actual_state->learn_actions._Find_next(actionId)
                    ){
                        if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 13\n"; break;}

                        int delta0, delta1, delta2, delta3, learn_price, tier_0_return, repeatable;
                        tie(delta0, delta1, delta2, delta3, learn_price, tier_0_return, repeatable) = SPELLS[actionId];

                        if(actual_state->ingredients[0] - learn_price >= 0)
                        {
                            if(actual_state->first_move == -1)
                                LAYER[depth + 1][id_in_next_layer]->first_move = 3000 + actionId;
                            else
                                LAYER[depth + 1][id_in_next_layer]->first_move = actual_state->first_move;

                            LAYER[depth + 1][id_in_next_layer]->Spells = actual_state->Spells;
                            LAYER[depth + 1][id_in_next_layer]->learn_actions = actual_state->learn_actions;
                            LAYER[depth + 1][id_in_next_layer]->learn_actions[actionId] = 0;
                            LAYER[depth + 1][id_in_next_layer]->usedSpells = actual_state->usedSpells;
                            LAYER[depth + 1][id_in_next_layer]->Spells[actionId] = 1;

                            LAYER[depth + 1][id_in_next_layer]->potions = actual_state->potions;

                            LAYER[depth + 1][id_in_next_layer]->ingredients[0] = actual_state->ingredients[0] - learn_price;
                            LAYER[depth + 1][id_in_next_layer]->ingredients[1] = actual_state->ingredients[1];
                            LAYER[depth + 1][id_in_next_layer]->ingredients[2] = actual_state->ingredients[2];
                            LAYER[depth + 1][id_in_next_layer]->ingredients[3] = actual_state->ingredients[3];

                            int sum = LAYER[depth + 1][id_in_next_layer]->ingredients[0] \
                                + LAYER[depth + 1][id_in_next_layer]->ingredients[1] \
                                + LAYER[depth + 1][id_in_next_layer]->ingredients[2] \
                                + LAYER[depth + 1][id_in_next_layer]->ingredients[3];

                            tier_0_return = min(tier_0_return, 10 - sum);
                            LAYER[depth + 1][id_in_next_layer]->ingredients[0] += tier_0_return;

                            LAYER[depth + 1][id_in_next_layer]->score = actual_state->score;
                            bool free_spell = delta0 >= 0 and  delta1 >= 0 and delta2 >= 0 and delta3 >= 0;
                            if(free_spell) LAYER[depth + 1][id_in_next_layer]->score += FREE_SPELL_BONUS;

                            id_in_next_layer ++;
                            if(id_in_next_layer >= LAYER_SIZE) {cerr << "break 14\n"; break;}
                            if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 15\n"; break;}
                        }
                    }
                }

                /* 4. REST */
                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 16\n"; break;}
                if(actual_state->usedSpells.count() > 0){
                    LAYER[depth + 1][id_in_next_layer]->score = actual_state->score;
                    LAYER[depth + 1][id_in_next_layer]->Spells = actual_state->Spells;
                    LAYER[depth + 1][id_in_next_layer]->usedSpells.reset();
                    LAYER[depth + 1][id_in_next_layer]->learn_actions = actual_state->learn_actions;
                    LAYER[depth + 1][id_in_next_layer]->potions = actual_state->potions;

                    LAYER[depth + 1][id_in_next_layer]->ingredients[0] = actual_state->ingredients[0];
                    LAYER[depth + 1][id_in_next_layer]->ingredients[1] = actual_state->ingredients[1];
                    LAYER[depth + 1][id_in_next_layer]->ingredients[2] = actual_state->ingredients[2];
                    LAYER[depth + 1][id_in_next_layer]->ingredients[3] = actual_state->ingredients[3];

                    if(actual_state->first_move == -1)
                        LAYER[depth + 1][id_in_next_layer]->first_move = 4000;
                    else
                        LAYER[depth + 1][id_in_next_layer]->first_move = actual_state->first_move;

                    id_in_next_layer ++;
                }

                nodes_visited ++;
            }
            if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {cerr << "break 17\n"; break;}
            if(id_in_next_layer == 0) {cerr << "break 18\n"; break;};
            sort(LAYER[depth + 1].begin(), LAYER[depth + 1].begin() + min(id_in_next_layer, MAX_ONE_LAYER), structCompare);
            actual_layer_size = id_in_next_layer;

            if(!arena)cerr << "Depth: " << depth << " | SZ: " << id_in_next_layer \
                << " | GLOBAL: " << best_score << " | Best score: " << LAYER[depth + 1][0]->score \
                << " | WORST: " << LAYER[depth + 1].back()->score << " | T: " \
                << (clock() - start_time) / CLOCKS_PER_SEC << " | " << ((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) << endl;
            depth ++;
            if(depth == MAX_DEPTH) break;
        }

        cerr << "best_action_int: " << best_action_int << " / " << best_action_int / 1000 << endl;
        best_action_id = best_action_int % 1000;
        if(best_action_int / 1000 == 1) best_action_str = "BREW";
        else if(best_action_int / 1000 == 2) best_action_str = "CAST";
        else if(best_action_int / 1000 == 3) best_action_str = "LEARN";
        else if(best_action_int / 1000 == 4) best_action_str = "REST";
        else if(best_action_int / 1000 == 5) best_action_str = "CAST2";
        else{
            cerr << "WARNING!\nWARNING!\n" << endl;
            best_action_str = "REST";
        }

        if(!arena){
            cerr << "Depth: " << depth << " | Best score: " << LAYER[depth][0]->score \
                << " | WORST: " << LAYER[depth].back()->score << endl;
            cerr << "TIME: " << (clock() - start_time) / CLOCKS_PER_SEC \
                << " | NODES: " << nodes_visited << " | BEST SCORE: " << best_score \
                << " BEST DEPTH: " << best_depth << " |+| "<< best_action_str << " | " << best_action_id << endl;
        }

        if(best_action_str == "CAST"){
             CASTED_SPELLS[best_action_id] = 1;
             best_action_id = hash_to_spell[best_action_id];
             if(arena) cout << best_action_str << " " << best_action_id << " TANIO SKÓRY NIE SPRZEDAM " << endl;
             else cout << best_action_str << " " << best_action_id << " CAST: " << nodes_visited << endl;
        }
        if(best_action_str == "CAST2"){
             CASTED_SPELLS[best_action_id] = 1;
             best_action_id = hash_to_spell[best_action_id];
             if(arena) cout << "CAST" << " " << best_action_id << " 2 MOJA LEWA RĘKA TO ŚMIERĆ... " << endl;
             else cout << "CAST" << " " << best_action_id << " 2 CAST222: " << best_action_id << " | " << nodes_visited << endl;
        }
        if(best_action_str == "LEARN"){
            best_action_id = hash_to_spell[best_action_id];
             if(arena) cout << best_action_str << " " << best_action_id << " REASUMUJĄC WSZYSTKIE ASPEKTY KWINTESENCJI TEMATU " << endl;
             else cout << best_action_str << " " << best_action_id << " LEARN: " << nodes_visited << endl;
        }
        if(best_action_str == "BREW"){
            if(arena) cout << best_action_str << " " << best_action_id << " POLSKA GÓRĄ! " << endl;
            else cout << best_action_str << " " << best_action_id << " BREW: " << nodes_visited << endl;
            my_brew ++;
        }
        if(best_action_str == "REST" or best_action_str==""){
            CASTED_SPELLS.reset();
            if(arena) cout << "REST" << " TO BY NIC NIE DAŁO... " << endl;
            else cout << "REST" << " REST: " << nodes_visited << endl;
        }

        cerr << "END TIME: " << (clock() - start_time) / CLOCKS_PER_SEC << endl;
   }

    return 0;
}
