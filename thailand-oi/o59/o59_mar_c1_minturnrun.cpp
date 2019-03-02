#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int n, m, s;
int A[N], dp[N][5];
int dr[3] = { -1, 0, 1 };
int dc[3] = { 0, 1, 0};

int f(int r, int c) { return m*(r-1) + c; }

struct node {
	int r, c;
	int cnt, h;
	node(int r, int c, int cnt, int h) : r(r), c(c), cnt(cnt), h(h) {}
};

int main() {
	fill_n(dp[0], N*5, (int)1e9);
	scanf("%d %d %d", &n, &m, &s);
	for(int i = 1; i <= n; i++) {
		string S;
		cin >> S;
		for(int j = 1; j <= m; j++) if(S[j-1] == '#') A[f(i, j)] = 1;
	}
	queue<node> Q;
	Q.emplace(s, 1, 0, 1);
	dp[f(s, 1)][1] = 0;
	while(!Q.empty()) {
		node now = Q.front();
		Q.pop();
		if(dp[f(now.r, now.c)][now.h] != now.cnt) continue;
		int r = now.r, c = now.c, h = now.h;
		for(int i = 0; i < 3; i++) {
			if(r+dr[i] > n || r+dr[i] < 1 || c+dc[i] > m || c+dc[i] < 1 || A[f(r+dr[i], c+dc[i])]) continue;
			if(dp[f(r+dr[i], c+dc[i])][i] > dp[f(r, c)][h] + (h != i)) {
				dp[f(r+dr[i], c+dc[i])][i] = dp[f(r, c)][h] + (h != i);
				Q.emplace(r+dr[i], c+dc[i], dp[f(r+dr[i], c+dc[i])][i], i);
			}
		}
	}
	int ans = INT_MAX;
	for(int i = 1; i <= n; i++) for(int j = 0; j < 3; j++) ans = min(ans, dp[f(i, m)][j]);

	printf("%d\n", ans);

	return 0;
}
