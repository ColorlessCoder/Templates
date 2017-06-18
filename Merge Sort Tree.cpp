#include <bits/stdc++.h>
#include <bitset>   // compact STL for Sieve, more efficient than vector<bool>!
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
#define vi vector<int>
#define vll vector<LL>
#define pii pair<int,int>
#define pli pair<LL,int>
#define pll pair<LL,LL>
#define fr first
#define sc second
#define MAX 50010
#define LL   long long int
#define ll   long long int
//#define LLL long long int
#define inf 1ll<<62
#define mod 1000000007
#define PI acos(-1)
#define NN 50003
#define mMax 100010
#define nMax 200
#define MAXN 1000100
#define SZ(a) a.size()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define rep1(i,b) for(int i=1;i<=b;i++)
#define rep2(i,b) for(int i=0;i<b;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define all(A) A.begin(),A.end()
#define isf(a) scanf("%d",&a);
#define Lsf(a) scanf("%I64d",&a);
#define lsf(a) scanf("%lld",&a);
#define INF 1e9
#define EPS 1e-9
#define csf(a) scanf("%c",&a);
using namespace std;
class MergeSortTree
{
  public: 
  vector<vi > Tree;
  vi _A;
  int n;
  void build(int p,int L,int R)
  {
    if(L==R)
    {
      Tree[p].pb(_A[L]);
      return;
    }
    int p1=p<<1,p2=(p<<1)+1;
    int mid=(L+R)>>1;
    build(p1,L,mid);
    build(p2,mid+1,R);
    L=SZ(Tree[p1]);
    R=SZ(Tree[p2]);
    for(int i=0,j=0;i<L || j<R;)
    {
      if(i==L) Tree[p].pb(Tree[p2][j++]);
      else if(j==R) Tree[p].pb(Tree[p1][i++]);
      else if(Tree[p1][i]<Tree[p2][j]) Tree[p].pb(Tree[p1][i++]);
      else Tree[p].pb(Tree[p2][j++]);
    }
    return;
  }
  MergeSortTree(const vi A)
  {
    _A=A;
    n=A.size();
    Tree.assign(4*n,vi());
    build(1,0,n-1);
  }
  int query() 
  {
    return 0;
  }
  void show()
  {
    for(int i=1;i<4*n;i++)
      {
        cout<<i<<"-> ";
        rep2(j,SZ(Tree[i]))
          cout<<Tree[i][j]<<" ";
        cout<<endl;
      }
  }
};
int main()
{
  vi A;
  A.pb(9);
  A.pb(8);
  A.pb(7);
  A.pb(6);
  A.pb(5);
  A.pb(4);
  A.pb(3);
  A.pb(2);
  A.pb(1);
  MergeSortTree B(A);
  B.show();
  return 0;
}
