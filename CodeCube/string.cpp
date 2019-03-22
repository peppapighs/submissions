#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct tp {
	char val;
	bool lz;
	int prior, size;
	tp *l, *r;
	tp(char val) : val(val), lz(false), prior(rand()), size(1), l(NULL), r(NULL) {}
};

typedef tp* tpp;

int sz(tpp t) { return t ? t->size : 0; }
int updt(tpp t) { if(t) t->size = sz(t->l) + 1 + sz(t->r); }

void push(tpp it) {
	if (it && it->lz) {
        it->lz = false;
        swap (it->l, it->r);
        if (it->l)  it->l->lz ^= true;
        if (it->r)  it->r->lz ^= true;
    }
}

void print(tpp t) {
	if(!t) return;
	push(t);
	print(t->l);
	printf("%c", t->val);
	print(t->r);
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

void reverse(tpp &t, int l, int r) {
	tpp t1, t2, t3;
    split(t, t1, t2, l - 2);
    split(t2, t2, t3, r - l);
    t2->lz ^= true;
    merge(t, t1, t2);
    merge(t, t, t3);
}

int q;
tpp t;

int main() {
	string str;
	cin >> str;
	for(int i = 0; i < str.length(); i++) merge(t, t, new tp(str[i]));
	scanf("%d", &q);
	while(q--) {
		char T;
		cin >> T;
		if(T == 'R') {
			int i, j;
			cin >> i >> j;
			reverse(t, i, j);
		} else if(T == 'I') {
			int x;
			string K;
			cin >> x >> K;
			tpp r;
			split(t, t, r, x - 1);
			for(int i = 0; i < K.length(); i++) merge(t, t, new tp(K[i]));
			merge(t, t, r);
		}
	}

	print(t);

	return 0;
}