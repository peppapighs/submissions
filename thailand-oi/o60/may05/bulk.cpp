#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1<<17;

int n, q;
int A[N], deg[N];
bitset<N> inc;
vector<pii> E;
vector<int> g[N];

struct node {
	queue<pii> Q;
	int sum, cnt;
	pii mx;
	node() {}
	node(int idx) {
		if(inc[idx]) mx = pii(A[idx], 1), cnt = 1;
		else mx = pii(0, 0), cnt = 0;
		sum = A[idx];
	}
	friend node operator+(const node &a, const node &b) {
		node ret;
		ret.sum = a.sum + b.sum;
		ret.cnt = a.cnt + b.cnt;
		if(!a.mx.y) ret.mx = b.mx;
		else if(!b.mx.y) ret.mx = a.mx;
		else {
			if(a.mx.x == b.mx.x) ret.mx = pii(a.mx.x, a.mx.y + b.mx.y);
			else ret.mx = max(a.mx, b.mx);
		}
		return ret;
	}
} t[N<<1];

void build(int p = 1, int l = 1, int r = n) {
	if(l == r) return void(t[p] = node(l));
	int m = (l + r) >> 1;
	build(p<<1, l, m), build(p<<1|1, m+1, r);
	t[p] = t[p<<1] + t[p<<1|1];
}

void push(int p, int l, int r) {
	while(!t[p].Q.empty()) {
		pii lz = t[p].Q.front();
		t[p].Q.pop();
		if(lz.x == 1) {
			t[p].sum += lz.y*(r-l+1);
			t[p].mx = pii(t[p].mx.x+lz.y, t[p].mx.y);
		} else if(lz.x == 2) {
			t[p].sum = lz.y*(r-l+1);
			t[p].mx = pii(lz.y, t[p].cnt);
		}
		if(l != r) {
			t[p<<1].Q.emplace(lz);
			t[p<<1|1].Q.emplace(lz);
		}
	}
}

void update(int k, int x, int y, int c, int p = 1, int l = 1, int r = n) {
	push(p, l, r);
	if(x > r || l > y) return;
	if(x <= l && r <= y) {
		t[p].Q.emplace(k, c);
		push(p, l, r);
		return;
	}
	int m = (l + r) >> 1;
	update(k, x, y, c, p<<1, l, m), update(k, x, y, c, p<<1|1, m+1, r);
	t[p] = t[p<<1] + t[p<<1|1];
}

int main() {
	E.emplace_back(0, 0);
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		E.emplace_back(a, b);
		g[a].emplace_back(b), g[b].emplace_back(a);
		A[i] = w;
		deg[a]++, deg[b]++;
	}
	queue<int> Q;
	for(int i = 1; i <= n; i++) if(deg[i] == 1) Q.emplace(i);
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for(int v : g[u]) if(--deg[v] == 1) Q.emplace(v);
	}
	for(int i = 1; i <= n; i++) inc[i] = (deg[E[i].x] != 1 && deg[E[i].y] != 1);
	build();
	while(q--) {
		int k, a, b, c;
		scanf("%d %d %d %d", &k, &a, &b, &c);
		if(k == 1) update(1, a, b, c);
		else update(2, a, b, c);
		printf("%d %d\n", t[1].sum - t[1].mx.x, t[1].mx.y);
	}

	return 0;
}
