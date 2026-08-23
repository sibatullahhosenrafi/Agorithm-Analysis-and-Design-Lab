#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;


// ---------------- Dijkstra ----------------

void dijkstra(int src,
              int V,
              vector<vector<pair<int,int>>> &adj,
              vector<int> &dis)
{
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dis.assign(V, INF);

    dis[src] = 0;

    pq.push({0, src});

    while (!pq.empty())
    {
        pair<int,int> par = pq.top();
        pq.pop();

        int par_dis = par.first;
        int par_node = par.second;

        // পুরনো distance হলে ignore করব
        if (par_dis != dis[par_node])
            continue;

        for (auto child : adj[par_node])
        {
            int child_node = child.first;
            int child_dis = child.second;

            if (par_dis + child_dis < dis[child_node])
            {
                dis[child_node] =
                    par_dis + child_dis;

                pq.push({
                    dis[child_node],
                    child_node
                });
            }
        }
    }
}


// ---------------- Bellman-Ford ----------------

bool bellmanFord(
    int V,
    vector<vector<pair<int,int>>> &adj,
    int src,
    vector<int> &h)
{
    h.assign(V, INF);

    h[src] = 0;

    // V-1 times relaxation
    for (int i = 0; i < V - 1; i++)
    {
        bool changed = false;

        for (int u = 0; u < V; u++)
        {
            if (h[u] == INF)
                continue;

            for (auto edge : adj[u])
            {
                int v = edge.first;
                int w = edge.second;

                if (h[u] + w < h[v])
                {
                    h[v] = h[u] + w;
                    changed = true;
                }
            }
        }

        if (!changed)
            break;
    }


    // Negative cycle check
    for (int u = 0; u < V; u++)
    {
        if (h[u] == INF)
            continue;

        for (auto edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (h[u] + w < h[v])
            {
                return false;
            }
        }
    }

    return true;
}


// ---------------- Johnson Algorithm ----------------

void johnson(
    int n,
    vector<vector<pair<int,int>>> &originalAdj)
{
    /*
        Original vertices:
        0, 1, 2, ..., n-1

        New vertex:
        n
    */

    int newSource = n;
    int V = n + 1;


    // -----------------------------------
    // Step 1:
    // New graph তৈরি করছি
    // -----------------------------------

    vector<vector<pair<int,int>>> adj(V);

    for (int u = 0; u < n; u++)
    {
        for (auto edge : originalAdj[u])
        {
            int v = edge.first;
            int w = edge.second;

            adj[u].push_back({v, w});
        }
    }


    // -----------------------------------
    // Step 2:
    // New source থেকে সব node-এ
    // 0 weight edge
    // -----------------------------------

    for (int i = 0; i < n; i++)
    {
        adj[newSource].push_back({i, 0});
    }


    // -----------------------------------
    // Step 3:
    // Bellman-Ford
    // -----------------------------------

    vector<int> h;

    bool possible =
        bellmanFord(V, adj, newSource, h);


    if (!possible)
    {
        cout << "Negative cycle detected\n";
        return;
    }


    // -----------------------------------
    // Step 4:
    // Reweight edges
    //
    // newWeight = w + h[u] - h[v]
    // -----------------------------------

    vector<vector<pair<int,int>>> newAdj(n);

    for (int u = 0; u < n; u++)
    {
        for (auto edge : originalAdj[u])
        {
            int v = edge.first;
            int w = edge.second;

            int newWeight =
                w + h[u] - h[v];

            newAdj[u].push_back({
                v,
                newWeight
            });
        }
    }


    // -----------------------------------
    // Step 5:
    // Every vertex থেকে Dijkstra
    // -----------------------------------

    vector<vector<int>> answer(
        n,
        vector<int>(n, INF)
    );

    for (int src = 0; src < n; src++)
    {
        vector<int> dis;

        dijkstra(
            src,
            n,
            newAdj,
            dis
        );


        // -----------------------------------
        // Step 6:
        // Original distance বের করা
        //
        // d(u,v) =
        // d'(u,v) - h[u] + h[v]
        // -----------------------------------

        for (int v = 0; v < n; v++)
        {
            if (dis[v] != INF)
            {
                answer[src][v] =
                    dis[v] - h[src] + h[v];
            }
        }
    }


    // -----------------------------------
    // Print Answer
    // -----------------------------------

    cout << "\nAll Pairs Shortest Distance:\n\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (answer[i][j] == INF)
                cout << "INF ";
            else
                cout << answer[i][j] << " ";
        }

        cout << "\n";
    }
}


// ---------------- Main ----------------

int main()
{
    int n, m;

    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;

        cin >> u >> v >> w;

        adj[u].push_back({v, w});
    }


    // Original graph print
    cout << "Original Graph:\n";

    for (int i = 0; i < n; i++)
    {
        cout << i << " -> ";

        for (auto edge : adj[i])
        {
            cout << "("
                 << edge.first
                 << ","
                 << edge.second
                 << ") ";
        }

        cout << "\n";
    }


    johnson(n, adj);

    return 0;
}
