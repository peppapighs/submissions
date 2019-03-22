#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int M = 135211;

int w, h, lim;
int dp[N][1<<10];
bool diag[10][N][2];

int get(int a, int b) {
	int ret = b >> (a << 1) & 1;
	if(b >> (a << 1 | 1) & 1) ret += 2;
	return ret;
}

bool chk(int b) {
	int prev = -1;
	for(int i = 0; i < h; i++) {
		if(get(i, b) == prev) return false;
		prev = get(i, b);
	}
	return true;
}

int main() {
	scanf("%d %d", &w, &h);
	for(int i = 1; i <= h; i++) {
		char S[N];
		scanf(" %s", S+1);
		for(int j = 1; j <= w; j++) {
			if(S[j] == '/') diag[i][j][0] = true;
			if(S[j] == '\\') diag[i][j][1] = true;
		}
	}
	++w, ++h;
	lim = 1 << (h << 1);
	for(int i = 0; i < lim; i++) if(chk(i)) dp[1][i] = 1;
	for(int i = 2; i <= w; i++) for(int j = 0; j < lim; j++) if(chk(j)) {
		for(int k = 0; k < lim; k++) if(chk(k)) {
			bool valid = true;
			for(int l = 0; l < h; l++) {
				if(get(l, j) == get(l, k)) valid = false;
				if(l != h-1 && diag[l+1][i-1][0] && get(l, j) == get(l+1, k)) valid = false;
				if(l && diag[l][i-1][1] && get(l, j) == get(l-1, k)) valid = false;
			}
			if(valid) dp[i][j] = (dp[i][j] + dp[i-1][k]) % M;
		}
	}
	int ans = 0;
	for(int i = 0; i < lim; i++) ans = (ans + dp[w][i]) % M;
	printf("%d\n", ans);

	return 0;
}