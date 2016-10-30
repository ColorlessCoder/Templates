int mf,f,s,t,n;
int res[N][N],Res[N][N];
vector<vi > E;
vi p;
void ini()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        res[i][j]=Res[i][j];
}
void augm(int v,int me)
{
    if(v==s) {f=me;return;}
    if(p[v]!=-1)
    {
        augm(p[v],min(me,res[p[v]][v]));
        res[p[v]][v]-=f;
        res[v][p[v]]+=f;
    }
    return ;
}
int maxflow()
{
    mf=0;
    while(1)
    {
        f=0;
        vector<bool> vis(n,0);
        queue<int> Q;
        vis[s]=0;
        Q.push(s);
        p.assign(n,-1);
        while(!Q.empty())
        {
        int u=Q.front();
        Q.pop();
        if(u==t) break;
        int z=E[u].size();
        for(int i=0;i<z;i++)
        {
         int v=E[u] [i];
            if((vis[v]==0    )&&( res[u][v]>0))
            vis[v]=1,Q.push(v),p[v]=u;
        }
 
        }
        augm(t,inf);
        if(f==0) break;
        mf+=f;
    }
    return mf;
}
