// version 1.0

LL moves(LL x,LL y){ // (0,0) to (x,y)
   x = abs(x);
   y = abs(y);
   if (x < y) swap(x,y);
   if(x==1 && y == 0) return 3;
   if(x==2 && y == 2) return 4;
   LL delta = x-y;
   if(y>delta) return delta - 2*floor((delta-y)/3.0);
   return delta - 2*floor((delta-y)/4.0);
}
LL moves(ll x1,ll y1,ll x2,ll y2)
{
  if(x1==x2 && y1==y2) return 0;
  return moves(x1-x2,y1-y2); //converting
}

// version 2.0

LL moves(ll x,ll y){ // (0,0) to (x,y)
   x = abs(x);
   y = abs(y);
   if (x < y) swap(x,y);
   if(x==1 && y == 0) return 3;
   if(x==2 && y == 2) return 4;
   if((!y) || (y<<1)<x)
   {
    LL c=y&1;
    LL a=x-(c<<1);
    LL b=a&3;
    return ((a-b)>>1)+c+b;
   }
   LL d=x-((x-y)>>1);
   LL z=((d%3)!=0);
   LL c=(x-y)&1;
   return ((d/3)*2) + c+ (z*2*(1-c));
}

LL moves(ll x1,ll y1,ll x2,ll y2)
{
  if(x1==x2 && y1==y2) return 0;
  if(x1>x2) swap(x1,x2),swap(y1,y2);
  if(y1>y2) y2=2*y1 -y2;
  return moves(x2-x1,y2-y1); //converting
}
