vector<vi > E,R,G;
vi col,TA;
void dfs1(int u)
{
	col[u]=1;

	for(int i=0;i<SZ(E[u]);i++)
		if(!col[E[u][i]])
			dfs1(E[u][i]);
	TA.pb(u);
	return ;
}
void dfs2(int u,int t)
{
	col[u]=t;
			//cout<<u<<" "<<t;
	for(int i=0;i<SZ(R[u]);i++)
		if(!col[R[u][i]]){
			dfs2(R[u][i],t);
		}
	return ;
}

int deg[100010];
void build(int t,int n)
{
	G.assign(t+1,vi());
	for(int i=1;i<=n;i++)
		for(int j=0;j<SZ(E[i]);j++)
			if(col[i] != col[E[i][j]]){
				G[col[i]].pb(col[E[i][j]]);
				deg[col[E[i][j]]]++;
			}
	return;
}

int SCC(int n)
{
	col.assign(n+1,0);
	TA.clear();
	for(int i=1;i<=n;i++)
		if(col[i]==0) dfs1(i);
	//cout<<TA.size();
	reverse(all(TA));
	//rep(i,SZ(TA)) cout<<TA[i]<<" ";
	int t=0;
	col.assign(n+1,0);
	for(int i=0;i<n;i++){
		if(!col[TA[i]]) dfs2(TA[i],++t);
		//cout<<t; 
	}
	build(t,n);
	//cout<<t;
	return t;
}
