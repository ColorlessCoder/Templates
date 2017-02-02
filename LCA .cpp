int par[17][N];
/*
first generate depth and par
*/
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
void preL(int n)
{
        for(int i=1; i<17; i++)
            for(int j=0; j<n; j++)
                if(par[i-1][j] != -1)
                    par[i][j] = par[i-1][par[i-1][j]];
}
int pth(int u, int p)
{
    for(int i=16;i>=0;i--)
        if(p&(1<<i))
    {
        u=par[i][u];
    }
    return u;
}
