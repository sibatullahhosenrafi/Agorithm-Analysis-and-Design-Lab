#include<bits/stdc++.h>
using namespace std;
const int INF =1e8;
void dijkstra(int src,int n,vector<vector<pair<int,int>>>&adj,vector<int>&dis)
{
    dis.assign(n,INF);
    dis[src]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,src});
    while(!pq.empty())
    {
        pair<int,int>par=pq.top();
        pq.pop();
        int par_node=par.second;
        int par_dis=par.first;
        for(auto &child:adj[par_node])
        {
            int child_node=child.first;
            int child_dis=child.second;
            if(par_dis+child_dis<dis[child_node])
            {
                dis[child_node]=par_dis+child_dis;
                pq.push({dis[child_node],child_node});

            }
        }
    }
}
bool bellman(int newsrc,int n,vector<vector<pair<int,int>>>&adj,vector<int>&h)
{
    h.assign(n,INF);
    h[newsrc]=0;
    for(int iter=0; iter<n-1; iter++)
    {
        bool changed=false;
        for(int u=0; u<n; u++)
        {
            if(h[u]==INF)
                continue;
            for(auto &e:adj[u])
            {
                int v=e.first;
                int w=e.second;
                if(h[u]!=INF&&h[u]+w<h[v])
                {
                    h[v]=h[u]+w;
                    changed=true;
                }
            }
        }
        if(!changed)
            break;
    }
    for(int u=0; u<n; u++)
    {
        if(h[u]==INF)
            continue;
        for(auto e:adj[u])
        {
            int v=e.first;
            int w=e.second;
            if(h[v]>h[u]+w)
            {
                return false;
            }
        }
    }
    return true;
}
void johnson(vector<vector<pair<int,int>>>&oadj,int n)
{
    int newsource=n;
    int V=n+1;
    vector<vector<pair<int,int>>>adj(V);
    for(int i=0; i<n; i++)
    {
        int u=i;
        for(auto &e:adj[i])
        {
            int v=e.first;
            int w=e.second;
            adj[u].push_back({v,w});

        }
    }
    for(int i=0; i<n; i++)
    {
        adj[newsource].push_back({i,0});
    }
    vector<int>h;
    bool possible=bellman(newsource,n,adj,h);
    if(!possible)
    {
        cout<<"Negative cycle"<<endl;
        return;
    }
    vector<vector<pair<int,int>>>newadj(n);
    for(int i=0; i<n; i++)
    {
        for(auto x:oadj[i])
        {
            int u=i;
            int w=x.second;
            int v=x.first;
            int newweight=w+ h[u]-h[v];
            newadj[u].push_back({v,newweight});
        }
    }
    vector<vector<int>>ans(n,vector<int>(n,INF));
    for(int u=0; u<n; u++)
    {
        vector<int>dis;
        dijkstra(u,n,newadj,dis);
        for(int v=0;v<n;v++)
        {
            if(dis[v]!=INF)
                ans[u][v]=dis[v]-h[u]+h[v];
        }

    }
    for(int u=0;u<n;u++)
    {
        for(int v=0;v<n;v++)
        {
            if(ans[u][v]==INF)
            {
                cout<<"INF ";
                continue;
            }
            cout<<ans[u][v]<< " ";

        }
        cout<<endl;
    }

}
int main()
{
    int n,e;
    cin>>n>>e;
    vector<vector<pair<int,int>>>oadj(n);
    while(e--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        oadj[u].push_back({v,w});
    }
    johnson(oadj,n);
}
/*5 7
0 1 4
0 2 2
1 2 -1
1 3 2
2 3 3
3 4 2
4 1 1
0 4 2 5 7
INF 0 -1 2 4
INF 6 0 3 5
INF 3 2 0 2
INF 1 0 3 0*/
