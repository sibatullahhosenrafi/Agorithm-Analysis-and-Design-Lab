#include <bits/stdc++.h>
using namespace std;
const int INF = 1e8;
vector<int> dis;

void dijkstra(int src, vector<vector<pair<int,int>>> &adj, vector<int> &dis, int n, vector<vector<int>> &path)
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});
    dis.assign(n, INF);
    dis[src] = 0;
    path.assign(n, {});
    while (!pq.empty())
    {
        pair<int,int> par = pq.top();
        pq.pop();
        int par_node = par.second;
        int par_dis = par.first;
        if (par_dis > dis[par_node]) continue; // stale entry, skip
        for (auto child : adj[par_node])
        {
            int child_node = child.first;
            int child_dis = child.second;
            if (child_dis + par_dis < dis[child_node])
            {
                dis[child_node] = child_dis + par_dis;
                pq.push({dis[child_node], child_node});
                path[child_node] = path[par_node];
                path[child_node].push_back(child_node);
            }
        }
    }
}

// FIX #1: h passed by reference so the computed potentials survive the call
bool bellman(int src, vector<vector<pair<int,int>>> &adj, int n, vector<int> &h)
{
    h.assign(n, INF);
    h[src] = 0;
    for (int iter = 0; iter < n - 1; iter++)
    {
        bool changed = false; // FIX #5: start false so early-exit actually works
        for (int u = 0; u < n; u++)
        {
            if (h[u] == INF)
                continue;
            for (auto e : adj[u])
            {
                int v = e.first;
                int w = e.second;
                if (h[u] != INF && h[v] > h[u] + w)
                {
                    h[v] = h[u] + w;
                    changed = true;
                }
            }
        }
        if (!changed)
            break;
    }
    // extra pass: if anything can still relax, there's a negative cycle
    for (int u = 0; u < n; u++)
    {
        if (h[u] == INF)
            continue;
        for (auto e : adj[u])
        {
            int v = e.first;
            int w = e.second;
            if (h[u] != INF && h[v] > h[u] + w)
                return false;
        }
    }
    return true;
}

void johnson(vector<vector<pair<int,int>>> &oadj, int n)
{
    int newsrc = n;
    int V = n + 1;
    vector<vector<pair<int,int>>> adj(V);
    for (int u = 0; u < n; u++)
        for (auto &e : oadj[u])
            adj[u].push_back(e);

    for (int i = 0; i < n; i++)
        adj[newsrc].push_back({i, 0});

    vector<int> h;
    bool possible = bellman(newsrc, adj, V, h);
    if (!possible)
    {
        cout << "negative cycle";
        return;
    }

    vector<vector<pair<int,int>>> newadj(n);
    for (int u = 0; u < n; u++)
    {
        for (auto e : oadj[u])
        {
            int v = e.first;
            int w = e.second;
            if (h[u] != INF && h[v] != INF)
            {
                int newwt = w + h[u] - h[v];
                newadj[u].push_back({v, newwt});
            }
        }
    }

    vector<vector<int>> ans(n, vector<int>(n, INF));
    for (int src = 0; src < n; src++)
    {
        vector<vector<int>> path;
        dijkstra(src, newadj, dis, n, path);
        // FIX #2: fill ans[src][v] for EVERY vertex reachable from src,
        // not just src's direct neighbors
        for (int v = 0; v < n; v++)
        {
            if (dis[v] == INF)
                continue;
            ans[src][v] = dis[v] - h[src] + h[v];
        }
    }

    // FIX #6: format matches "u, v, d" one triple per line, as required
    ofstream fout("output1.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue; // skip self-pairs, distance 0 and not meaningful here
            if (ans[i][j] == INF) // FIX #3: == not =
            {
                fout << i << ", " << j << ", INF\n";
                continue;
            }
            fout << i << ", " << j << ", " << ans[i][j] << "\n";
        }
    }
    fout.close();
    cout << "DONE, results written to output1.txt" << endl;
}

int main()
{
    int V = 33;
    int E = 333;
    srand(time(0));

    // FIX #4: build a genuinely random UNDIRECTED graph.
    // Pick E distinct unordered vertex pairs at random and add both directions.
    vector<vector<pair<int,int>>> oadj(V);
    set<pair<int,int>> used;
    int e = 0;
    while (e < E)
    {
        int i = rand() % V;
        int j = rand() % V;
        if (i == j) continue;
        int a = min(i, j), b = max(i, j);
        if (used.count({a, b})) continue;
        used.insert({a, b});
        int w = rand() % 10 + 1; // nonnegative weight, 1..10
        oadj[a].push_back({b, w});
        oadj[b].push_back({a, w}); // undirected: add both directions
        e++;
    }

    johnson(oadj, V);
    return 0;
}
