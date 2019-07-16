#include <bits/stdc++.h>

using namespace std;

#define LLI long long int
#define LLU long long unsigned

int main()
{

    int t;
    cin>>t;
    while(t--)
    {
    	int N,M,K;
    	cin>>M>>N>>K;

    	double DP[M+1][K+1],DP2[M+1][K+1];
    	double val=(double)((double)1/(double)N);

    	for(int i=0;i<=M;i++)
    	{
    		for(int j=0;j<=K;j++)
    		{
    			DP[i][j]=0;
    			DP2[i][j]=0;
    		}
    	}

    	for(int i=1;i<=N;i++)
    	{
    		DP[1][i]=val;
    		/*while(DP[1][i]<1)
    		{
    			DP[1][i]*=10;
    			DP2[1][i]++;
			}*/
    	}


    	for(int i=2;i<=M;i++)
    	{
    		for(int j=1;j<=K;j++)
    		{
    			for(int s=1;s<=N;s++)
    			{
    				if((j-s)>0)
    				{
    					DP[i][j]+=DP[i-1][j-s]*val;
    					//DP2[i][j]=DP[i][j-s];

    				}

    			}
    // 			while(DP[i][j]<1)
				// {
				// 	DP[i][j]*=10;
				// 	DP2[i][j]
				// }
    		}
    	}


    	int c=0;
    	while(DP[M][K]<1.0)
    	{
    		DP[M][K]*=10;
    		//cout<<DP[M][K]<<endl;
    		c++;
    	}

    	cout<<fixed<<setprecision(3)<<DP[M][K]<<" "<<c<<endl;
    }
	return 0;
}
