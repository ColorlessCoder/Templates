vector<point>P;
bool check_inside(int L,int R,point test) // check_inside(1,P.size()-2,test) if P.back()=P[0]
{
  // cout<<P[0].x<<" "<<P[0].y<<endl;
  // cout<<P[L].x<<" "<<P[L].y<<endl;
  while(1){
  if(L>R) break;
  if(R-L+1 ==1 ) {return dist(P[0],test)+dist(P[L],test) == dist(P[0],P[L]);}
  if(R-L+1 == 2)
  { 
    return (colllinear(P[0],P[L],test)+colllinear(P[L],P[R],test)+colllinear(P[R],P[0],test) == colllinear(P[L],P[R],P[0]));
  }
  int mid=(L+R)/2;
  if(!ccw(P[0],P[mid],test)) R=mid;
  else L=mid;
  }
  return false;
} 
