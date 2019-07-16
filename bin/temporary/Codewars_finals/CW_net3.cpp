#include<bits/stdc++.h>
using namespace std;
int main()
{
 int a1,b;//pos
int  c,d;//target
int n,m;
cin>>n>>m;
 char a[500][500];
for(int i=1;i<=n;i++)
{
 for(int j=1;j<=m;j++)
 a[i][j]='.';
}
cin>>a1;
cin>>b;
cin>>c;
cin>>d;
 //logic
 if(a1>c)
        cout<<"no";
 else
 {
      if(b!=1 || b!=m)
      {
            if(a[c-1]!='X' && a[c+1]!='X')
            {
            cout<<"yes";
            }
            else
            {
                if((b==c-1 || b==c+1) && bo[c]=='X')
                cout<<"yes";
                else
                cout<<"no";
            }
      }
      else
            cout<<"no";
 }

}
