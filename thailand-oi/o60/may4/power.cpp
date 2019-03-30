#include <bits/stdc++.h>

#define iii tuple<int, int, int>
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;
const int M = 33331;

int modpow(int a, int b) {
	int ret = 1;
	for( ; b; b >>= 1) {
		if(b & 1) ret = (ret * a) % M;
		a = (a * a) % M;
	}
	return ret;
}

int n, m, q;
int dsu[N], par[N][18], d[N], dep[N];
vector<iii> E;
vector<pii> g[N];

int find(int x) { return dsu[x] = x == dsu[x] ? x : find(dsu[x]); }

void dfs(int u, int p) {
	dep[u] = dep[p] + 1, par[u][0] = p;
	for(int i = 1; i <= 17; i++) par[u][i] = par[par[u][i-1]][i-1];
	for(pii v : g[u]) if(v.x != p) {
		d[v.x] = (d[u] + v.y) % M;
		dfs(v.x, u);
	}
}

int lca(int a, int b) {
	if(dep[a] < dep[b]) swap(a, b);
	for(int i = 17; ~i; i--) if(dep[par[a][i]] >= dep[b]) a = par[a][i];
	if(a == b) return a;
	for(int i = 17; ~i; i--) if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
	return par[a][0];
}

int main() {
	iota(dsu, dsu+N, 0);
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1, a, b, c; i <= m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		E.emplace_back(c, a, b);
	}
	sort(E.begin(), E.end());
	for(iii e : E) {
		int a, b, c;
		tie(c, a, b) = e;
		if(find(a) != find(b)) {
			dsu[find(a)] = find(b);
			g[a].emplace_back(b, modpow(2, c));
			g[b].emplace_back(a, modpow(2, c));
		}
	}
	dfs(1, 1);
	for(int i = 1, a, b; i <= q; i++) {
		scanf("%d %d", &a, &b);
		int now = (d[a] + d[b]) % M;
		now = (now - (2 * d[lca(a, b)]) % M + M) % M;
		printf("%d\n", now);
	}

	return 0;
}