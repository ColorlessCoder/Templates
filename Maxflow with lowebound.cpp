int main()
{
   freopen("cooling.in","r",stdin);
   freopen("cooling.out","w",stdout);
  int T,I=1;
  //cin>>T;
  T=1;
  while(T--){
    //printf("Case %d: ",I++);
    int n,m;
    ind=0;
    scanf("%d %d",&n,&m);
    source=0;
    sink=n+1;
    adj.assign(sink + 1,vi());
    memset(A,0,sizeof(A));
    int D=0;
    rep2(i,m)
    {
      int a,b,c,d;
      scanf("%d %d %d %d",&a,&b,&c,&d);
      C[i]=c;
      add(a,b,d-c,0);
      A[b]+=c;
      A[a]-=c;
    }
    rep1(i,n)
    {
      if(A[i]>0){
      add(source,i,A[i],0);
      D+=A[i];
      }
      else 
      add(i,sink,-A[i],0);
    }
    //add(n,1,inf,0); // iff source and source exist
    int ans=dinicFlow();
    //cout<<ans ;
    if(ans==D)
    {
      printf("YES\n");
      rep2(i,m)
        printf("%d\n",edge[i*2 +1].cap+C[i]);
    }
    else printf("NO\n");
  }
  return 0;
}
