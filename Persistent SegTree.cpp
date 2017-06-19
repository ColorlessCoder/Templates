
struct node{
  int left,right;
  int val;
} Tree[3000010];
int sz=0;
class PersistentTree
{
  public:
  vi A;
  vi roots;
  int n,root;
  void build(int p,int L,int R)
  {
    if(L==R)
    {
      Tree[p].val=A[L];
      return;
    }
    Tree[p].left=++sz;
    Tree[p].right=++sz;
    int mid=(L+R)>>1;
    build(Tree[p].left,L,mid);
    build(Tree[p].right,mid+1,R);
    Tree[p].val=Tree[Tree[p].left].val+Tree[Tree[p].right].val;
    return;
  }
  PersistentTree(const vi _A)
  {
    A=_A;
    n=A.size();
    roots.pb(0);
    build(0,0,n-1);
    root=0;
  }
  int query(int p,int L,int R,int x,int y)
  {
    if(L>y || R<x) return 0;
    if(x<=L && R<=y) return Tree[p].val;
    int p1=Tree[p].left;
    int p2=Tree[p].right;
    int mid=(L+R)>>1;
    return query(p1,L,mid,x,y) + query(p2,mid+1,R,x,y);
  }
  void update(int p,int q,int L,int R,int ind,int x)
  {
    if(L==R) {
      Tree[q].val=Tree[p].val+x;
      return;
    }
    int mid=(L+R)>>1;
    if(L<=ind && ind<=mid)
    {
      Tree[q].right=Tree[p].right;
      Tree[q].left=++sz;
      update(Tree[p].left,Tree[q].left,L,mid,ind,x);
    }
    else
    {
      Tree[q].left=Tree[p].left;
      Tree[q].right=++sz;
      update(Tree[p].right,Tree[q].right,mid+1,R,ind,x);
    }
    Tree[q].val=Tree[Tree[q].left].val+Tree[Tree[q].right].val;
    return;
  }

  //for user 
  void update(int ind,int x) // increase ind by x
  {
    int newroot=++sz;
    update(root,newroot,0,n-1,ind,x);
    root=newroot;
    roots.pb(newroot);
    return;
  }
  int query(int nroot,int L,int R) // nroot means the root of the tree at time nroot
  {
    return query(roots[nroot],0,n-1,L,R);
  }
  
  //end of general structure
  
  /***************************************************************************************************************************/
  
  // main query for MKTHNUM SPOJ.
  int main_query(int p,int q,int L,int R,int k)
  {
    if(L==R) return L;
    int mid=(L+R)>>1;
    if((Tree[Tree[p].left].val-Tree[Tree[q].left].val) <k)
    {
      k-= Tree[Tree[p].left].val-Tree[Tree[q].left].val;
    }
    else return main_query(Tree[p].left,Tree[q].left,L,mid,k);
    return main_query(Tree[p].right,Tree[q].right,mid+1,R,k);
  }
  int main_query(int x,int y,int k)
  {
    return main_query(roots[y],roots[x-1],0,n-1,k);
  }
};
