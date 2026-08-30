#include<bits/stdc++.h>
using namespace std;
const int INF =1e8;
vector<int>dis;
void dijkstra(int src,int n,vector<vector<pair<int,int>>>&adj,vector<int>&dis,vector<vector<int>>&path)
{
    dis.assign(n,INF);
    dis[src]=0;
    path.assign(n, {});
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,src});
    path[src]= {src};
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
                path[child_node]=path[par_node];
                path[child_node].push_back(child_node);

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
        for(auto e:oadj[i])
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
    bool possible=bellman(newsource,V,adj,h);
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
    vector<vector<vector<int>>>all_path(n);
    vector<vector<int>>ans(n,vector<int>(n,INF));
    for(int u=0; u<n; u++)
    {

        vector<vector<int>>path;
        dijkstra(u,n,newadj,dis,path);
        all_path[u]=path;
        for(int v=0; v<n; v++)
        {
            if(dis[v]!=INF)
                ans[u][v]=dis[v]-h[u]+h[v];
        }

    }
    for(int u=0; u<n; u++)
    {
        for(int v=0; v<n; v++)
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
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(ans[i][j]==INF)
            {
                cout<<"INF ";
            }
            else
            {
                cout<<"[";
                for(int x:all_path[i][j])
                {
                    cout<<x<<" ";
                }
                cout<<"]";
            }
        }
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
