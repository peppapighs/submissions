#include <bits/stdc++.h>

using namespace std;

const int N = 1<<18;

struct line {
	long long m, b;
	long long f(int x) { return m*x + b; }
	line() {}
	line(long long m, long long b) : m(m), b(b) {}
};

line t[N<<1];
int chk[N<<1], book = 1;

void update(line x, int p = 1, int l = (int)-1e5, int r = (int)1e5) {
	if(chk[p] < book) {
		t[p] = x, chk[p] = book;
		return;
	}
	int m = (l+r) >> 1;
	bool left = x.f(l) < t[p].f(l);
	bool mid = x.f(m) < t[p].f(m);
	if(mid) swap(x, t[p]);
	if(l == r) return;
	if(left ^ mid) update(x, p<<1, l, m);
	else update(x, p<<1|1, m+1, r);
}

long long query(int x, int p = 1, int l = (int)-1e5, int r = (int)1e5) {
	if(chk[p] < book) return LLONG_MAX;
	if(l == r) return t[p].f(x);
	int m = (l+r) >> 1;
	if(x < m) return min(t[p].f(x), query(x, p<<1, l, m));
	else return min(t[p].f(x), query(x, p<<1|1, m+1, r));
}

int n;
int A[N], B[N];
int sz[N];
vector<int> g[N];
long long ans[N];

int calc(int u, int p) {
	sz[u] = 1;
	for(int v : g[u]) if(v != p) sz[u] += calc(v, u);
	return sz[u];
}

void add(int u, int p) {
	update(line(B[u], ans[u]));
	for(int v : g[u]) if(v != p) add(v, u);
}

void dfs(int u, int p, int keep) {
	int hv = -1;
	for(int v : g[u]) if(v != p && (hv == -1 || sz[v] > sz[hv])) hv = v;
	for(int v : g[u]) if(v != p && v != hv) dfs(v, u, 0);
	if(hv != -1) dfs(hv, u, 1);
	for(int v : g[u]) if(v != p && v != hv) add(v, u);
	if(hv != -1) ans[u] = query(A[u]);
	update(line(B[u], ans[u]));
	if(!keep) book++;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", A+i);
	for(int i = 1; i <= n; i++) scanf("%d", B+i);
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].emplace_back(b), g[b].emplace_back(a);
	}
	calc(1, 0);
	dfs(1, 0, 1);
	for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
	printf("\n");

	return 0;
}
