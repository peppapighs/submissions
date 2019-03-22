#include <bits/stdc++.h>

using namespace std;

struct tp {
	int val, prior, size;
	bool lz;
	tp *l, *r;
	tp(int val) : val(val), lz(false), prior(rand()), size(1), l(NULL), r(NULL) {}
};

typedef tp* tpp;

int sz(tpp t) { return t ? t->size : 0; }
void updt(tpp t) { if(t) t->size = sz(t->l) + 1 + sz(t->r); }

void push(tpp t) {
	if(!t || !t->lz) return;
	swap(t->l, t->r);
	if(t->l) t->l->lz ^= true;
	if(t->r) t->r->lz ^= true;
	t->lz = false;
}

void split(tpp t, tpp &l, tpp &r, int pos, int add = 0) {
	if(!t) return void(l = r = NULL);
	push(t);
	int cur_pos = add + sz(t->l);
	if(cur_pos <= pos) split(t->r, t->r, r, pos, cur_pos + 1), l = t;
	else split(t->l, l, t->l, pos, add), r = t;
	updt(t);
}

void merge(tpp &t, tpp l, tpp r) {
	push(l), push(r);
	if(!l || !r) t = l ? l : r;
	else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;
	updt(t);
}

int left(tpp t) {
	push(t);
	if(!t->l) return t->val;
	else return left(t->l);
}

void reverse(tpp &t, int k) {
	tpp R;
	split(t, t, R, k - 1);
	if(t) t->lz ^= true;
	merge(t, t, R);
}

int n;
tpp t;

int main() {
	scanf("%d", &n);
	for(int i = 1, val; i <= n; i++) scanf("%d", &val), merge(t, t, new tp(val));
	int l = left(t), cnt = 0;
	while(l != 1) reverse(t, l), cnt++, l = left(t);

	printf("%d", cnt);

	return 0;
}