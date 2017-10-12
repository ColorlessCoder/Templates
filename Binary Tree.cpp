// Trick for reducing the number of decision for a vertex
// Pool-style implementation
// Caution: n has been declared locally in functions

// Problem: http://codeforces.com/problemset/problem/109/C

struct nodes{
    int ind,par,cost;
    bool dummy;
    nodes(){}
    nodes(int a,int b,bool dum=false)
    {
        ind=a;par=b;dummy=dum;
    }
    nodes(int a,int b,int c,bool dum=false)
    {
        ind=a;par=b;dummy=dum;cost=c;
    }
} node[200100];

vector<vi> adj;
vector<vi> adj2;
vector<vi> cost;

int root;
int sz;

void init(int a,int _n){
    sz=_n+1; root=a;
    adj.assign(sz+1,vi());
    cost.assign(sz+1,vi());
    adj2.assign(2*sz+10,vi());
}

void build(int u,int par)
{
    int len=SZ(adj[u]);
    int cur=u;
    int f=0;
    for(int i=0;i<len;i++)
        if(adj[u][i]!=par)
    {
        int v=adj[u][i];
        if(f==0){ f=1;adj2[cur].pb(v);node[v]=nodes(v,cur,cost[u][i]); build(v,u); continue; }

        if(len-i >=2)
        {
            adj2[cur].pb(sz);
            node[sz]=nodes(sz,cur,0,true);
            cur=sz++;
        }
        adj2[cur].pb(v);
        node[v]=nodes(v,cur,cost[u][i]);
        build(v,u);
    }
    return ;
}
