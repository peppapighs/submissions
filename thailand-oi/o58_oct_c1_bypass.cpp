#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5+5;

int n;
vector<int> g[N];
vector<pii> E;
int par[N], sub[N];
pii mx1[N], mx2[N];

int subsize(int u, int p) {
	par[u] = p;
	sub[u] = 1;
	for(int v : g[u]) if(v != p) {
		sub[u] += subsize(v, u);
		pii ret(sub[v], v);
		if(ret > mx1[u]) swap(ret, mx1[u]);
		if(ret > mx2[u]) swap(ret, mx2[u]);
	}
	pii ret(n-sub[u], p);
	if(ret > mx1[u]) swap(ret, mx1[u]);
	if(ret > mx2[u]) swap(ret, mx2[u]);
	return sub[u];
}

int main() {
	scanf("%d", &n);
	for(int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		g[a].emplace_back(b);
		g[b].emplace_back(a);
		E.emplace_back(a, b);
	}
	subsize(1, 0);
	long long ans = 0;
	for(pii e : E) {
		int a = e.x, b = e.y;
		long long u = (long long)mx1[a].y == b ? mx2[a].x : mx1[a].x;
		long long v = (long long)mx1[b].y == a ? mx2[b].x : mx1[b].x;
		if(!u || !v) continue;
		ans = max(ans, u*v);	
	}
	printf("%lld\n", ans);

	return 0;
}