#include <bits/stdc++.h>
using namespace std;

struct Edge{ int u, v, w; };

vector<Edge> edge_list;   // the ONLY storage — no int adj[n][n] anywhere

// Look up the current best-known cost from u to v by scanning the edge list.
// Returns INT_MAX if no edge (or relaxed path so far) connects u to v.
// Takes the min in case of duplicate/multi-edges between the same pair.
int getCost(int u, int v)
{
    int best = INT_MAX;
    for(auto &edge : edge_list)
    {
        if(edge.u == u && edge.v == v)
            best = min(best, edge.w);
    }
    return best;
}

// Update (or insert) the cost from u to v. If an entry for (u,v) already
// exists, its weight is overwritten in place; otherwise a new edge is
// appended. This lets edge_list double as both the input edges AND the
// working "distance table" that Floyd-Warshall keeps improving.
void setCost(int u, int v, int w)
{
    for(auto &edge : edge_list)
    {
        if(edge.u == u && edge.v == v)
        {
            edge.w = w;
            return;
        }
    }
    edge_list.push_back({u, v, w});
}

int main()
{
    int n, e;
    cin >> n >> e;

    vector<vector<vector<int>>> path(n, vector<vector<int>>(n));

    // Self-distance is 0 for every node — stored as self-loop edges
    // (u==v) instead of a matrix diagonal.
    for(int i = 0; i < n; i++)
    {
        edge_list.push_back({i, i, 0});
        path[i][i] = {i};
    }

    // Input edges
    while(e--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edge_list.push_back({a, b, c});
        path[a][b] = {a, b};
    }

    // Floyd Warshall — same k,i,j structure as always, but every
    // adj[i][j] read is a getCost() call, every write is a setCost() call.
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            int cik = getCost(i, k);        // cost(i,k) doesn't change within this j loop, so hoist it out
            if(cik == INT_MAX) continue;    // no path i->k at all, skip this i for this k

            for(int j = 0; j < n; j++)
            {
                int ckj = getCost(k, j);
                if(ckj == INT_MAX) continue;

                int newcost = cik + ckj;
                int cij = getCost(i, j);

                if(newcost < cij)
                {
                    setCost(i, j, newcost);
                    path[i][j] = path[i][k];
                    for(int x : path[k][j])
                    {
                        if(x != k)
                            path[i][j].push_back(x);
                    }
                }
            }
        }
    }

    // Check Negative Cycle
    bool negcycle = false;
    for(int i = 0; i < n; i++)
    {
        if(getCost(i, i) < 0)
        {
            negcycle = true;
            break;
        }
    }

    if(negcycle)
    {
        cout << "There is a negative cycle";
        return 0;
    }
    else
    {
        cout << "There is no negative cycle\n";
    }

    // Cost Matrix (printed as a grid for readability only — every value
    // here comes from a getCost() scan of edge_list, nothing is stored as a matrix)
    cout << "\nCost Matrix:\n";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int c = getCost(i, j);
            if(c == INT_MAX)
                cout << "INF\t";
            else
                cout << c << "\t";
        }
        cout << endl;
    }

    // Path Matrix
    cout << "\nPath Matrix:\n";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int c = getCost(i, j);
            if(c == INT_MAX)
            {
                cout << "INF\t";
            }
            else
            {
                cout << "[";
                for(int x : path[i][j])
                {
                    cout << x << " ";
                }
                cout << "]\t";
            }
        }
        cout << endl;
    }
    return 0;
}
