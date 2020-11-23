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

using namespace std;

#define FOR(i,x,n) for(int i = x; i < n; i++)
#define pb push_back

typedef tuple<int, int, int, int, int> t5;
typedef tuple<int, int, int, int, int, int> t6;
typedef tuple<int, int, int, int, int, int, int> t7;
typedef tuple<int, int, int, int, int, int, int, int> t8;

unordered_map < int, t7 > LEARN_ACTIONS;
unordered_map < int, t5 > SPELLS;

double MAX_TIME = 0.038;

int MAX_DEPTH = 10;
unsigned int MAX_SPELLS = 12;

double GAMMA = 0.5;
double PUNISH_CONSTANT = 0.01;
double FREE_SPELL_BONUS = 10;
bool arena = true;

typedef struct State{
    double score = 0.0;
    string first_move_str = "";
    int first_move_id = -1;
    int ingredients[4] = {0, 0, 0, 0};
    unordered_set < int > usedSpells;
    unordered_set < int > learn_actions;
    vector < int > Spells;
}State;

inline bool structCompare(State *A, State *B){
    return A->score > B->score;
}

unordered_set < int > CASTED_SPELLS;
int my_brew = 0, opp_brew = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    FOR(turn, 0, 1000)
    {
        double start_time = clock();
        unordered_map < int, t5 > brew_actions;
        State* actual_state = new State;
        actual_state->Spells.reserve(50);

        int actionCount; // the number of spells and recipes in play
        scanf("%d", &actionCount);
        vector < t8 > learn_actions; learn_actions.reserve(actionCount);
        vector < t6 > cast_actions; cast_actions.reserve(actionCount);

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

            // cin >> actionId >> actionType >> delta0 >> delta1 >> delta2 >> delta3 >> price >> tomeIndex >> taxCount >> castable >> repeatable; cin.ignore();
            scanf("%d%s%d%d%d%d%d%d%d%d%d", &actionId, actionType_, &delta0, &delta1, &delta2, &delta3, &price, &tomeIndex, &taxCount, &castable, &repeatable);

            string actionType = actionType_;


            // cerr << actionId << " " << actionType << " " << delta0 << " " << delta1 << " " << delta2 << " " << delta3 << " ";
            // cerr << price << " " << tomeIndex << " " << taxCount << " " << castable << " " << repeatable << endl;


            if(actionType == "BREW") brew_actions[actionId] = {delta0, delta1, delta2, delta3, price};
            if(actionType == "LEARN")
            {
                LEARN_ACTIONS[actionId] = {delta0, delta1, delta2, delta3, tomeIndex, taxCount, repeatable};
                SPELLS[actionId] = {delta0, delta1, delta2, delta3, repeatable};
                actual_state->learn_actions.insert(actionId);
                if(turn <= 20 and taxCount - tomeIndex >= -3)
                    learn_actions.pb({actionId, delta0, delta1, delta2, delta3, tomeIndex, taxCount, repeatable});
            }
            if(actionType == "CAST")
            {
                actual_state->Spells.pb(actionId);
                SPELLS[actionId] = {delta0, delta1, delta2, delta3, repeatable};
                // cast_actions.pb({actionId, delta0, delta1, delta2, delta3, repeatable});
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


        /* FIRST X TURNS ARE USED TO LEARN RECEPIES */
        // if(turn <= 1){
        //     cerr << "CONSIDERING: " << learn_actions.size() << " learn_actions." << endl;
        //     int best_rev = -10;
        //     int best_learn_action = -1;
        //     for(auto t8: learn_actions)
        //     {
        //         if(get<5>(t8) <= actual_state->ingredients[0] and get<6>(t8) - get<5>(t8) > best_rev)
        //         {
        //             best_rev = get<6>(t8) - get<5>(t8);
        //             best_learn_action = get<0>(t8);
        //         }
        //     }
        //     cerr << "Best revenue: " << best_rev << " action: " << best_learn_action << endl;
        //     if(best_rev > -10)
        //     {
        //         cout << "LEARN " << best_learn_action << " RĘKA JAK MŁOTEK NO TO CO ..." << endl;
        //         continue;
        //     }
        // }

        actual_state->usedSpells = CASTED_SPELLS;

        if(turn == 0) MAX_TIME = 0.98;

        int nodes_visited = 0, best_action_id = 0, depth = 0;
        double best_score = -1000.0;
        string best_action_str = "";

        vector < State* > LAYER[100];
        LAYER[0].reserve(1000);
        LAYER[0].pb(actual_state);

        while((clock() - start_time) / CLOCKS_PER_SEC <= MAX_TIME)
        {
            LAYER[depth + 1].reserve(1000);
            int vector_index = 0;
            for(State *actual_state: LAYER[depth])
            {
                vector_index ++;
                if(vector_index == 300) break;

                /* 1. CHECK IF I CAN BUY SOMETHING */
                vector < int > can_brew;
                can_brew.reserve(5);
                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {break;}
                for(auto &[actionId, t5]: brew_actions){
                    if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {break;}
                    int delta0, delta1, delta2, delta3, price;
                    tie(delta0, delta1, delta2, delta3, price) = t5;

                    bool can_afford = true;
                    int d1 = delta0 + actual_state->ingredients[0], d2 = delta1 + actual_state->ingredients[1];
                    int d3 = delta2 + actual_state->ingredients[2], d4 = delta3 + actual_state->ingredients[3];
                    int punish = 0;

                    if(d1 < 0) { can_afford = false; punish += d1 * d1; }
                    if(d2 < 0) { can_afford = false; punish += d2 * d2; }
                    if(d3 < 0) { can_afford = false; punish += d3 * d3; }
                    if(d4 < 0) { can_afford = false; punish += d4 * d4; }
                    if(delta0 + delta1 + delta2 + delta3 \
                        + actual_state->ingredients[0] + actual_state->ingredients[1] \
                        + actual_state->ingredients[2] + actual_state->ingredients[3] > 10
                    ) can_afford = false;

                    if(can_afford)
                    {
                        int potion_bonus = price;
                        if(price < 10) potion_bonus /= 2;
                        if(price > 15) potion_bonus *= 2;
                        actual_state->score += potion_bonus * potion_bonus;

                        if(actual_state->first_move_str == ""){
                            actual_state->first_move_str = "BREW";
                            actual_state->first_move_id = actionId;
                        }
                        can_brew.pb(actionId);

                        if(!arena){
                            cerr << "BREW " << actionId << " PRICE: " << price << " ==> " << actual_state->score << endl;
                            cerr << "FOUND SOLUTION: " << actual_state->first_move_str << " " << actual_state->first_move_id;
                            cerr << " || NODES: " <<  nodes_visited << " || DEPTH: " << depth << endl << endl;
                        }
                    }
                    else
                    {
                        // actual_state->score -= punish * PUNISH_CONSTANT;
                    }
                }

                for(auto &a: can_brew) brew_actions.erase(a);

                if((actual_state->score + depth) * pow(GAMMA, depth) > best_score)
                {
                    // cerr << "BEST: " << actual_state->score << " " << actual_state->first_move_str << endl;
                    best_score = actual_state->score;
                    best_action_str = actual_state->first_move_str;
                    best_action_id = actual_state->first_move_id;
                }

                if(actual_state->first_move_str == "BREW") actual_state->first_move_str = "";

                /* 2. CAST SPELLS */
                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {break;}
                for(auto &actionId: actual_state->Spells){
                    if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {; break;}

                    int delta0, delta1, delta2, delta3, repeatable;
                    tie(delta0, delta1, delta2, delta3, repeatable) = SPELLS[actionId];

                    bool can_afford = true;
                    if(delta0 + actual_state->ingredients[0] < 0) can_afford = false;
                    if(delta1 + actual_state->ingredients[1] < 0) can_afford = false;
                    if(delta2 + actual_state->ingredients[2] < 0) can_afford = false;
                    if(delta3 + actual_state->ingredients[3] < 0) can_afford = false;
                    if(delta0 + delta1 + delta2 + delta3 \
                        + actual_state->ingredients[0] + actual_state->ingredients[1] \
                        + actual_state->ingredients[2] + actual_state->ingredients[3] > 10
                    ) can_afford = false;

                    if(can_afford)
                    {
                        if(actual_state->usedSpells.find(actionId) != actual_state->usedSpells.end()) continue;

                        State* new_state = new State;

                        if(actual_state->first_move_str == ""){
                            new_state->first_move_str = "CAST";
                            new_state->first_move_id  = actionId;
                        }
                        else{
                            new_state->first_move_str = actual_state->first_move_str;
                            new_state->first_move_id  = actual_state->first_move_id;
                        }
                        new_state->Spells = actual_state->Spells;
                        new_state->usedSpells = actual_state->usedSpells;
                        new_state->usedSpells.insert(actionId);

                        new_state->ingredients[0] = actual_state->ingredients[0] + delta0;
                        new_state->ingredients[1] = actual_state->ingredients[1] + delta1;
                        new_state->ingredients[2] = actual_state->ingredients[2] + delta2;
                        new_state->ingredients[3] = actual_state->ingredients[3] + delta3;

                        new_state->score = actual_state->score;
                        LAYER[depth + 1].pb(new_state);
                    }
                }

                /* 3. LEARN */
                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {break;}
                if(actual_state->Spells.size() < MAX_SPELLS)
                    for(auto &actionId: actual_state->learn_actions){
                    if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {break;}

                    int delta0, delta1, delta2, delta3, learn_price, tier_0_return, repeatable;
                    tie(delta0, delta1, delta2, delta3, learn_price, tier_0_return, repeatable) = LEARN_ACTIONS[actionId];

                    if(actual_state->ingredients[0] - learn_price >= 0)
                    {
                        State* new_state = new State;
                        if(actual_state->first_move_str == ""){
                            new_state->first_move_str = "LEARN";
                            new_state->first_move_id  = actionId;
                        }
                        else{
                            new_state->first_move_str = actual_state->first_move_str;
                            new_state->first_move_id  = actual_state->first_move_id;
                        }

                        new_state->Spells = actual_state->Spells;
                        new_state->learn_actions = actual_state->learn_actions;
                        new_state->usedSpells = actual_state->usedSpells;
                        new_state->Spells.pb(actionId);
                        new_state->learn_actions.erase(actionId);

                        new_state->ingredients[0] = actual_state->ingredients[0] - learn_price;
                        new_state->ingredients[1] = actual_state->ingredients[1];
                        new_state->ingredients[2] = actual_state->ingredients[2];
                        new_state->ingredients[3] = actual_state->ingredients[3];

                        int sum = new_state->ingredients[0] + new_state->ingredients[1] \
                            + new_state->ingredients[2] + new_state->ingredients[3];
                        tier_0_return = min(tier_0_return, 10 - sum);
                        new_state->ingredients[0] += tier_0_return;

                        new_state->score = actual_state->score \
                            + delta0 + delta1 * 2 + delta2 * 3 + delta3 * 4 \
                            - learn_price + tier_0_return;

                        bool free_spell = delta0 >= 0 and  delta1 >= 0 and delta2 >= 0 and delta3 >= 0;
                        if(free_spell) new_state->score += FREE_SPELL_BONUS;

                        LAYER[depth + 1].pb(new_state);
                    }

                }

                /* 4. REST */
                if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {break;}
                if(actual_state->usedSpells.size() > 0){
                    if(depth == 0){
                        actual_state->first_move_str = "REST";
                        actual_state->first_move_id  = 0;
                    }
                    actual_state->usedSpells.clear();
                    LAYER[depth + 1].pb(actual_state);
                }

                nodes_visited ++;
            }
            if((clock() - start_time) / CLOCKS_PER_SEC >= MAX_TIME) {break;}
            sort(LAYER[depth + 1].begin(), LAYER[depth + 1].end(), structCompare);
            if(LAYER[depth + 1].size() == 0) break;

            if(!arena)cerr << "Depth: " << depth << " | SZ: " << LAYER[depth + 1].size() \
                << " | GLOBAL: " << best_score << " | Best score: " << LAYER[depth + 1][0]->score \
                << " | WORST: " << LAYER[depth + 1].back()->score << endl;
            depth ++;
            if(depth == MAX_DEPTH) break;
        }

        if(!arena){
            cerr << "BEST ACTION: " << best_action_str << " " << best_action_id << " SCORE: " << best_score << endl;
            cerr << "Depth: " << depth << " | Best score: " << LAYER[depth][0]->score << " | WORST: " << LAYER[depth].back()->score << endl;
            cerr << "TIME: " << (clock() - start_time) / CLOCKS_PER_SEC \
                << " | NODES: " << nodes_visited << " | BEST SCORE: " << best_score << " | " << best_action_str << " | " << best_action_id << endl;
        }

        if(best_action_str == "CAST"){
             CASTED_SPELLS.insert(best_action_id);
             if(arena) cout << best_action_str << " " << best_action_id << " TANIO SKÓRY NIE SPRZEDAM " << endl;
             else cout << best_action_str << " " << best_action_id << " CAST: " << nodes_visited << endl;
        }
        if(best_action_str == "LEARN"){
             if(arena) cout << best_action_str << " " << best_action_id << " REASUMUJĄC WSZYSTKIE ASPEKTY KWINTESENCJI TEMATU " << endl;
             else cout << best_action_str << " " << best_action_id << " LEARN: " << nodes_visited << endl;
        }
        if(best_action_str == "BREW"){
            if(arena) cout << best_action_str << " " << best_action_id << " POLSKA GÓRĄ! " << endl;
            else cout << best_action_str << " " << best_action_id << " BREW: " << nodes_visited << endl;
            my_brew ++;
        }
        if(best_action_str == "REST" or best_action_str==""){
            CASTED_SPELLS.clear();
            if(arena) cout << "REST" << " TO BY NIC NIE DAŁO... " << endl;
            else cout << "REST" << " REST: " << nodes_visited << endl;
        }

        cerr << "END TIME: " << (clock() - start_time) / CLOCKS_PER_SEC << endl;
   }

    return 0;
}
