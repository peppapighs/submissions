#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

int k;
char arr[N];
int dp[N][N];

int solve(int i,int j) {
	if(dp[i][j]!=-1) return dp[i][j];
	if(i>=j) return dp[i][j] = 0;
	if(arr[i]==arr[j]) return dp[i][j] = max(dp[i][j],solve(i+1,j-1)+1);
	for(int k=i;k<j;k++) dp[i][j] = max(dp[i][j],solve(i,k)+solve(k+1,j));
	return dp[i][j];
}

int main() {
	scanf("%d",&k);
	for(int i=1;i<=k;i++) {
		scanf(" %c",&arr[i]);
	}
	memset(dp,-1,sizeof(dp));
	printf("%d\n",solve(1,k));

	return 0;
}