//codeforces http://codeforces.com/problemset/problem/128/B
deque<int> occ[100100];
LL sum[100100];
pii call(int Start,int fin,LL k,LL minus)
{
  if(sum[Start]-sum[Start-1] <=minus) return call(Start+1,fin,k,minus);
  if(Start==fin) return mp(Start,minus+1+k);
  int prev=Start;
  bool flag=true;
  int I=0;
  while(flag)
  {
    int u;
    if(occ[minus].empty()) {
      flag=false;
      u=fin+1;
    }
    else if(occ[minus].front()>fin)
    {
      flag=false;
      u=fin+1;
    }
    else u=occ[minus].front();
    if(prev==u) {
      occ[minus].pop_front();
      continue;
    }
    LL len=sum[u-1]-sum[prev-1] - 1ll*minus*1ll*(u-prev);
    if(u-prev >k) return mp(prev,minus+1);
    if(len >k){
     return call(prev,u-1,k-(u-prev),minus+1);
    }
    k-=len;
    for(int i=prev+1;i<=u;i++) occ[LCP[i]].pop_front();
    prev=u;
  }
}
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
      T[n++]='$';
      constructSA();
      computeLCP();
      LL k=0;
      scanf("%d",&k);
      for(int i=2;i<n;i++)  occ[LCP[i]].pb(i);
      for(int i=1;i<n;i++)  sum[i]=sum[i-1]+n-1-SA[i];
      if(k> 1ll*n*(1ll*n- 1ll)/2) printf("No such line.\n");
      else {
        pii ans=call(1,n-1,k-1,0);
        //cout<<ans.fr<<" "<<ans.sc;
        for(int i=0;i<ans.sc;i++) printf("%c",T[SA[ans.fr]+i]);
          printf("\n");
      }
    } 
    return 0;
}
