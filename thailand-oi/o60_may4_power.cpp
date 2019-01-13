#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int M = 33331;

int n, m, q;
int dsu[N], par[N][18], dep[N];
vector<vector<pii> > g(N);

struct edge {
	int u, v, w;
	edge(int u, int v, int w) : u(u), v(v), w(w) {}
	friend bool operator<(const edge &a, const edge &b) {
		return a.w < b.w;
	}
};

int find(int u) { return dsu[u] = dsu[u] == u ? u : find(dsu[u]); }

int pow2(int x) {
	if(x == 0) return 1;
	if(x == 1) return 2;
	int y = pow2(x >> 1) % M;
	int ret = (y * y) % M;
	if(x & 1) ret = (ret * 2) % M;
	return ret;
}

void dfs(int u, int p) {
	par[u][0] = p;
	for(int i = 1; i < 18; i++) par[u][i] = par[par[u][i - 1]][i - 1];
	for(pii vw : g[u]) {
		int v = vw.x, w = vw.y;
		if(v == p) continue;
		dep[v] = (dep[u] + w) % M;
		dfs(v, u);
	}
}

int lca(int a, int b) {
	if(dep[a] < dep[b]) swap(a, b);
	for(int i = 17; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
	if(a == b) return a;
	for(int i = 17; ~i; i--) if(par[a][i] != par[b][i]) {
		a = par[a][i];
		b = par[b][i];
	}
	return par[a][0];
}

vector<edge> E;

int main() {
	scanf("%d%d%d", &n, &m , &q);
	for(int i = 1; i <= n; i++) dsu[i] = i;
	while(m--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		E.emplace_back(u, v, w);
	}
	sort(E.begin(), E.end());
	int cnt = 0;
	for(edge p : E) {
		int u = find(p.u), v = find(p.v);
		if(u != v) {
			dsu[u] = v;
			g[p.u].emplace_back(p.v, pow2(p.w));
			g[p.v].emplace_back(p.u, pow2(p.w));
			cnt++;
		}
		if(cnt == n - 1) break;
	}

	dfs(1, 0);
	while(q--) {
		int a, b;
		scanf("%d%d", &a, &b);
		long long ret = dep[a] + dep[b] - 2 * dep[lca(a, b)];
		ret = ((ret % M) + M) % M;
		printf("%lld\n", ret);
	}

	return 0;
}