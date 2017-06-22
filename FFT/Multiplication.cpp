#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
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
#define pi acos(-1)
#define NN 50003
#define mMax 100010
#define nMax 200
#define MAXN 300010
#define maxN 1<<18
#define SZ(a) a.size()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define rep1(i,b) for(int i=1;i<=b;i++)
#define rep2(i,b) for(int i=0;i<b;i++)
#define REP(i,b) for(int i=0;i<b;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define all(A) A.begin(),A.end()
#define isf(a) scanf("%d",&a);
#define Lsf(a) scanf("%I64d",&a);
#define lsf(a) scanf("%lld",&a);
#define csf(a) scanf("%c",&a);
using namespace std;
#define LSOne(S) (S & (-S))
// Tested:
// - FBHC 2016 R3 - Problem E
// - https://open.kattis.com/problems/polymul2 (need long double)
// Note:
// - a[2] will have size <= 2*n
// - When rounding, careful with negative numbers:
int my_round(double x) {
    if (x < 0) return -my_round(-x);
    return (int) (x + 1e-3);
}


typedef complex<double> cplex;
int rev[maxN];
cplex wlen_pw[maxN], fa[maxN], fb[maxN];

void fft(cplex a[], int n, bool invert) {
    for (int i = 0; i < n; ++i) if (i < rev[i]) swap (a[i], a[rev[i]]);

    for (int len = 2; len <= n; len <<= 1) {
        double alpha = 2 * PI / len * (invert ? -1 : +1);
        int len2 = len >> 1;

        wlen_pw[0] = cplex(1, 0);
        cplex wlen(cos(alpha), sin(alpha));
        for (int i = 1; i < len2; ++i) wlen_pw[i] = wlen_pw[i-1] * wlen;

        for (int i = 0; i < n; i += len) {
            cplex t, *pu = a+i, *pv = a + i + len2,
                    *pu_end = a + i + len2, *pw = wlen_pw;
            for (; pu != pu_end; ++pu, ++pv, ++pw) {
                t = *pv * *pw;
                *pv = *pu - t;
                *pu += t;
            }
        }
    }

    if (invert) REP(i, n) a[i] /= n;
}

void calcRev(int n, int logn) {
    REP(i, n) {
        rev[i] = 0;
        REP(j, logn) if (i & (1 << j)) rev[i] |= 1 << (logn - 1 - j);
    }
}

// A and B are polynomials
// A = a[0] + a[1] * x + a[2] * x^2 +.... + a[i] * x^i + ... + a[na-1] * x^(na-1)
// Same def goes for B
void mulpoly(int a[], int b[], ll c[], int na, int nb, int &n) {
    int l = max(na, nb), logn = 0;
    for (n = 1; n < l; n <<= 1) ++logn;
    n <<= 1; ++logn;
    calcRev(n, logn);

    REP(i,n) fa[i] = fb[i] = cplex(0);
    REP(i,na) fa[i] = cplex(a[i]);
    REP(i,nb) fb[i] = cplex(b[i]);

    fft(fa, n, false);
    fft(fb, n, false);

    REP(i,n) fa[i] *= fb[i];
    fft(fa, n, true);

    REP(i,n) c[i] = (ll)(fa[i].real() + 0.5);
}
char A[maxN];
char B[maxN];
char C[maxN];
int coeffA[maxN];
int coeffB[maxN];
LL coeffC[maxN];
int main()
{
  scanf("%s",A);
  scanf("%s",B);
  int na,nb;
  na=strlen(A);
  nb=strlen(B);
  for(int i=na-1,j=0;i>=0;i--,j++) coeffA[j]=A[i]-'0';
  for(int i=nb-1,j=0;i>=0;i--,j++) coeffB[j]=B[i]-'0';
  int nc;
  mulpoly(coeffA,coeffB,coeffC,na,nb,nc);
  ll carry=0;
  for(int i=0;i<nc;i++)
  {
    coeffC[i]+=carry;
    C[i]=coeffC[i]%10 +'0';
    carry=coeffC[i]/10;
  }
  reverse(C,C+nc);
  bool flag=false;
  for(int i=0;i<nc;i++)
    if(C[i]>'0' || flag)
    {
      flag=true;
      printf("%c",C[i]);
    }
  if(!flag) printf("0");
  printf("\n");
  return 0;
}
