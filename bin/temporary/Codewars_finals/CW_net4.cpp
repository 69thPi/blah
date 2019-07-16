#include<bits/stdc++.h>
using namespace std;
int main()
{
    int tp,i,a,f,x=0,j, k, l;
    cin>>tp;
    for(i=0; i<tp; ++i)
    {
            cin>>a;
            f=(2*a)-1;
            x=0;
            for(j=1; j<=a; ++j)
            {
                    x+=(j*f);
                    f-=2;
            }
            cout<<endl;
            for(k=0; k<a; ++k)
            {
                for(l=0;l<a; ++l)
                {
                    if(i==j)
                        cout<<i+1<<" ";
                    else
                        cout<<j+1<<" ";
                }
                cout<<endl;
            }
            cout<<x<<endl;
    }
}

