#include<bits/stdc++.h>
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
#define INF 1000000
#define mod 1000000007
#define PI acos(-1)
#define NN 50003
#define mMax 100010
#define nMax 200
#define MAXN 200010
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
#define csf(a) scanf("%c",&a);
using namespace std;
typedef pair<int, int> ii;

#define MAX_N 200010                         // second approach: O(n log n)
char T[MAX_N];                   // the input string, up to 100K characters
int n;                                        // the length of input string
int RA[MAX_N], tempRA[MAX_N];        // rank array and temporary rank array
int SA[MAX_N], tempSA[MAX_N];    // suffix array and temporary suffix array
int c[MAX_N];                                    // for counting/radix sort


int Phi[MAX_N];                      // for computing longest common prefix
int PLCP[MAX_N];
int LCP[MAX_N];  // LCP[i] stores the LCP between previous suffix T+SA[i-1]
                                              // and current suffix T+SA[i]

//bool cmp(int a, int b) { return strcmp(T + a, T + b) < 0; }      // compare



void countingSort(int k) {                                          // O(n)
  int i, sum, maxi = max(300,n);   // up to 255 ASCII chars or length of n
  memset(c, 0, sizeof c);                          // clear frequency table
  for (i = 0; i < n; i++)       // count the frequency of each integer rank
    c[i + k < n ? RA[i + k] : 0]++;
  for (i = sum = 0; i < maxi; i++) {
    int t = c[i]; c[i] = sum; sum += t;
  }
  for (i = 0; i < n; i++)          // shuffle the suffix array if necessary
    tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
  for (i = 0; i < n; i++)                     // update the suffix array SA
    SA[i] = tempSA[i];
}

void constructSA() {         // this version can go up to 100000 characters
  int i, k, r;
  for (i = 0; i < n; i++) RA[i] = T[i];                 // initial rankings
  for (i = 0; i < n; i++) SA[i] = i;     // initial SA: {0, 1, 2, ..., n-1}
  for (k = 1; k < n; k <<= 1) {       // repeat sorting process log n times
    countingSort(k);  // actually radix sort: sort based on the second item
    countingSort(0);          // then (stable) sort based on the first item
    tempRA[SA[0]] = r = 0;             // re-ranking; start from rank r = 0
    for (i = 1; i < n; i++)                    // compare adjacent suffixes
      tempRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
      (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
    for (i = 0; i < n; i++)                     // update the rank array RA
      RA[i] = tempRA[i];
    if (RA[SA[n-1]] == n-1) break;               // nice optimization trick
} }
void computeLCP() {
  int i, L;
  Phi[SA[0]] = -1;                                         // default value
  for (i = 1; i < n; i++)                            // compute Phi in O(n)
    Phi[SA[i]] = SA[i-1];    // remember which suffix is behind this suffix
  for (i = L = 0; i < n; i++) {             // compute Permuted LCP in O(n)
    if (Phi[i] == -1) { PLCP[i] = 0; continue; }            // special case
    while (T[i + L] == T[Phi[i] + L]) L++;       // L increased max n times
    PLCP[i] = L;
    L = max(L-1, 0);                             // L decreased max n times
  }
  for (i = 0; i < n; i++)                            // compute LCP in O(n)
    LCP[i] = PLCP[SA[i]];   // put the permuted LCP to the correct position
}
int check(int len,int m) // T contains m repeated string of length len
{
    int d=-1,temp=1,ans=-1;
    for(int i=0;i<n;i++)
        if(LCP[i]>=len)
        {
            temp++;
            if(d==-1) d=SA[i-1];
            d=max(SA[i],d);
            if(temp>=m) ans=max(ans,d);
        }
        else 
        {
            d=-1;
            temp=1;
        }
    return ans;
}
bool match(char *P)
{
  int lo=0,hi=n,mid,ans=-1,m=strlen(P);
  for(int i=0;i<15;i++)
  {
    if(lo>hi) break;
    mid=(lo+hi)>>1;
    int res=strncmp(T+SA[mid],P,m);
    if(res>=0) ans=mid,hi=mid-1;
    else lo=mid+1;
  }
  if(ans==-1) return 0;
  if(strncmp(T+SA[ans],P,m)==0) return true;
  return false;
}
LL dis_sub()
{
  LL ans=0;
  rep2(i,n) 
  ans+= (n-1-SA[i]-LCP[i]);
  return ans;
}
pii kth(LL k,pii prev=mp(0,0)) // prev = {previous SA index accessed,how much accessed of it}
{                              // k= how much more from previous query
  for(int i=prev.fr;i<n;i++)   // Eg: query1, 5th substring, then kth(5,mp(0,0)) 
  {                            // Suppose query1 return {a,b} that means string starts
                               // at SA[a] and ends at SA[a]+b-1
                               // Query2 , 8th substring, then kth(8-5,mp(a,b))=kth(3,{a,b})
                               // and so on.
                               // Note: Querys should be sorted first. Offline
    int temp=n-1-SA[i]-max(LCP[i],prev.sc);
    //cout<<temp<<" "<<k<<" "<<i<<endl;
    if(temp>=k)
      return mp(i,max(LCP[i],prev.sc)+k);
    k-=temp;
    prev.sc=0;
  }
  return mp(-1,-1);
}
int LCS(int a,int b) // a=length of first string,b=length of second(unnecessary b)
{
  int ans=0;
  for(int i=0;i<n;i++)
  {
    if(LCP[i]>0)
    {
      if(SA[i-1]<=a && SA[i]>a)
      {
        ans=max(ans, min(LCP[i],min(a-SA[i-1],n-1-SA[i])));
      }
      else if(SA[i]<=a && SA[i-1]>a)
      {
        ans=max(ans, min(LCP[i],min(a-SA[i],n-1-SA[i-1])));
      }
    }
  }
  return ans;
}
char LRstr[MAX_N];
int LRS()/// LRstr contain longest repeated substr, return how many times it occurs.
{
  int ans=0,a,b=1;
  for(int i=0;i<n;i++)
    if(LCP[i]>ans)
    {
      ans=LCP[i];
      a=i-1;
    }
  if(ans==0) return -1;
  for(int i=a+1;i<n;i++)
    if(LCP[i]>=ans)
      b++;
    else break;
  for(int j=0;j<ans;j++)
    LRstr[j]=T[SA[a]+j];
  LRstr[ans]='\0';
  return b;
}
char P[1050];
char nstr[MAX_N];
int main()
{
    int t;
    t=1;
    //cin>>t;
    int I=0;
    n=0;
    while(t--)
    {
      scanf("%s",T);
      n=strlen(T);
      int m=n;
      rep2(i,n) T[i+n]=T[i];
      n=n+n;
      T[n++]='$';
      constructSA();
      computeLCP();
      int ans=n;
      for(int i=0;i<n;i++)
        if(SA[i]<m){
          if(ans!=n)
          {
            if(LCP[i]>=m) ans=min(SA[i],ans);
            else break;
          }
          else ans=SA[i];
        }
        else if(ans!=n) break;
        printf("%d\n",ans);
    } 
    
    return 0;
}
