#include<bits/stdc++.h>
using namespace std;
const int INF=1e8;
int dijkstra(vector<vector<int>>&adj,int u,int v,int n)
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    vector<int>dis;
    dis.assign(n,INF);
    pq.push({0,u});
    dis[u]=0;
    vector<vector<int>>path(n,vector<int>(n));
    while(!pq.empty())
    {
        pair<int,int>par=pq.top();
        pq.pop();
        int par_node=par.second;
        int par_dis=par.first;
        for(int child_node=0; child_node<n; child_node++)
        {
            int child_dis=adj[par_node][child_node];
            if(child_dis+par_dis<dis[child_node])
            {
                dis[child_node]=child_dis+par_dis;
                pq.push({dis[child_node],child_node});
                path[child_node]=path[par_node];
                path[child_node].push_back(child_node);
            }

        }
    }
   return dis[v];


}
int main()
{    srand(time(0));

    int n;
    cin>>n;
    vector<vector<int>>adj(n,vector<int>(n));
    vector<vector<int>>radj(n,vector<int>(n));

    vector<vector<vector<int>>>path(n,vector<vector<int>>(n));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==j)
            {
                adj[i][i]=0;
                radj[i][i]=0;
                path[i][i]= {i};
            }
            else
            {
                adj[i][j]=INF;
                radj[i][j]=INF;
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                int w = rand() % 10 + 1;
                adj[i][j]=w;
                radj[i][j]=w;
                cout<<w<<" ";
                path[i][j]= {i};
            }
        }
        cout<<endl;
    }
    for(int k=0; k<n; k++)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {

                if(adj[i][k]!=INF&&adj[k][j]!=INF)
                {
                    int newcost=adj[i][k]+adj[k][j];
                    if(newcost<adj[i][j])
                    {
                        adj[i][j]=newcost;
                        path[i][j]=path[i][k];
                        for(int x:path[k][j])
                        {
                            if(x!=k)
                                path[i][j].push_back(x);
                        }
                    }
                }
            }
        }
    }
    ofstream fout("output.txt");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(adj[i][j]==INF)
            {
                fout<<"INF ";
                continue;
            }
            else
            {
                fout<<adj[i][j]<<" ";
            }
        }
        fout<<endl;
    }
    cout<<"Enter u,v"<<endl;
    int u,v;
    cin>>u>>v;
    int x= dijkstra(radj,u,v,n);
    int y = dijkstra(radj,v,u,n);
    if(x==adj[u][v])
    {
        cout<<"Matched 10->20\n";
    }
    else {
                cout<<"UnMatched 10->20\n";

    }
    if(y==adj[v][u])
    {
        cout<<"Matched 20->10\n";
    }
    else {
        cout<<"Unmatched 20->10\n";
    }




}
