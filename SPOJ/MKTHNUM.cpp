#include <bits/stdc++.h>

using namespace std;

struct node {
	int d;
	node *l, *r;
	node() { }
	node(int d, node *l, node *r) : d(d), l(l), r(r) { }
};

node* newleaf(int d) {
	return new node(d, nullptr, nullptr);
}

node* newpar(node* l, node* r) {
	return new node(l->d + r->d, l, r);
}

const int N = 1e5+5;

int n, m, A[N];
node* ver[N];
vector<int> coord;

int get(int x) { return lower_bound(coord.begin(), coord.end(), x) - coord.begin() + 1; }

node* build(int l = 1, int r = coord.size()) {
	if(l == r) return newleaf(0);
	int mid = (l + r) >> 1;
	return newpar(build(l, mid), build(mid+1, r));
}

node* update(int x, node* p, int l = 1, int r = coord.size()) {
	if(l == r) return newleaf(p->d + 1);
	int mid = (l + r) >> 1;
	if(x <= mid) return newpar(update(x, p->l, l, mid), p->r);
	else return newpar(p->l, update(x, p->r, mid+1, r));
}

int query(int k, node* p1, node* p2, int l = 1, int r = coord.size(), int add = 0) {
	if(l == r) return l;
	int mid = (l + r) >> 1;
	int cur_pos = add + p1->l->d - p2->l->d;
	if(cur_pos >= k) return query(k, p1->l, p2->l, l, mid, add);
	else return query(k, p1->r, p2->r, mid+1, r, cur_pos);
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d", A+i);
		coord.emplace_back(A[i]);
	}
	sort(coord.begin(), coord.end());
	coord.resize(unique(coord.begin(), coord.end()) - coord.begin());
	ver[0] = build();
	for(int i = 1; i <= n; i++) ver[i] = update(get(A[i]), ver[i-1]);
	for(int i = 1, a, b, c; i <= m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		int ret = query(c, ver[b], ver[a-1]);
		printf("%d\n", coord[ret-1]);
	}	

	return 0;
}