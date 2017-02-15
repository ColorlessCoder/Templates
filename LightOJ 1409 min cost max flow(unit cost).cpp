#include<bits/stdc++.h>
#define vi vector<int>
#define pii pair<int,int>
#define fr first
#define sc second
#define MAX 50010
#define LL long long int
#define inf 10000
#define INF 10000000
//#define mod 1000000007
#define mMax 30010
#define nMax 2010
#define SZ(a) a.size()
#define pb push_back
#define mp make_pair
#define N 200
using namespace std;
int mf,f,s,t,n,cost;
int res[N][N],C[N][N];//,RES[N][N];
vector<vi > E;
vi p;
    pii A[N];
void augm(int v,int me)
{
    if(v==s) {f=me;return;}
   // cout<<v<<" ";
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
    cost=0;
    while(1)
    {
        f=0;
        vi D(n,inf);
        priority_queue<pair<int,int> > Q;
        Q.push(pii(0,s));
        p.assign(n,-1);
        while(!Q.empty())
        {
        pii u=Q.top();
        Q.pop();
        if((0-u.fr) > D[u.sc]) continue;
        if(u.sc==t) break;
        int z=E[u.sc].size();
        for(int i=0;i<z;i++)
        {
         int v=E[u.sc] [i];
        // cout<<D[v];
            //if((D[v]>(0-u.fr  +C[u.sc][v])    )&&( res[u.sc][v]>0))
           if((D[v]>(0-u.fr  +C[u.sc][v])    ))

           if(( res[u.sc][v]>0))
                D[v]=0-u.fr  + C[u.sc][v],Q.push(pii(u.fr-C[u.sc][v],v)),p[v]=u.sc;
        }

        }
        augm(t,inf);
        if(f==0) break;
        mf+=f;
        cost+=(f*D[t]);
    }
    return mf;
}
void add(int u,int v,int flow,int rflow,int cc,int rcc)
{
    E[u].pb(v);
    E[v].pb(u);
    res[u][v]=flow;
    res[v][u]=rflow;
    C[u][v]=cc;
    C[v][u]=rcc;
    return;
}
int main()
{
    int T,I=1;
    cin>>T;
    while(T--)
    {
        printf("Case %d: ",I++);
        int c,r;
        int a,b;
        for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            C[i][j]=inf;
        scanf("%d %d %d",&n,&c,&r);
        s=0;
        t=2*n + c +10;
        E.assign(t+2,vi());
        int mid=2*n +1;
        int sum=0;
        for(int i=1;i<=n;i++)
            {
                scanf("%d",&a);
                sum+=a;
                add(s,i,a,0,0,0);
                add(n+i,t,a,0,0,0);
                add(mid,n+i,inf,0,0,0);
                if(i<n) add(i,i+1,inf,0,0,0);
            }
        for(int i=1;i<=c;i++)
        {
            scanf("%d %d",&a,&b);
            add(s,mid+i,a,0,b,-b);
            add(mid+i,mid,inf,0,0,0);
        }
        for(int i=1;i<=r;i++)
        {
            scanf("%d %d",&a,&b);
            a++;
            for(int j=1;j+a <=n;j++)
            {
                if(C[j][n+j+a]==inf) add(j,n+j+a,inf,0,b,-b);
                C[j][j+n+a]=min(C[j][j+n+a],b);
                C[j+n+a][j]=max(C[j+a+n][j],-b);
            }
        }
        n=t+1;
        if(maxflow()!=sum) printf("impossible\n");
        else printf("%d\n",cost);
    }

    return 0;
}
