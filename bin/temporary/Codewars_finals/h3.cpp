#include<bits/stdc++.h>
using namespace std;
bool s[500][500];
bool crack(int r1,int c1,int r2,int c2,int n,int m)
{
bool x1,x2,x3,x4;
cout<<"r1="<<r1<<"\tc1="<<c1<<endl;
    if(r1==r2 && c1==c2)
        return 1;
    else
    {

        if((r1+1)<=n)
        {
            if(s[r1+1][c1]==1)
                {
                    s[r1+1][c1]=0;
                    x1=crack(r1+1,c1,r2,c2,n,m);
                }
            else
                x1=0;
        }
        if((r1-1)>0)
        {
            if(s[r1-1][c1]==1)
            {
                s[r1-1][c1]=0;
                x2=crack(r1-1,c1,r2,c2,n,m);

            }else
                x2=0;
        }
        if((c1+1)<=m)
        {
            if(s[r1][c1+1]==1)
             {
                s[r1][c1+1]=0;
                 x3=crack(r1,c1+1,r2,c2,n,m);
             }
            else
                x3=0;
        }
        if((c1-1)>0)
        {
            if(s[r1][c1-1]==1)
             {
             s[r1][c1-1]=0;
             x4=crack(r1,c1-1,r2,c2,n,m);
             }
            else
                x4=0;
        }
    return(x1+x2+x3+x4);
    }
}
int main()
{
  //bool s[500][500];
  int n,m,i,j,r1,c1,r2,c2;
  cin>>n>>m;

  for(i=1;i<=n;i++)
  {
    for(j=1;j<=m;j++)
    {   char c;
        cin>>c;
        if(c=='x'|| c=='X')
        s[i][j]=0;
        else if(c=='.')
        s[i][j]=1;
    }
  }

    cin>>r1>>c1;
    cin>>r2>>c2;
  if(s[r1][c1]==0)
{
    if(crack(r1,c1,r2,c2,n,m)==1)
        cout<<"YES";
    else
        cout<<"NO";
}
}
