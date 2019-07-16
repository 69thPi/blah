#include<bits/stdc++.h>
using namespace std;

int main()
{
 int t,i,sum;
 long int n;
 cin>>t;
 if(1<=t && t<=10)
 {
    for(i=0; i<t; ++i)
    {
        cin>>n;
        if(n>=1 && n<=100000)
        {
            sum=n*(n+1)/2;
            cout<<sum-1<<endl;
        }
    }
}
}
