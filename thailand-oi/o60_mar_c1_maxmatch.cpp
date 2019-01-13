#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e4+5;

struct edge {
	int u, v, w;
	edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

int n, k, ans;
vector<pii> g[N];
vector<edge> E;
int dp[N][2], chk[N];

void dfs(int u, int p) {
	for(pii vw : g[u]) {
		int v = vw.x, w = vw.y;
		if(v == p) continue;
		dfs(v, u);
		dp[u][0] = max(dp[u][0], dp[v][0]);
		if(!chk[v]) {
			dp[u][0] = max(dp[u][0], dp[v][1]);
			if(!chk[u]) dp[u][1] = max(dp[u][1], dp[v][0] + w);
		}
	}
}

int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1; i < n; i++) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		g[a].emplace_back(b, w), g[b].emplace_back(a, w);
	}
	for(int i = 1; i <= k; i++) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		E.emplace_back(a, b, w);
	}
	for(int bit = 0; bit < (1<<k); bit++) {
		int ret = 0;
		bool valid = true;
		memset(chk, 0, sizeof chk);
		for(int i = 0; i < k; i++) if((bit>>i) & 1) {
			if(chk[E[i].u] || chk[E[i].v]) {
				valid = false;
				break;
			}
			ret += E[i].w, chk[E[i].u] = chk[E[i].v] = 1;
		}
		if(!valid) continue;
		memset(dp, 0, sizeof dp);
		dfs(1, 0);
		ret += max(dp[1][0], dp[1][1]);
		ans = max(ans, ret);
	}
	printf("%d\n", ans);

	return 0;
}
