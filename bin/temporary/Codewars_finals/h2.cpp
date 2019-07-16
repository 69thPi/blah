#include<bits/stdc++.h>
using namespace std;
int n,m,k;
double dp[53][10002];
double solve(int idx,int sum)
{
	if(idx>m)
	{
		if(sum==0)
			return 1;
		return 0;
	}
	if(dp[idx][sum]!=-1) return dp[idx][sum];
	double res=0;
	for(int i=1;i<=n;i++)
	{
		if(sum>=i)
			res+=(1.0/n)*solve(idx+1,sum-i);
		else break;
	}
	return dp[idx][sum]=res;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>m>>n>>k;
		for(int i=0;i<53;i++)
			for(int j=0;j<10002;j++)
				dp[i][j]=-1;
		double res=solve(1,k);
		int ct=0;
		while(res!=0 && res<10)
		{
			res*=10;
			ct++;
		}
		res/=10;
		if(res!=0) ct-=1;
		printf("%.3lf %d\n",res,ct);
	}
	return 0;
}
