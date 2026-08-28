#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, e;
    cin >> n >> e;

    int adj[n][n];

    vector<vector<vector<int>>> path(n, vector<vector<int>>(n));

    // Initialize
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
            {
                adj[i][j] = 0;
                path[i][j] = {i};
            }
            else
            {
                adj[i][j] = INT_MAX;
            }
        }
    }

    // Input edges
    while(e--)
    {
        int a, b, c;
        cin >> a >> b >> c;

        adj[a][b] = c;
        path[a][b] = {a, b};
    }

    // Floyd Warshall
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(adj[i][k] != INT_MAX && adj[k][j] != INT_MAX)
                {
                    int newcost = adj[i][k] + adj[k][j];

                    if(newcost < adj[i][j])
                    {
                        adj[i][j] = newcost;

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
    }

    // Check Negative Cycle
    bool negcycle = false;

    for(int i = 0; i < n; i++)
    {
        if(adj[i][i] < 0)
        {
            negcycle = true;
            break;
        }
    }

    // Negative Cycle Result
    if(negcycle)
    {
        cout << "There is a negative cycle";
        return 0;
    }
    else
    {
        cout << "There is no negative cycle\n";
    }

    // Cost Matrix
    cout << "\nCost Matrix:\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(adj[i][j] == INT_MAX)
                cout << "INF\t";
            else
                cout << adj[i][j] << "\t";
        }

        cout << endl;
    }

    // Path Matrix
    cout << "\nPath Matrix:\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(adj[i][j] == INT_MAX)
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
