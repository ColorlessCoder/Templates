struct edges
{
    int v;
    LL cap, rev;
    edges(int v=0,LL cap=0,LL rev=0)
    {
        this->v = v;
        this->cap = cap;
        this->rev = rev;
    }
};
edges edge[mMax];
vector<vi >adj;
vi pt;
int ind,source,sink;
int bigN;
LL dis[nMax];
void add(int u, int v, LL w, LL w2)
{
    edge[ind] = edges(v, w, ind+1);
    adj[u].pb(ind);
    edge[ind+1] = edges(u, w2, ind);
    adj[v].pb(ind+1);
    ind+=2;
}
int dinicBfs(LL cost)
{
    queue<int>Q;
    //memset(dis, -1, sizeof(dis));
    rep1(i,bigN) dis[i]=-1;
    Q.push(source);
    dis[source] = 0;
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        int z=adj[u].size();
        for(int i=0; i<z; i++)
        {
            int id = adj[u][i];
            int v = edge[id].v;
            if((edge[id].cap)>=cost && dis[v] == -1)
            {

                dis[v] = dis[u] + 1;
                if(v == sink) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}
bool dinicDfs(int cur, LL cost)
{
    if(cur == sink) return true;
    LL low, ans = 0;
    int z=adj[cur].size();
    for(; pt[cur]<z; pt[cur]++)
    {
        int id = adj[cur][pt[cur]];
        int v = edge[id].v;
        if((edge[id].cap)>=cost && (dis[v] == dis[cur] + 1) &&
                 dinicDfs(v,cost))
        {
            edge[id].cap -= cost;
            edge[edge[id].rev].cap += cost;
            return true;
        }
    }
    return false;
}
LL dinicFlow()
{
    LL MaxFlow = 0;
    LL lim=1ll<<30;
    int I=0;
    while(lim){
      if(!dinicBfs(lim)) {
        //cout<<I<<" "<<lim<<endl;
        lim>>=1;
        continue;
      }
      //I++;
      pt.assign(bigN,0);
      while(dinicDfs(source,lim))
        MaxFlow+=lim;
    }
    return MaxFlow;
}
