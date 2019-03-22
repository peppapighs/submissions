#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int q;
int dp[N];

int main() {
	scanf("%d",&q);
	while(q--) {
		int a,b;
		scanf("%d%d",&a,&b);
		dp[a]++;
		dp[b]--;
	}
	int mx=0;
	for(int i=1;i<N;i++) {
		dp[i]+=dp[i-1];
		mx=max(mx,dp[i]);
	}

	printf("%d",mx);

	return 0;
}