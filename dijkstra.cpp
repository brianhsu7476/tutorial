#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Vertex{
    int d, v;
    Vertex(){}
    Vertex(int V, int D){d=D, v=V;}
    bool operator<(const Vertex r)const{return d<r.d||d==r.d&&v<r.v;}
};

struct Edge{
    int v, w;
    Edge(){}
    Edge(int V, int W){v=V, w=W;}
};

set<Vertex> S;
int n, m;
#define kN 1000006
vector<Edge> G[kN];
bool used[kN]={0};
int d[kN];

signed main(){
    cin>>n>>m;
    for(int i=0; i<m; ++i){
        int u, v, w; cin>>u>>v>>w;
        G[u].push_back(Edge(v, w)), G[v].push_back(Edge(u, w));
    }
    used[0]=1;
    for(int i=0; i<G[0].size(); ++i)S.insert(Vertex(G[0][i].v, G[0][i].w));
    while(S.size()){
        Vertex x=*S.begin();
        S.erase(S.begin());
        if(used[x.v])continue;
        d[x.v]=x.d, used[x.v]=1;
        for(int i=0; i<G[x.v].size(); ++i)if(!used[G[x.v][i].v])S.insert(Vertex(G[x.v][i].v, x.d+G[x.v][i].w));
    }
    for(int i=0; i<n; ++i)cout<<d[i]<<' ';
    cout<<endl;
}
