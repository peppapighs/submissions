#include <bits/stdc++.h>

using namespace std;

struct tp {
	int val, prior, lz, size;
	tp *l, *r;
	tp(int val) : val(val), prior(rand()), lz(0), size(1), l(NULL), r(NULL) {}
};

typedef tp* tpp;

int sz(tpp t) { return t ? t->size : 0; }
int updt(tpp t) { if(t) t->size = sz(t->l) + 1 + sz(t->r); }

void push(tpp t) {
	if(!t || !t->lz) return;
	t->val += t->lz;
	if(t->l) t->l->lz += t->lz;
	if(t->r) t->r->lz += t->lz;
	t->lz = 0;
}

void split(tpp t, tpp &l, tpp &r, int key) {
	if(!t) return void(l = r = NULL);
	push(t);
	if(t->val <= key) split(t->r, t->r, r, key), l = t;
	else split(t->l, l, t->l, key), r = t;
	updt(t);
}

void merge(tpp &t, tpp l, tpp r) {
	push(l), push(r);
	if(!l || !r) t = l ? l : r;
	else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;
	updt(t);
}

bool find(tpp t, int key) {
	push(t);
	if(!t) return false;
	else if(t->val == key) return true;
	else if(t->val > key) return find(t->l, key);
	else return find(t->r, key);
}

int n, q;
tpp t;

int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1, val; i <= n; i++) scanf("%d", &val), merge(t, t, new tp(val));
	while(q--) {
		int T;
		int a, b, c;
		scanf("%d%d", &T, &a);
		if(T == 1) printf("%d\n", find(t, a));
		if(T == 2) {
			scanf("%d%d", &b, &c);
			if(!find(t, a)) continue;
			tpp R;
			split(t, t, R, a - 1);
			if(t) t->lz += b;
			if(R) R->lz += c;
			merge(t, R, t);
		}
	}

	return 0;
}