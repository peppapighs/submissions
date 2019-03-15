#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e4+5;

int n, k, ans;
int dp[N][2];
bool chk[N];
vector<pii> g[N];
vector<iii> E;

void dfs(int u, int p) {
	for(pii v : g[u]) if(v.x != p) dfs(v.x, u), dp[u][0] += dp[v.x][1];
	dp[u][1] = dp[u][0];
	for(pii v : g[u]) if(v.x != p) {
		if(chk[v.x] || chk[u]) continue;
		dp[u][1] = max(dp[u][1], dp[u][0] - dp[v.x][1] + v.y + dp[v.x][0]);
	}
	dp[u][1] = max(dp[u][0], dp[u][1]);
}

int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1, a, b, c; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		g[a].emplace_back(b, c), g[b].emplace_back(a, c);
	}
	for(int i = 1, a, b, c; i <= k; i++) {
		scanf("%d %d %d", &a, &b, &c);
		E.emplace_back(a, b, c);
	}
	for(int bit = 0; bit < (1 << k); bit++) {
		int ret = 0;
		memset(chk, 0, sizeof chk), memset(dp, 0, sizeof dp);
		bool valid = true;
		for(int i = 0; i < k; i++) if(bit >> i & 1) {
			int a, b, c;
			tie(a, b, c) = E[i];
			if(chk[a] || chk[b]) valid = false;
			chk[a] = chk[b] = true;
			ret += c;
		}
		if(!valid) continue;
		dfs(1, 1);
		ans = max(ans, ret + dp[1][1]);
	}
	printf("%d\n", ans);

	return 0;
}