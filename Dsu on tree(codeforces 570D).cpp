#include<bits/stdc++.h>
#define vi vector<int>
#define pii pair<int,int>
#define fr first
#define sc second
#define MAX 50010
#define LL long long int
#define inf 1e15
#define INF 10000000
#define mod 1000000007
#define mMax 30010
#define nMax 2010
#define SZ(a) a.size()
#define pb push_back
#define mp make_pair
#define N 500010
using namespace std;
LL bigmod(LL a,LL p)
{
    if(p==0ll) return 1ll;
    if(p%2==1) return ((a%mod) * bigmod(a,p-1))%mod;
    LL b=bigmod(a,p/2ll);
    return (b*b)%mod;
}
vector<vi > E;
int BC[N];
int cnt[30][N];
LL ans[N];
int mark[N];
int col[N];
int sz[N];
int H[N];
LL total,mcnt;
void clr(int a)
{
    E.assign(a+1,vi());
    memset(BC,-1,sizeof(BC));
    memset(cnt,0,sizeof(cnt));
    memset(ans,0,sizeof(ans));
    memset(sz,0,sizeof(sz));
    memset(mark,0,sizeof(mark));
}
vector<pii> query[N];
void getsz(int u,int p,int h=1)
{
    H[u]=h;
    sz[u]++;
    int z=E[u].size();
    int best=0;
    for(int i=0;i<z;i++)
        if(E[u][i]!=p)
    {
        getsz(E[u][i],u,h+1);
        if(sz[E[u][i]]>best)
        {
            best=sz[E[u][i]];
            BC[u]=E[u][i];
        }
        sz[u]+=sz[E[u][i]];
    }
    return;
}
void add(int u,int p,int x)
{
    cnt[col[u]][H[u]]+=x;
    int z=E[u].size();
    for(int i=0;i<z;i++)
        if((E[u][i]!=p)&& mark[E[u][i]]==0)
                add(E[u][i],u,x);
    return ;
}
void dfs(int u,int p,int x)
{
    int z=E[u].size();
    for(int i=0;i<z;i++)
        if((E[u][i]!=p)&& (BC[u]!=E[u][i]))
                dfs(E[u][i],u,1);
    if(BC[u]!=-1)
    {
        dfs(BC[u],u,0);mark[BC[u]]=1;
    }
    add(u,p,1);
    ///answer
    z=query[u].size();
    for(int i=0;i<z;)
    {
        int h=query[u][i].fr;
        int a=0,b;
        for(int j=0;j<26;j++)            if(cnt[j][h]%2) a++;
        if(a>1) b=0; else b=1;
        while(i<z && query[u][i].fr==h) {
            ans[query[u][i].sc]=b;
            i++;
        }
    }
    ///
    if(BC[u]!=-1)
    mark[BC[u]]=0;
    if(x) add(u,p,-1);
    return ;
}
char str[N];
int main()
{
    int n,m;
    cin>>n>>m;
    int a,b;
    clr(n);
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&a);
        E[a].pb(i);
        E[i].pb(a);
    }
    scanf("%s",str);
    for(int i=1;i<=n;i++)
    {
        col[i]=str[i-1]-'a';
    }
    for(int i=0;i<m;i++)
    {
        scanf("%d %d",&a,&b);
        query[a].push_back(mp(b,i));
    }
    for(int i=1;i<=n;i++) sort(query[i].begin(),query[i].end());
    getsz(1,0);
    dfs(1,0,0);
    for(int i=0;i<m;i++)
        if(ans[i]==0)  printf("No\n");
    else printf("Yes\n");
    return 0;
}
