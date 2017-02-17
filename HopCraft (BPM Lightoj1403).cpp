#include<bits/stdc++.h>
#define vi vector<int>
#define pii pair<int,int>
#define fr first
#define sc second
#define MAX 50010
#define LL unsigned long long int
#define inf 10000
#define oo 10000
#define INF 10000000
//#define mod 1000000007
#define mMax 30010
#define nMax 2010
#define pb push_back
#define mp make_pair
//#define N 200
#define SZ(a) ((int)a.size())
#define Clear(a,b) memset(a,b,sizeof(a))
using namespace std;
/// LeftEle= no of element int left side
/// left side has element from 1 to leftEle
/// right side has element from leftEle+1 to rightEle+leftEle
/// we have to add edge with respect to this indexing
/// by mapping them or something else
int N,M,L[2200],R[2200],dist[2200],leftEle,rightEle;
vector<vi>E;
bool BFS()
{
    queue<int>Q;
    for(int i=1; i<=leftEle; i++)
    {
        if(!L[i])
        {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[0] = INF;
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if(!u) continue;
        for(int i=0; i<SZ(E[u]); i++)
        {
            int v = E[u][i];
            if(dist[R[v]] == INF)
            {
                dist[R[v]] = dist[u]+1;
                Q.push(R[v]);
            }
        }
    }
    return (dist[0]!=INF);
}
bool dfs(int u)
{
    if(u==0) return true;
    for(int i=0; i<SZ(E[u]); i++)
    {
        int v = E[u][i];
        if(dist[u]+1 == dist[R[v]] &&dfs(R[v]))
        {
            L[u] = v;
            R[v] = u;
            return true;
        }
    }
    dist[u] = INF;
    return false;
}
int HopCraft()
{
    Clear(L,0);
    Clear(R,0);
    int ret = 0;
    while(BFS())
    {
        for(int i=1; i<=leftEle; i++)
            if(!L[i] &&dfs(i))
                ret++;
    }
    return ret;
}
void add(int u,int v)
{
    E[u].push_back(v);
    E[v].push_back(u);
}
int n,m;
int main()
{
    int T,I=1;
    cin>>T;
    while(T--)
    {
        printf("Case %d: ",I++);
        scanf("%d %d",&n,&m);
        E.assign(2*n  +2,vi());
        int a,b;
        leftEle=n;
        rightEle=n;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d",&a,&b);
            add(a,b+n);
        }
        int ans=n- HopCraft();
        printf("%d\n",ans);
    }
    return 0;
}
