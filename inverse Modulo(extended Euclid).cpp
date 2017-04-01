
ll ext_euclid(ll a, ll b,ll Mod)
{
    ll q, ps=1, s=0, pt=0, t=1, r;
        if(b==0) while(1);
    while(a%b != 0)
    {
        q = a/b; r = a-q*b;
 
        ll tmps=s, tmpt=t;
        s = ps-q*s, t = pt-q*t;
        ps = tmps, pt = tmpt;
 
        a=b; b=r;
        if(b==0) while(1);
    }
    return (t+Mod)%Mod;
}
