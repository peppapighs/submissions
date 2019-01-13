#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n,k,p;
long long dp[2][N],ps[N];

int main() {
	scanf("%d%d%d",&n,&k,&p);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&ps[i]);
		ps[i]+=ps[i-1];
	}
	int a=0;

	if(k*p>=n) {
		printf("%lld",ps[n]);
		return 0;
	}

	for(int i=1;i<=k;i++) {
		for(int j=0;j<=p;j++) dp[a][j] = INT_MIN;
		for(int j=p;j<=n;j++) {
			dp[a][j] = max(dp[a][j-1],dp[1-a][j-p]+ps[j]-ps[j-p]);
		}
		a=1-a;
	}

	printf("%lld",dp[1-a][n]);

	return 0;
}