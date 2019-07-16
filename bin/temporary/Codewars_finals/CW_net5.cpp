#include<bits/stdc++.h>
using namespace std;
int main()
{
    int k,n,sum=0,i;
    cin>>n>>k;
   // cin>>k;
    for(i=1; i<=n; ++i)
    {
        sum+=pow(i,k);
    }
    cout<<sum;
}

