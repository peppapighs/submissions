#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n, q;
int sz[N], cpar[N], cdep[N], d[N][18];
vector<int> g[N];
bitset<N> chk;

int getsz(int u, int p) { sz[u] = 1; for(int v : g[u]) if(v != p && !chk[v]) sz[u] += getsz(v, u); return sz[u]; }

int find_cen(int u, int p, int all, pii &ret) {
	int mx = all - sz[u];
	for(int v : g[u]) if(v != p && !chk[v])
		mx = max(mx, find_cen(v, u, all, ret));
	ret = min(ret, pii(mx, u));
	return sz[u];
}

void dfs(int u, int p, int dep) {
	for(int v : g[u]) if(v != p && !chk[v]) {
		d[v][dep] = d[u][dep] + 1;
		dfs(v, u, dep);
	}
}

void build_centroid(int u, int p, pii ret = pii(1e9, -1)) {
	getsz(u, u), find_cen(u, u, sz[u], ret);
	cpar[u = ret.y] = p, cdep[u] = cdep[p] + 1, chk[u] = true;
	dfs(u, u, cdep[u]);
	for(int v : g[u]) if(!chk[v]) build_centroid(v, u);
}

int dist[N];

void update(int u) {
	dist[u] = 0;
	for(int i = cpar[u]; i; i = cpar[i])
		dist[i] = min(dist[i], d[u][cdep[i]]);
}

int query(int u) {
	int ret = dist[u];
	for(int i = cpar[u]; i; i = cpar[i])
		ret = min(ret, dist[i] + d[u][cdep[i]]);
	return ret;
}

int main() {
	fill_n(dist, N, 1e9);

	scanf("%d %d", &n, &q);
	for(int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		g[a].emplace_back(b), g[b].emplace_back(a);
	}
	build_centroid(1, 0);
	update(1);
	for(int i = 1, T, a; i <= q; i++) {
		scanf("%d %d", &T, &a);
		if(T == 1) update(a);
		else printf("%d\n", query(a));
	}

	return 0;
}