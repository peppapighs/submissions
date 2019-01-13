#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n,k;
long long dp[N][2];
pair<long long,long long> can[N];

int main() {
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++) {
		scanf("%lld%lld",&can[i].first,&can[i].second);
	}

	sort(can,can+n);
	dp[0][0]=-1;
	dp[0][1]=0;
	for(int i=1;i<n;i++) {
		long long dx1=can[i].first-can[i-1].first;
		if(dx1<=k) {
			dp[i][0] = dp[i-1][1]+can[i].second+can[i-1].second-dx1;
			if(i>1) {
				long long dx2 = can[i].first-can[i-2].first;
				if(dx2<=k) dp[i][0] = max(dp[i][0],dp[i-2][1]+can[i].second+can[i-2].second-dx2);
			}
		} else {
			dp[i][0] = -1LL;
		}
		dp[i][1] = max(dp[i-1][0],dp[i-1][1]);
	}
	/*for(int i=0;i<n;i++) {
		printf("%lld ",dp[i][0]);
	}
	printf("\n");
	for(int i=0;i<n;i++) {
		printf("%lld ",dp[i][1]);
	}
	printf("\n");*/
	printf("%lld",max(dp[n-1][0],dp[n-1][1]));

	return 0;
}