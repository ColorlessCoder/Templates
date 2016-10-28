using namespace std;
int mf,f,s,t,n,cost;
int res[N][N],C[N][N];
vector<vi > E;
vi p;
void augm(int v,int me,int lim)
{
    if(v==s) {f=min(me,lim);return;}
  //  cout<<v<<" ";
    if(p[v]!=-1)
    {
        augm(p[v],min(me,res[p[v]][v]),lim);
      //  cost+=(f*C[p[v]][v]);
        res[p[v]][v]-=f;
        res[v][p[v]]+=f;
    }
    return ;
}
int maxflow(int limit)
{
    mf=0;
    cost=0;
    while(1)
    {
        f=0;
        vi D(n,-inf);
        priority_queue<pair<int,int> > Q;
        Q.push(pii(0,s));
        p.assign(n,-1);
        while(!Q.empty())
        {
        pii u=Q.top();
        Q.pop();
        if((u.fr) < D[u.sc]) continue;
      //  if(u.sc==t) break;
        int z=E[u.sc].size();
        for(int i=0;i<z;i++)
        {
         int v=E[u.sc] [i];
            if((D[v]<(u.fr  +C[u.sc][v])    )&&( res[u.sc][v]>0))
            D[v]=u.fr  + C[u.sc][v],Q.push(pii(u.fr+C[u.sc][v],v)),p[v]=u.sc;
        }
 
        }
        int lim=limit-mf;
        augm(t,inf,lim);
        if(f==0) break;
        cost+=D[t];
        mf+=f;
    //    cout<<"--"<<D[t]<<endl;
        if(mf==limit) break;
    }
    return mf;
}
