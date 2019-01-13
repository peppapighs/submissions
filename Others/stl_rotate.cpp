#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct tp {
	int val, prior, size;
	tp *l, *r;
	tp(int val) : val(val), prior(rand()), size(1), l(NULL), r(NULL) {}
};

typedef tp* tpp;

int n, q;

int sz(tpp t) { return t ? t->size : 0; }
int updt(tpp t) { if(t) t->size = sz(t->l) + sz(t->r) + 1; }

void split(tpp t, tpp &l, tpp &r, int pos, int add = 0) {
	if(!t) return void(l = r = NULL);
	int cur_pos = add + sz(t->l);
	if(cur_pos < pos) split(t->r, t->r, r, pos, cur_pos + 1), l = t;
	else split(t->l, l, t->l, pos, add), r = t;
	updt(t);
}

void merge(tpp &t, tpp l, tpp r) {
	if(!l || !r) t = l ? l : r;
	else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;
	updt(t);
}

void print(tpp t) {
	if(!t) return;
	print(t->l);
	printf("%d ", t->val);
	print(t->r);
}

tpp t;

int main() {
	scanf("%d", &n);
	for(int i = 1, val; i <= n; i++) scanf("%d", &val), merge(t, t, new tp(val));
	scanf("%d", &q);
	while(q--) {
		int l, m, r;
		scanf("%d%d%d", &l, &m, &r);
		tpp a, b, c, d;
		split(t, a, b, l);
		split(b, b, c, r - l);
		split(b, b, d, m - l);
		merge(b, d, b);
		merge(b, b, c);
		merge(t, a, b);
	}

	print(t);

	return 0;
}