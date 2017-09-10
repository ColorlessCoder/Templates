vi restricted;
bool check(int unm)
{
     queue<int>Q;
    for(int i=1; i<=leftEle; i++)
    {
        dist[i] = INF;
    }
    dist[unm] = 0;
    dist[0] = INF;
    int cur=-1;
    Q.push(unm);
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if(!u) continue;
        for(int i=0; i<SZ(E[u]); i++)
        {
            int v = E[u][i];
            if(L[u]==v) continue;
            if(restricted[v]) continue;
            if(R[v]==0){
                dist[v]=dist[u]+1;
                par[v]=u;
                cur=v;break;
            }
            if(dist[R[v]] == INF)
            {
                par[v]=u;
                dist[R[v]] = dist[u]+1;
                Q.push(R[v]);
            }
        }
    }
    if(cur!=-1)
    {
        int i=0;
        int dd=cur;
        while(1)
        {
            R[cur]=par[cur];
            int temp=L[par[cur]];
            L[par[cur]]=cur;
            if(temp==0) break;
            cur=temp;
        }
        return true;
    }
    return false;
}

int main()
{
  /* Pseudocode soln: https://vjudge.net/solution/10676753    -> shakil_ruet
  
  for left=1 to 10
      for right=a to h
          if R[right] == left
              restrict[right]= restrict[left]= 1
              save(right)
          else if restricted[right] == 0
              right2 = L[left]
              left2 = R[right]
              if left2 == 0
                  R[right]= left
                  R[right2] = 0
                  L[left]= right
                  restrict[right]= restrict[left]= 1
                  save(right)
                  break
              else
                  R[right2]=0
                  L[left2]=0
                  L[left]=right
                  R[right]=left
                  restrict[right]= restrict[left]= 1
                  if check(left2)
                    save(right)
                    break
                  else
                    R[right]=left2
                    L[left2]=right
                    L[left]=right2
                    R[right2]=left
                    restrict[right]= restrict[left]= 0
     end
  
  */
}
