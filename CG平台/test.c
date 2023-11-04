#include <stdio.h>
#include <string.h>
int main(void)
{
	int v;
	int i,j;
	scanf("%d",&v);
	int n;
	scanf("%d",&n); 
	int weight[n];
	int dp[n+1][v+1];
	memset(weight,0,sizeof(weight));
	memset(dp,0,sizeof(dp));
	for(i=1; i<=n; i++)
	{
		scanf("%d",&weight[i]);
	}
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=v; j++)
		{
			if(j<weight[i])
			{
				dp[i][j] = dp[i-1][j];
			}
			else
			{
				dp[i][j] = dp[i-1][j] > dp[i-1][j-weight[i]]+weight[i] ? dp[i-1][j] : dp[i-1][j-weight[i]]+weight[i];
			}
		}
	}
	printf("%d",v-dp[i-1][j-1]);
 } 
