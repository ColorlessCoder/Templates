#include<bits/stdc++.h>
#define vi vector<int>
#define rep(a,b,n) for(int a=b;a<n;a++)
#define pii pair<int,int>
#define fr first
#define sc second
#define LL long long int
#define inf 100000000
#define INF 100000000
#define N 502
#define mMax 8000
#define nMax 2800
#define SZ(a) a.size()
#define pb push_back

using namespace std;
struct edges
{
    int v, cap, rev;
    edges(int v=0,int cap=0,int rev=0)
    {
        this->v = v;
        this->cap = cap;
        this->rev = rev;
    }
};
edges edge[mMax];
vector<vi >adj;
int ind,source,sink,dis[nMax];
void add(int u, int v, int w, int w2)
{
    edge[ind] = edges(v, w, ind+1);
    adj[u].pb(ind);
    edge[ind+1] = edges(u, w2, ind);
    adj[v].pb(ind+1);
    ind+=2;
}
int dinicBfs()
{
    queue<int>Q;
    memset(dis, -1, sizeof(dis));
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
            if(edge[id].cap && dis[v] == -1)
            {
                dis[v] = dis[u] + 1;
                if(v == sink) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}
int dinicDfs(int cur, int cost = INF)
{
    if(cur == sink) return cost;
    int low, ans = 0;
    int z=adj[cur].size();
    for(int i = 0; i<z; i++)
    {
        int id = adj[cur][i];
        int v = edge[id].v;
        if(edge[id].cap && (dis[v] == dis[cur] + 1) &&
                (low = dinicDfs(v, min(edge[id].cap ,cost))))
        {
            edge[id].cap -= low;
            edge[edge[id].rev].cap += low;
            ans += low;
            cost -= low;
            if(!cost) break;
        }
    }
    return ans;
}
int dinicFlow()
{
    int MaxFlow = 0;
    while(dinicBfs())
        MaxFlow += dinicDfs(source);
    return MaxFlow;
}
int mask[200][200];
int sm[200][200];
int main()
{
    int nn;
    int m,t;
    int T,I=1;
    T=1;
    cin>>T;
    while(T--)
    {
        scanf("%d",&nn);
        //  if(nn==0) break;
        printf("Case %d:\n",I++);
        scanf("%d",&m);
        //   memset(res,0,sizeof(res));
        int a=1,tot=0,n;
        n=nn*m + 2*nn + 2*m +1 ;
        adj.assign(n,vi());
        rep(i,0,nn) rep(j,0,m) mask[i][j]=a++;
        a--;
//        rep(i,1,a+1) add(0,i,inf);
        source=0;
        n=tot;
        tot=nn+m-1;
        t=1;
        ind=0;
        rep(i,0,nn) sm[i][m-1]=t++;
        for(int i=m-2; i>=0; i--) sm[nn-1][i]=t++;
        for(int i=nn-2; i>=0; i--)
            rep(j,0,m-1)
            sm[i][j]=sm[i+1][j+1];
        rep(i,0,nn)
        {
            rep(j,0,m)
            {
                t=i+j+1;
                add(t,mask[i][j]+tot,99,0);
                add(mask[i][j]+tot,sm[i][j]+tot+a,99,0);
            }
        }
//        rep(i,0,nn){
//        rep(j,0,m)
//        printf("%d ",sm[i][j]);
//        cout<<endl;
//    }
        rep(i,1,tot+1)
        {
            int tt=min(nn-1,i-1) -max(0,i-m) +1;
            scanf("%d",&t);
            add(0,i,t-tt,0);
        }
        //memset(A,0,sizeof(A));
       // rep(i,0,nn) rep(j,0,m) A[sm[i][j]]++;
        n=a+ 2*tot;
        n++;
        rep(i,1,tot+1)
        {
            int tt=min(nn-1,i-1) -max(0,i-m) +1;
            scanf("%d",&t);
            add(a+tot+i,n,t-tt,0);
        }
        //s=0;
        sink=n++;
        //memset(res,0,sizeof(res));
        // cout<<n<<" "<<s<<" "<<t;
        int ans=dinicFlow();
        // cout<<ans;
        rep(i,0,nn)
        rep(j,0,m)
        {
            t=mask[i][j]+tot;
           sm[i][j]=edge[adj[t][0]].cap;
        }
        rep(i,0,nn)
        {
            rep(j,0,m)
            {
                if(j) printf(" ");
                printf("%d",sm[i][j]+1);
            }
            printf("\n");
        }
    }
    return 0;
}
