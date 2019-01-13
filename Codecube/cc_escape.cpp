#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

int m[N][N],dp[N][N];
int n,m;

int main() {
	scanf("%d%d",&n,&m);
	for(int j=0;j<n;j++) {
		for(int i=0;i<m;i++) {
			scanf("%d",&m[i][j]);
		}
	}

	return 0;
}