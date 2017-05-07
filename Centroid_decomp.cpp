vector<vi > E;
int A[MAXN],subtree[MAXN],depth[MAXN];
int par[20][MAXN];
int auxilarypar[MAXN];
int iscentroid[MAXN];
int nn;
////////////// Decompose //////////////
void dfs1(int u,int prev)
{
    subtree[u]=1;
    nn++;
    int z=E[u].size();
    for(int i=0;i<z;i++)
        if(E[u][i]!=prev && (iscentroid[E[u][i]]==0))
    {
        dfs1(E[u][i],u);
        subtree[u]+=subtree[E[u][i]];
    }
    return;
}
 
int dfs2(int u,int prev)
{
    int z=E[u].size();
    for(int i =0;i<z;i++)
        if((E[u][i]!=prev  )&& (iscentroid[E[u][i]]==0) && subtree[E[u][i]] > nn/2 )
            return dfs2(E[u][i],u);
    return u;
}
void decompose(int root,int prev)
{
    nn=0;
    dfs1(root,root);
    int centroid=dfs2(root,root);
    if(prev==-1) prev=centroid;
    auxilarypar[centroid]=prev;
    iscentroid[centroid]=1;
    int z=E[centroid].size();
    for(int i=0;i<z;i++)
        if(iscentroid[E[centroid][i]]==0)
            decompose(E[centroid][i],centroid);
    return ;
}
///////////////////////// Preprocessing
void dfs0(int u,int prev,int d)
{
    depth[u]=d;
    par[0][u]=prev;
    int z=E[u].size();
    for(int i=0;i<z;i++)
        if(E[u][i]!=prev)
        dfs0(E[u][i],u,d+1);
    return;
}
void preL(int n)
{
        for(int i=1; i<17; i++)
            for(int j=1; j<=n; j++)
                if(par[i-1][j] != -1)
                    par[i][j] = par[i-1][par[i-1][j]];
}
int lca(int u, int v)
{
    if(depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    for(int i=0; i<17; i++)
        if( (diff>>i)&1 )
         u = par[i][u];
    if(u == v) return u;
    for(int i=17-1; i>=0; i--)
      if(par[i][u] != par[i][v])
        {
            u = par[i][u];
            v = par[i][v];
        }
    return par[0][u];
}
int dist(int a,int b)
{
    return depth[a]+depth[b]- (2*depth[lca(a,b)]);
}
 
//// UPDATE AND QUERY
set< pii > ans[MAXN];
int color[MAXN];
void update(int u)
{
    if(color[u]==0) ans[u].insert(make_pair(0,u));
    else ans[u].erase(make_pair(0,u));
    int p=u;
    while(p!=auxilarypar[p])
    {
        p=auxilarypar[p];
    if(color[u]==0) ans[p].insert(make_pair(dist(p,u),u));
    else ans[p].erase(make_pair(dist(p,u),u));
    }
    color[u]=1^color[u];
    return;
}
int query(int u)
{
    int mm=(ans[u].begin())->fr;
    int p=u;
       while(p!=auxilarypar[p])
    {
        p=auxilarypar[p];
        mm=min(mm,(ans[p].begin())->fr+dist(p,u));
    }
    return mm;
}
int main()
{
  //...
  dfs0(1,-1,0);
	preL(n);
	decompose(1,-1);
  //....
  return 0;
}
