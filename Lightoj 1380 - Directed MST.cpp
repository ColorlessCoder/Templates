#include<bits/stdc++.h>
#define vi vector<int>
#define rep(a,b,n) for(int a=b;a<n;a++)
#define pii pair<int,int>
#define fr first
#define sc second
#define LL long long int
#define inf 1e15
using namespace std;
vector<pair<LL,pii > > Edges;
LL dmst(int N,int root) {
  vector<LL> cost(N), back(N), label(N), bio(N);
  LL ret = 0;
int m=Edges.size();
  while(1) {
    rep(i,0,N) cost[i] = inf;
    rep(i,0,m) {
        pair<LL,pii > e=Edges[i];
      if (e.sc.fr == e.sc.sc) continue;
      if (e.fr < cost[e.sc.sc]) cost[e.sc.sc] = e.fr, back[e.sc.sc] = e.sc.fr;
    }
    cost[root] = 0;
    rep(i,0, N) if (cost[i] == inf) return -1;
    rep(i,0, N) ret += cost[i];

    int K = 0;
    rep(i,0, N) label[i] = -1;
    rep(i,0,  N) bio[i] = -1;

    rep(i,0,N) {
      int x = i;
      for (; x != root && bio[x] == -1; x = back[x]) bio[x] = i;

      if (x != root && bio[x] == i) {
        for (; label[x] == -1; x = back[x]) label[x] = K;
        ++K;
      }
    }
    if (K == 0) break;

    rep(i,0,N) if (label[i] == -1) label[i] = K++;

    rep(i,0,m){
            pair<LL,pii > e=Edges[i];
      int xx = label[e.sc.fr];
      int yy = label[e.sc.sc];
      if (xx != yy) e.fr -= cost[e.sc.sc];
      e.sc.fr = xx;
      e.sc.sc = yy;
      Edges[i]=e;
    }

    root = label[root];
    N = K;
  }

  return ret;
}
int main(){
    int n;
    int m;
    int T,I=1;
    cin>>T;
    while(T--)
    {
        scanf("%d %d",&n,&m);
        printf("Case %d: ",I++);
        Edges.clear();
        int a,b,k;
        scanf("%d",&k);
        LL c;
        LL ans=0;
        rep(i,0,m)
        {
           scanf("%d %d %lld",&a,&b,&c);
           //a--;b--;
           //ans+=c;
            Edges.push_back(make_pair(c,make_pair(a,b)));

        }
        ans=dmst(n,k);
        if(ans==-1)
            printf("impossible\n");
        else
        printf("%lld\n",ans);
    }
    return 0;
}
