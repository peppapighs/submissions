#include <bits/stdc++.h>

using namespace std;

int road[2005];
int umb[2005];
int w[2005];
int dp[2005][2005];

int main() {
	int a,n,m;
	scanf("%d%d%d",&a,&n,&m);
	for(int i=0;i<n;i++) {
		int l,r;
		scanf("%d%d",&l,&r);
		road[l]++;
		road[r+1]--;
	}
	for(int i=1;i<=a;i++) {
		road[i]+=road[i-1];
	}

	for(int i=1;i<=m;i++) {
		int x;
		scanf("%d%d",&x,&w[i]);
		umb[x]=i;
	}

	for(int i=0;i<=a;i++) {
		printf("%d ",road[i]);
		for(int j=0;j<=m;j++) {
			dp[i][j] = 1e9;
		}
	}
	printf("\n\n");
	if(!road[0]) {
		dp[0][0] = 0;
	}
	if(umb[0]) {
		dp[0][umb[0]] = 0;
	}

	for(int i=0;i<a;i++) {
		for(int j=0;j<=m;j++) {
			if(j==0) {
				if(umb[i]) {
					dp[i+1][umb[i]] = min(dp[i+1][umb[i]],dp[i][j]+w[umb[i]]);
				}
				if(road[i+1]) {
					dp[i+1][j] = 1e9;
				} else {
					dp[i+1][j] = 0;
				}
			} else {
				if(!road[i+1]) {
					dp[i+1][0] = min(dp[i+1][0],dp[i][j]+w[j]);
				}
				if(umb[i]) {
					dp[i+1][umb[i]] = min(dp[i+1][umb[i]],dp[i][j]+w[umb[i]]);
				}
				dp[i+1][j] = min(dp[i+1][j],dp[i][j]+w[j]);
			}
		}
	}

	for(int j=0;j<=m;j++) {
		for(int i=0;i<=a;i++) {
			if(dp[i][j]!=1e9)
				printf("%d ",dp[i][j]);
			else
				printf("I ");
		}
		printf("\n");
	}

	return 0;
}