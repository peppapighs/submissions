#include <bits/stdc++.h>

using namespace std;

const int M = 29947;

int a, b, c;
int dp[705][705];

int main() {
	scanf("%d %d %d", &a, &b, &c);
	for(int i = 0; i <= 700; i++) for(int j = 0; j <= 700; j++) {
		if(i == 0 || j == 0) dp[i][j] = 1;
		else dp[i][j] = (dp[i-1][j] + dp[i][j-1] + M) % M;	
	}
	int ans = 0;
	for(int i = 1; i < a; i++) for(int j = 1; j < b; j++) {
		int ret = (dp[i-1][j-1] * dp[a-i-1+b-j-1][c-1]) % M;
		ans = (ans + ret) % M;
	}
	ans = (ans + dp[a+b-2][c-1]) % M;
	printf("%d\n", ans);

	return 0;
}
