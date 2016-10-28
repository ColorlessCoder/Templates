int mf,f,s,t,n;
int res[N][N];
vi p;
string A[]={"","XXL","XL","L","M","S","XS"};
inline int ai(string str)
{
    for(int i=1;i<7;i++)
        if(str==A[i])
        return i;
    return 0;
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
        for(int v=0;v<n;v++)
            if((vis[v]==0    )&&( res[u][v]>0))
            vis[v]=1,Q.push(v),p[v]=u;
        }
        augm(t,inf);
        if(f==0) break;
        mf+=f;
    }
    return mf;
}
