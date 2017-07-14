vector< vi > E;
vector< vi > C;
vector< vi > G;
vector< vi > D;
bool artp[MAXN];
int artn[MAXN];
vi realArt;
int dfsnum[MAXN],dfslo[MAXN],par[MAXN];
int dfsn,dfsroot,child,n;
int ans,nc,tot;
stack<int> Q;
void dfs(int u)
{
    tot++;
    dfsnum[u]=dfslo[u]=dfsn++;
    Q.push(u);
    int z=E[u].size();
    for(int i=0;i<z;i++)
    {
        int v=E[u][i];
        if(dfsnum[v]==0)
        {
            par[v]=u;
            if(u==dfsroot)
                    child++;
            dfs(v);
            if(dfslo[v]>=dfsnum[u]){
             if(artp[u]==false) {realArt.pb(u);artn[u]=ans;ans++;}
             artp[u]=true;
             C.pb(vi());
             C[C.size()-1].pb(u);
             while(1)
             {
              int temp=Q.top();
              C[C.size()-1].pb(temp);
              Q.pop();
              if(temp==v) break;
             }
            }
            dfslo[u]=min(dfslo[u],dfslo[v]);
        }
        else if(v != par[u])
            dfslo[u]=min(dfslo[u],dfsnum[v]);
    }
    return ;
}
int main()
{
//...
    memset(dfsnum,0,sizeof(dfsnum));
    memset(artp,false,sizeof(artp));
    for(int i=1;i<=n;i++)
        if(dfsnum[i]==0)
    {
        tot=0;
        dfsn=1;
        ans=0;
        while(!Q.empty()) Q.pop();
        C.clear();
        realArt.clear();
        dfsroot=i;
        child=0;
        dfs(i);
        artp[i]= (child > 1);
     }
//...
}
