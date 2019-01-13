#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 100;
const int M1 = 1e9 + 7;
const int M2 = 1e9 + 9;

pii add(pii a, pii b) { return {(a.x + b.x) % M1, (a.y + b.y) % M2}; }
pii mul(pii a, pii b) { return {(a.x * b.x) % M1, (a.y * b.y) % M2}; }

pii power[N];

struct item {
	pii hsh;
	item *l, *r;
	item() {}
	item(pii hsh, item *l, item *r) : hsh(hsh), l(l), r(r) {}
};

int n, m, s, t;
vector<vector<pii> > g(N);

int par[N];
item *dist[N];

item *newleaf(pii a) {
	return new item(a, nullptr, nullptr);
}

item *newpar(item *l, item *r) {
	return new item(add(l->hsh, r->hsh), l, r);
}

item *build(bool inf, int l = 0, int r = N) {
	if(l == r) {
		if(inf) return newleaf(power[l]);
		else return newleaf(pii(0, 0));
	}
	int mid = (l + r) >> 1;
	return newpar(build(inf, l, mid), build(inf, mid + 1, r));
}

bool travel(int x, item *p, int l = 0, int r = N) {
	if(l == r) return (p->hsh != pii(0, 0));
	int mid = (l + r) >> 1;
	if(x <= mid) return travel(x, p->l, l, mid);
	else return travel(x, p->r, mid + 1, r);
}

item *update(int x, item *p, int l = 0, int r = N) {
	if(l == r) {
		if(p->hsh == pii(0, 0)) return newleaf(power[l]);
		else return newleaf(pii(0, 0));
	}
	int mid = (l + r) >> 1;
	if(x <= mid) return newpar(update(x, p->l, l, mid), p->r);
	else return newpar(p->l, update(x, p->r, mid + 1, r));
}

bool compare(item *p1, item *p2, int l = 0, int r = N) {
	if(l == r) {
		if(p1->hsh == p2->hsh) return false;
		else return p2->hsh != pii(0, 0);
	}
	int mid = (l + r) >> 1;
	if(p1->r->hsh == p2->r->hsh) return compare(p1->l, p2->l, l, mid);
	else return compare(p1->r, p2->r, mid + 1, r);
}

item *true_add(int x, item *p) {
	item *ret = update(x, p);
	while(!travel(x++, ret)) ret = update(x, ret);
	return ret;
}

struct node {
	item *d;
	int u;
	node(item *d, int u) : d(d), u(u) {}
	friend bool operator<(const node &a, const node &b) {
		return !compare(a.d, b.d);
	}
};

priority_queue<node> Q;

int main() {
	power[0] = pii(1, 1);
	for(int i = 1; i < N; i++) power[i] = mul(power[i - 1], pii(2, 2));
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	scanf("%d%d", &s, &t);
	item *INF = build(true);
	for(int i = 1; i <= n; i++) dist[i] = INF;

	dist[s] = build(false);
	Q.emplace(dist[s], s);

	while(!Q.empty()) {
		node now = Q.top();
		Q.pop();
		if(dist[now.u] != now.d) continue;
		for(pii v : g[now.u]) {
			item *sum = true_add(v.y, dist[now.u]);
			if(compare(sum, dist[v.x])) {
				dist[v.x] = sum;
				par[v.x] = now.u;
				Q.emplace(dist[v.x], v.x);
			}
		}
	}

	if(dist[t] == INF) return !printf("-1");
	vector<int> ans;
	ans.emplace_back(t);
	for(int i = par[t]; i; i = par[i]) ans.emplace_back(i);
	printf("%d\n", dist[t]->hsh.x);
	printf("%d\n", ans.size());
	for(int i = ans.size() - 1; ~i; i--) printf("%d ", ans[i]);

	return 0;
}