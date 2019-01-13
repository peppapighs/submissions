#include <bits/stdc++.h>

using namespace std;

int INF = 1e9+5;

int main() {
	int n;
	scanf("%d",&n);
	int s[n],c[n];
	for(int i=0;i<n;i++) {
		scanf("%d",&s[i]);
	}
	for(int i=0;i<n;i++) {
		scanf("%d",&c[i]);
	}

	int dp1[n],dp2[n];

	for(int i=0;i<n;i++) {
		dp1[i] = INF;
		dp2[i] = INF;
	}

	for(int i=1;i<n;i++) {
		for(int j=0;j<i;j++) {
			if(s[j]<s[i]) {
				dp1[i] = min(dp1[i],c[i]+c[j]);
			}
		}
	}

	for(int i=2;i<n;i++) {
		for(int j=1;j<i;j++) {
			if(s[j]<s[i]) {
				dp2[i] = min(dp2[i],c[i]+dp1[j]);
			}
		}
	}

	int ans = INF;

	for(int i=0;i<n;i++) {
		ans=min(ans,dp2[i]);
	}

	if(ans==INF) {
		printf("-1");
	} else {
		printf("%d",ans);
	}

	return 0;
}