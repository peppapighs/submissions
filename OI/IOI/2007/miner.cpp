#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int dp[2][4][4][4][4];
int n, arr[N];
string str;

int cnt(int x, int y, int z) {
	int ret = 0;
	for(int i = 1; i <= 3; i++) if(x == i || y == i || z == i) ret++;
	return ret;
}

int main() {
	scanf("%d", &n);
	cin >> str;
	for(int i = 0; i < n; i++) {
		if(str[i] == 'M') arr[i] = 1;
		else if(str[i] == 'F') arr[i] = 2;
		else arr[i] = 3;
	}

	int now = 0;

	for(int k = n - 1; k >= 0; k--) {
		for(int a = 0; a < 4; a++) for(int b = 0; b < 4; b++) for(int c = 0; c < 4; c++) for(int d = 0; d < 4; d++) 
			dp[now][a][b][c][d] = max(dp[1 - now][arr[k]][a][c][d] + cnt(arr[k], a, b), dp[1 - now][a][b][arr[k]][c] + cnt(arr[k], c, d));
		now = 1 - now;
	}	

	printf("%d", dp[1 - now][0][0][0][0]);

	return 0;
}