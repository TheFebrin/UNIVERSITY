#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    int n;
    map < string, int > Mstring;
    map < int, string > Mint;
    vector < list < pair < int, int > > > G;
public:
    Graph(int n)
    {
        this->n = n;
        G.assign(n + 1, list < pair < int, int > >());
    }

    void add(int v, int w, int weight)
    {
        G[v].push_back({w, weight});
        G[w].push_back({v, weight});
    }

    void set_name(int v, string s)
    {
        Mstring[s] = v;
        Mint[v] = s;
    }

    void del_edge(int v, int w)
    {
        list <pair< int, int > > :: iterator it;
        for(it = G[v].begin(); it != G[v].end(); it ++)
        {
            if(it->first == w)
            {
                G[v].erase(it);
                break;
            }
        }

        for(it = G[w].begin(); it != G[w].end(); it ++)
        {
            if(it->first == v)
            {
                G[w].erase(it);
                break;
            }
        }
    }

    void change_weight(int v, int w, int new_weight)
    {
         for(auto it = G[v].begin(); it != G[v].end(); it ++)
        {
            if(it->first == w)
            {
                it->second = new_weight;
                break;
            }
        }
    }

    void print_neighbours(int v)
    {
        cout << "Neighbours of " << v << ":" << endl;
        for(auto it = G[v].begin(); it != G[v].end(); it ++)
        {
            cout << it->first << ", weight: " << it->second << endl;
        }
    }

    void delete_vertex(int v)
    {
        list <pair< int, int > > :: iterator it;
        vector < int > neighbours;
        for(it = G[v].begin(); it != G[v].end(); it ++)
        {
            neighbours.push_back(it->first);
            G[v].erase(it);
        }

        for(auto a: neighbours)
        {
            del_edge(a, v);
        }
    }
    
    void Dijkstra(int v, int w){
        long long dist[n + 1];
        int ancestor[n + 1];
        for(int i = 0; i <= n; i ++)
            dist[i] = INT_MAX;

        dist[v] = 0;
        priority_queue < pair <int, int> >Q;
        Q.push({0,v});
        
        while (!Q.empty()) {
            auto top = Q.top();
            Q.pop();
            int vertex = top.second;
    
            list <pair< int, int > > :: iterator it;
            for(it = G[vertex].begin(); it != G[vertex].end(); it ++){
                cout << vertex << " - >> " << it->first << endl;
                int w = it->first;
                int act_dist = dist[vertex] + it->second;
                
                if(act_dist < dist[w]){
                    dist[w] = act_dist;
                    ancestor[w] = vertex;
                    Q.push({-dist[w], w});
                }
            }
        }
        // for(int i = 1; i <= n; i ++) cout << dist[ i ] << " ";
        // cout << endl;
        cout << "Distance " << v << " -> " << w << " : " << dist[w] << endl;
    }
    
};

int main()
{
    Graph g = Graph(6);
    g.add(1, 2, 1);
    g.add(1, 3, 2);
    g.add(1, 4, 3);
    g.add(1, 5, 4);
    g.add(3, 6, 10);
    g.change_weight(1, 3, 22);
    g.del_edge(1, 5);
    g.print_neighbours(1);

    g.Dijkstra(1, 6);
    


    cout << "Delete node 1" << endl;
    g.delete_vertex(1);
    g.print_neighbours(1);

    return  0;
}