#define REP(i,n)    for(i=0;i<n;i++)
struct matrix
{
  int row,col;
  unsigned mat[100][100];
  matrix(int _row=0,int _col=0)
    {
    row=_row;col=_col;
    for(int i=0;i<row;i++)
    for(int j=0;j<col;j++) mat[i][j]=0;
    }
  matrix operator*(const matrix &B)const
{
  int i,j,k;
  matrix temp(row,B.col);
  REP(i,row) REP(j,B.col) REP(k,col)
    temp.mat[i][j]=(temp.mat[i][j]+  mat[i][k]*B.mat[k][j]);
  return temp;
}
matrix operator+(const matrix &B)const
{
  int i,j;
  matrix temp(row,col);
  REP(i,row) REP(j,col)
    temp.mat[i][j]=mat[i][j]+B.mat[i][j];
  return temp;
}
};
matrix PowerMat(matrix A,int P){
  int i;
  matrix R(A.row,A.col);
  REP(i,R.row) R.mat[i][i]=1;
  while(P){
    if(P&1) R=(R*A);
    P>>=1; A=(A*A);
  }
  return R;
}
