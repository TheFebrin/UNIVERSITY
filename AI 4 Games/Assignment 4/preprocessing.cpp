/* Dejwo to ziomal ®© */
#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline")
#pragma GCC option("arch=native","tune=native","no-zero-upper")
#pragma GCC target("avx")
#include <x86intrin.h>
#include <bits/stdc++.h>

using namespace std;

#define FOR(i,x,n) for(int i = x; i < n; i++)
#define pb push_back


char MAP[100][100];
bool PRIMARY_JP[100][100][4];
int DISTANCES[100][100][4];
int DIAGONAL[100][100][4];

int m; // Width of the map
int n; // Height of the map

/*
 0 - LEFT
 1 - RIGHT
 2 - TOP
 3 - BOTTOM
*/

void find_primary_jump_points()
{

    FOR(i, 0, n)
    {
        /* LEFT RIGHT */
        FOR(j, 0, m)
        {
            if(MAP[i][j] == '#') continue;

            /* TOP FORCED NEIGHBOUR */
            if(i - 1 >= 0 and MAP[i - 1][j] == '#' and j + 1 < m \
                and MAP[i][j + 1] == '.' and MAP[i - 1][j + 1] == '.')
            {
                PRIMARY_JP[i][j + 1][2] = true;
            }

            /* BOTTOM FORCED NEIGHBOUR */
            if(i + 1 < n and MAP[i + 1][j] == '#' and j + 1 < m \
                and MAP[i][j + 1] == '.' and MAP[i + 1][j + 1] == '.')
            {
                PRIMARY_JP[i][j + 1][3] = true;
            }
        }

        /* RIGHT LEFT */
        for(int j = m - 1; j >= 0; j --)
        {
            if(MAP[i][j] == '#') continue;

            /* TOP FORCED NEIGHBOUR */
            if(i - 1 >= 0 and MAP[i - 1][j] == '#' and j - 1 >= 0 \
                and MAP[i][j - 1] == '.' and MAP[i - 1][j - 1] == '.')
            {
                PRIMARY_JP[i][j - 1][2] = true;
            }

            /* BOTTOM FORCED NEIGHBOUR */
            if(i + 1 < n and MAP[i + 1][j] == '#' and j - 1 < m \
                and MAP[i][j - 1] == '.' and MAP[i + 1][j - 1] == '.')
            {
                PRIMARY_JP[i][j - 1][3] = true;
            }
        }
    }

    FOR(j, 0, m)
    {
        /* TOP DOWN */
        FOR(i, 0, n)
        {
            if(MAP[i][j] == '#') continue;

            /* LEFT FORCED NEIGHBOUR */
            if(j - 1 >= 0 and MAP[i][j - 1] == '#' and i + 1 < n \
                and MAP[i + 1][j] == '.' and MAP[i + 1][j - 1] == '.')
            {
                PRIMARY_JP[i + 1][j][0] = true;
            }

            /* RIGHT FORCED NEIGHBOUR */
            if(j + 1 < m and MAP[i][j + 1] == '#' and i + 1 < n \
                and MAP[i + 1][j] == '.' and MAP[i + 1][j + 1] == '.')
            {
                PRIMARY_JP[i + 1][j][1] = true;
            }
        }

        /* DOWN TOP */
        for(int i = n - 1; i >= 0; i --)
        {
            if(MAP[i][j] == '#') continue;

            /* LEFT FORCED NEIGHBOUR */
            if(j - 1 >= 0 and MAP[i][j - 1] == '#' and i - 1 >= 0 \
                and MAP[i - 1][j] == '.' and MAP[i - 1][j - 1] == '.')
            {
                PRIMARY_JP[i - 1][j][0] = true;
            }

            /* RIGHT FORCED NEIGHBOUR */
            if(j + 1 < m and MAP[i][j + 1] == '#' and i - 1 >= 0 \
                and MAP[i - 1][j] == '.' and MAP[i - 1][j + 1] == '.')
            {
                PRIMARY_JP[i - 1][j][1] = true;
            }
        }
    }
}

void find_straight_jump_points()
{
    FOR(i, 0, n)
    {
        int dist = 0;
        bool meet = false;
        FOR(j, 0, m)
        {
            if(MAP[i][j] == '#')
            {
                meet = false;
                dist = 0;
                continue;
            }
            
            if(meet) DISTANCES[i][j][0] = dist;
            else DISTANCES[i][j][0] = -dist;

            if(PRIMARY_JP[i][j][1])
            {
                meet = true;
                dist = 0;
            }

            dist ++;
        }

        dist = 0;
        meet = false;
        for(int j = m - 1; j >= 0; j --)
        {
            if(MAP[i][j] == '#')
            {
                meet = false;
                dist = 0;
                continue;
            }
            
            if(meet) DISTANCES[i][j][1] = dist;
            else DISTANCES[i][j][1] = -dist;

            if(PRIMARY_JP[i][j][0])
            {
                meet = true;
                dist = 0;
            }

            dist ++;
        }
    }

     FOR(j, 0, m)
    {
        int dist = 0;
        bool meet = false;
        FOR(i, 0, n)
        {
            if(MAP[i][j] == '#')
            {
                meet = false;
                dist = 0;
                continue;
            }
            
            if(meet) DISTANCES[i][j][2] = dist;
            else DISTANCES[i][j][2] = -dist;

            if(PRIMARY_JP[i][j][3])
            {
                meet = true;
                dist = 0;
            }

            dist ++;
        }

        dist = 0;
        meet = false;
        for(int i = n - 1; i >= 0; i --)
        {
            if(MAP[i][j] == '#')
            {
                meet = false;
                dist = 0;
                continue;
            }
            
            if(meet) DISTANCES[i][j][3] = dist;
            else DISTANCES[i][j][3] = -dist;

            if(PRIMARY_JP[i][j][2])
            {
                meet = true;
                dist = 0;
            }

            dist ++;
        }
    }
}


int WEST = 0, EAST = 1, NORTH = 2, SOUTH = 3;
int NORTH_WEST = 0, NORTH_EAST = 1, SOUTH_EAST = 2, SOUTH_WEST = 3;

void fill_diagonals()
{
    /*
    0 - TOP LEFT
    1 - TOP RIGHT
    2 - BOTTOM RIGHT
    3 - BOTTOM LEFT
    */



    FOR(i, 0, n)
    {
        FOR(j, 0, m)
        {
            if(MAP[i][j] == '#') continue;

            if(i == 0 or j == 0 or (i - 1 >= 0 and MAP[i - 1][j] == '#') \
                or (j - 1 >= 0 and MAP[i][j - 1] == '#') \
                or (i - 1 >= 0 and j - 1 >= 0 and MAP[i - 1][j - 1] == '#'))
            {
                DIAGONAL[i][j][NORTH_WEST] = 0;
            }
            else if(i - 1 >= 0 and MAP[i - 1][j] != '#' and j - 1 >= 0 and MAP[i][j - 1] != '#' \
                and (DISTANCES[i - 1][j - 1][NORTH] > 0 or DISTANCES[i - 1][j - 1][WEST] > 0))
            {
                DIAGONAL[i][j][NORTH_WEST] = 1;
            }
            else if(i - 1 >= 0 and j - 1 >= 0)
            {
                int dist = DIAGONAL[i - 1][j - 1][NORTH_WEST];

                if(dist > 0) DIAGONAL[i][j][NORTH_WEST] = dist + 1;
                else DIAGONAL[i][j][NORTH_WEST] = dist - 1;

                // cerr << "Act: " << i << " " << j << " | PREV | " << dist << endl;
            }
        }
    }


    FOR(i, 0, n)
    {
        for(int j = m - 1; j >= 0; j --)
        {
            if(MAP[i][j] == '#') continue;

            if(i == 0 or j == m - 1 or (i - 1 >= 0 and MAP[i - 1][j] == '#') \
                or (j + 1 < m and MAP[i][j + 1] == '#') \
                or (i - 1 >= 0 and j + 1 < m and MAP[i - 1][j + 1] == '#'))
            {
                DIAGONAL[i][j][NORTH_EAST] = 0;
            }
            else if(i - 1 >= 0 and MAP[i - 1][j] != '#' and j + 1 < m and MAP[i][j + 1] != '#' \
                and (DISTANCES[i - 1][j + 1][NORTH] > 0 or DISTANCES[i - 1][j + 1][EAST] > 0))
            {
                DIAGONAL[i][j][NORTH_EAST] = 1;
            }
            else if(i - 1 >= 0 and j + 1 < m)
            {
                int dist = DIAGONAL[i - 1][j + 1][NORTH_EAST];

                if(dist > 0) DIAGONAL[i][j][NORTH_EAST] = dist + 1;
                else DIAGONAL[i][j][NORTH_EAST] = dist - 1;
            }
        }
    }


    for(int i = n - 1; i >= 0; i --)
    {
        FOR(j, 0, m)
        {
            if(MAP[i][j] == '#') continue;

            if(i == n - 1 or j == 0 or (j - 1 >= 0 and MAP[i][j - 1] == '#') \
                or (i + 1 < n and MAP[i + 1][j - 1] == '#') \
                or (i + 1 < n and j >= 0 and MAP[i + 1][j] == '#'))
            {
                DIAGONAL[i][j][SOUTH_WEST] = 0;
            }
            else if(i + 1 < n and j - 1 >= 0 \
                and (DISTANCES[i + 1][j - 1][SOUTH] > 0 or DISTANCES[i + 1][j - 1][WEST] > 0))
            {
                DIAGONAL[i][j][SOUTH_WEST] = 1;
            }
            else if(i + 1 < n and j - 1 >= 0)
            {
                int dist = DIAGONAL[i + 1][j - 1][SOUTH_WEST];

                if(dist > 0) DIAGONAL[i][j][SOUTH_WEST] = dist + 1;
                else DIAGONAL[i][j][SOUTH_WEST] = dist - 1;
            }
        }
    }


    for(int i = n - 1; i >= 0; i --)
    {
        for(int j = m - 1; j >= 0; j --)
        {
            if(MAP[i][j] == '#') continue;

            if(i == n - 1 or j == m - 1 or (j + 1 < m and MAP[i][j + 1] == '#') \
                or (i + 1 < n and j + 1 < m and MAP[i + 1][j + 1] == '#') \
                or (i + 1 < n and j >= 0 and MAP[i + 1][j] == '#'))
            {
                DIAGONAL[i][j][SOUTH_EAST] = 0;
            }
            else if(i + 1 < n and j + 1 < m \
                and (DISTANCES[i + 1][j + 1][SOUTH] > 0 or DISTANCES[i + 1][j + 1][EAST] > 0))
            {
                DIAGONAL[i][j][SOUTH_EAST] = 1;
            }
            else if(i + 1 < n and j + 1 < m)
            {
                int dist = DIAGONAL[i + 1][j + 1][SOUTH_EAST];

                if(dist > 0) DIAGONAL[i][j][SOUTH_EAST] = dist + 1;
                else DIAGONAL[i][j][SOUTH_EAST] = dist - 1;
            }
        }
    }


}

int main()
{
    cin >> m >> n; cin.ignore();
    FOR(i, 0, n) {
        string row; // A single row of the map consisting of passable terrain ('.') and walls ('#')
        cin >> row; cin.ignore();
        FOR(j, 0, m){
            MAP[i][j] = row[j];
        }
    }

    find_primary_jump_points();
    find_straight_jump_points();
    fill_diagonals();

    FOR(i, 0, n)
    {
        FOR(j, 0, m)
        {
            int s = 0;
            FOR(k, 0, 4) s += PRIMARY_JP[i][j][k];
            
            if(MAP[i][j] == '#') cerr << "# ";
            else cerr << s << " ";
        }
        cerr << endl;
    }

    cerr << endl;

    FOR(i, 0, n)
    {
        FOR(j, 0, m)
        {
            if(MAP[i][j] == '#') cerr << "# ";
            else cerr << DISTANCES[i][j][0] + DISTANCES[i][j][2] << " ";
        }
        cerr << endl;
    }

    cerr << endl;

    /*
    0 - TOP LEFT
    1 - TOP RIGHT
    2 - BOTTOM RIGHT
    3 - BOTTOM LEFT
    */

    FOR(i, 0, n)
    {
        FOR(j, 0, m)
        {
            if(MAP[i][j] == '#') cerr << "# ";
            else cerr << DIAGONAL[i][j][0] << " ";
        }
        cerr << endl;
    }


    // For each empty tile of the map, a line containing "column row N NE E SE S SW W NW".
    FOR(i, 0, n)
    {
        FOR(j, 0, m)
        {
            if(MAP[i][j] == '#') continue;

            cout << j << " " << i << " " << DISTANCES[i][j][2] << " " << DIAGONAL[i][j][NORTH_EAST] << " ";
            cout << DISTANCES[i][j][1] << " " << DIAGONAL[i][j][SOUTH_EAST] << " ";
            cout << DISTANCES[i][j][3] << " " << DIAGONAL[i][j][SOUTH_WEST] << " ";
            cout << DISTANCES[i][j][0] << " " << DIAGONAL[i][j][NORTH_WEST] << endl;
        }
    }

    /*
    0 - LEFT
    1 - RIGHT
    2 - TOP
    3 - BOTTOM
    */
}