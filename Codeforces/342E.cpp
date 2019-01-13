#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n, m;
int block = (int)sqrt(N);
int dist[N], par[N][18], dep[N];
vector<int> g[N];
bitset<N> red;
vector<int> redlist;

void bfs() {
	queue<pii> Q;
	for(int i = 1; i <= n; i++) if(red[i]) {
		red[i] = true;
		Q.emplace(i, dist[i] = 0);
	}
	while(!Q.empty()) {
		pii now = Q.front();
		Q.pop();
		for(int v : g[now.x]) if(dist[now.x] + 1 < dist[v]) Q.emplace(v, dist[v] = min(dist[v], dist[now.x] + 1));
	}
	redlist.clear();
}

void dfs(int u, int p) {
	dep[u] = dep[p] + 1;
	par[u][0] = p;
	for(int i = 1; i <= 17; i++) par[u][i] = par[par[u][i - 1]][i - 1];
	for(int v : g[u]) if(v != p) dfs(v, u);
}

int lca(int a, int b) {
	if(dep[a] < dep[b]) swap(a, b);
	for(int i = 17; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
	if(a == b) return a;
	for(int i = 17; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
	return par[a][0];
}

int d(int a, int b) { return dep[a] + dep[b] - 2*dep[lca(a, b)]; }

int main() {
	fill(begin(dist), end(dist), INT_MAX);
	scanf("%d%d", &n, &m);
	for(int i = 1, a, b; i < n; i++) {
		scanf("%d%d", &a, &b);
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	dfs(1, 0);
	redlist.emplace_back(1);
	red[1] = 1;
	for(int i = 1, a, b; i <= m; i++) {
		scanf("%d%d", &a, &b);
		if(a == 1) {
			redlist.emplace_back(b);
			red[b] = true;
		} else if(a == 2) {
			int ans = dist[b];
			for(int v : redlist) ans = min(ans, d(b, v));
			printf("%d\n", ans);
		}
		if(i % block == 0) bfs();
	}

	return 0;
}