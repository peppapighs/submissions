#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, ans;
int dep[N], par[N][18], cpar[N], sub[N], dp[N];
vector<int> g[N];
bitset<N> chk;
int cent, mxnode;

void dfs(int u, int p) {
	par[u][0] = p;
	for(int i = 1; i <= 17; i++) par[u][i] = par[par[u][i - 1]][i - 1];
	dep[u] = dep[p] + 1;
	for(int v : g[u]) if(v != p) dfs(v, u);
}

int lca(int a, int b) {
	if(dep[a] < dep[b]) swap(a, b);
	for(int i = 17; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
	if(a == b) return a;
	for(int i = 17; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
	return par[a][0];
}

int dist(int a, int b) {
	return dep[a] + dep[b] - 2 * dep[lca(a, b)];
}

int calsz(int u, int p) {
	sub[u] = 1;
	for(int v : g[u]) if(v != p && !chk[v]) sub[u] += calsz(v, u);
	return sub[u];
}

void centroid(int u, int p, int all) {
	int mxsub = all - sub[u];
	for(int v : g[u]) if(v != p && !chk[v]) {
		centroid(v, u, all);
		mxsub = max(mxsub, sub[v]);
	}
	if(mxsub < mxnode) cent = u, mxnode = mxsub;
}

void build(int u, int p) {
	calsz(u, u);
	mxnode = sub[u] + 1;
	centroid(u, u, sub[u]);
	u = cent;
	cpar[u] = p;
	chk[u] = true;
	for(int v : g[u]) if(v != p && !chk[v]) build(v, u);
}

void paint(int u, int p) {
	if(!u) return;
	dp[u] = min(dp[u], dist(p, u));
	paint(cpar[u], p);
}

void query(int u, int p) {
	if(!u) return;
	ans = min(ans, dp[u] + dist(p, u));
	query(cpar[u], p);
}

int main() {
	fill(dp, dp + N, N);
	scanf("%d%d", &n, &m);
	for(int i = 1, a, b; i < n; i++) {
		scanf("%d%d", &a, &b);
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	dfs(1, 0);
	build(1, 0);
	paint(1, 1);
	while(m--) {
		int a, b;
		scanf("%d%d", &a, &b);
		if(a == 1) paint(b, b);
		else if(a == 2) {
			ans = INT_MAX;
			query(b, b);
			printf("%d\n", ans);
		}
	}

	return 0;
}