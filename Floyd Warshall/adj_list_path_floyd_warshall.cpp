#include<bits/stdc++.h>
using namespace std;
vector<vector<pair<int,int>>>adj_list;
vector<vector<vector<int>>>path;
int getcost(int u,int v)
{
    if(u==v)return 0;
    for(auto &p:adj_list[u])
    {
        if(p.first==v)
            return p.second;

    }
    return INT_MAX;
}
void setcost(int u,int v,int w)
{
    for(auto &p:adj_list[u])
    {
        if(p.first==v)
        {
            p.second=w;
            return;
        }
    }
    adj_list[u].push_back({v,w});
}
int main()
{
    int n,e;
    cin>>n>>e;
    adj_list.assign(n, {});
    path.assign(n,vector<vector<int>>(n));
    for(int i=0; i<n; i++)
    {
        path[i][i]= {i};
    }
    while(e--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adj_list[u].push_back({v,w});
        setcost(u,v,w);
        path[u][v]= {u,v};

    }
    for(int k=0; k<n; k++)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                int ik=getcost(i,k);
                int kj=getcost(k,j);
                if(ik!=INT_MAX&&kj!=INT_MAX)
                {
                    int newcost=ik+kj;
                    if(newcost<getcost(i,j))
                    {
                        setcost(i,j,newcost);
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
    bool negcycle=false;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {


            if(getcost(i,i)<0)
            {
                negcycle=true;
            }
        }
    }
    if(negcycle)
    {
        cout<<"There is a neg cycle"<<endl;
    }
    else
    {
        cout<<"No neg cycle"<<endl;
    }

    cout<<"Cost Matrix"<<endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(getcost(i,j)==INT_MAX)
            {
                cout<<"INF"<<endl;
                continue;
            }
            else
            {
                cout<<getcost(i,j)<<" ";
            }
        }
        cout<<endl;
    }
    cout<<"Path Matrix:"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<i<<" : ";
        for(int j=0; j<n; j++)
        {
            if(getcost(i,j)==INT_MAX)
            {
                cout<<"INF ";
            }
            else {
                cout<<"[";
                for(int x:path[i][j])
                {
                    cout<<x<<" ";
                }
                cout<<"] ";
            }
        }
        cout<<endl;
    }

}
