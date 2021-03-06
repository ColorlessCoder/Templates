#include<bits/stdc++.h>
#define vi vector<LL>
#define pii pair<LL,LL>
#define fr first
#define sc second
#define MAX 50010
#define LL  long long int
#define ll  long long int
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
typedef map<int, int> mii;

ll _sieve_size;
bitset<100010> bs;   // 10^7 should be enough for most cases
vi primes;   // compact list of primes in form of vector<int>


// first part

void sieve(ll upperbound) {          // create list of primes in [0..upperbound]
  _sieve_size = upperbound + 1;                   // add 1 to include upperbound
  bs.set();                                                 // set all bits to 1
  bs[0] = bs[1] = 0;                                     // except index 0 and 1
  for (ll i = 2; i <= _sieve_size; i++) if (bs[i]) {
    // cross out multiples of i starting from i * i!
    for (ll j = i * i; j <= _sieve_size; j += i) bs[j] = 0;
    primes.push_back((int)i);  // also add this vector containing list of primes
} }                                           // call this method in main method

bool isPrime(ll N) {                 // a good enough deterministic prime tester
  if (N <= _sieve_size) return bs[N];                   // O(1) for small primes
  for (int i = 0; i < (int)primes.size(); i++)
    if (N % primes[i] == 0) return false;
  return true;                    // it takes longer time if N is a large prime!
}                      // note: only work for N <= (last prime in vi "primes")^2


// second part
#define vpi vector<pii >
vpi primeFactors(ll N) {   // remember: vi is vector of integers, ll is long long
  vpi factors;                    // vi `primes' (generated by sieve) is optional
  ll PF_idx = 0, PF = primes[PF_idx];     // using PF = 2, 3, 4, ..., is also ok
  while (N != 1 && (PF * PF <= N)) {   // stop at sqrt(N), but N can get smaller
        int f=0,c=0;
    while (N % PF == 0) { N /= PF; c++;f=1; }    // remove this PF
    if(f) factors.pb(mp(PF,c));
    PF = primes[++PF_idx];                              // only consider primes!
  }
  if (N != 1) factors.push_back(mp(N,1));     // special case if N is actually a prime
  return factors;         // if pf exceeds 32-bit integer, you have to change vi
}
void allfactor(int i,int n,LL val,vpi A,vi &ret)
{
    if(i==n) {
        ret.pb(val);
        return;
    }
    LL temp=1;
    for(int j=0;j<=A[i].sc;j++)
    {
        allfactor(i+1,n,val*temp,A,ret);
        temp*=A[i].fr;
    }
    return;
}
LL bigpow(LL n,LL p)
{
    if(p==1) return n;
    if(p%2) return bigpow(n,p-1)*p;
    LL a=bigpow(n,p/2);
    return a*a;
}

void dfs(LL n,LL val,LL mpf,vi &ret)
{
    if(n==1) /// phi(x)=1 if x=1 or 2
    {
        ret.pb(val);
        if(mpf<2)   ret.pb(val*2);
    }
    if(n%2) return;
    vpi pfs=primeFactors(n);
    vi facts;
    allfactor(0,pfs.size(),1,pfs,facts);
    sort(facts.begin(),facts.end());
//    for(int i=0;i<facts.size();i++)
//        cout<<facts[i]<<" ";
    LL cc;
    for(int i=facts.size()-1;i>=0  && (facts[i]+1)>mpf;i--)
        if(isPrime(facts[i]+1))
        {
             cc=facts[i]+1;
            LL a=facts[i],b=facts[i]+1;
                while(n%a==0)   {
                    dfs(n/a,val*b,facts[i]+1,ret);
                    b*= (facts[i]+1);
                    a*=(facts[i]+1);
                }
        }
    return;
}
int main()
{
    sieve(100010);
    LL n;
    while(scanf("%lld",&n)==1)
    {
        vi ans;
//        vpi tt=primeFactors(n);
//        allfactor(0,tt.size(),1,tt,ans);
//         for(int i=0;i<ans.size();i++)
//            {
//
//                printf("%lld ",ans[i]);
//
//            }
        dfs(n,1,0,ans);
        if(ans.size()==0)
            printf("No solution.\n");
        else{
            int I=0;
            sort(ans.begin(),ans.end());
            ans.resize(unique(ans.begin(),ans.end())-ans.begin());
            for(int i=0;i<ans.size();i++)
            {
                if(I) printf(" ");
                printf("%lld",ans[i]);
                I=1;
            }
            printf("\n");
        }
    }
    return 0;
}
