#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

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

void trash(tpp &t) {
	if(!t) return;
	push(t);
	trash(t->l);
	trash(t->r);
	free(t);
}

void hsh(tpp t, pii &h) {
	if(!t) return;
	push(t);
	hsh(t->l, h);
	h = add(mul(h, pii(101, 103)), pii(t->val, t->val));
	hsh(t->r, h);
}

void print(tpp t) {
	if(!t) return;
	push(t);
	print(t->l);
	printf("%c", t->val);
	print(t->r);
}

tpp t;

int q;
string s;

int main() {
	cin >> s;
	for(int i = 0; i < s.length(); i++) merge(t, t, new tp(s[i]));
	scanf("%d", &q);
	while(q--) {
		int T;
		scanf("%d", &T);
		if(T == 1) { //Insert string at x
			tpp R;
			int x;
			string tmp;
			cin >> x >> tmp;
			split(t, t, R, x - 1);
			for(int i = 0; i < tmp.length(); i++) merge(t, t, new tp(tmp[i]));
			merge(t, t, R);
			print(t);
		} else if(T == 2) { //Delete string from x to y (index start at 1)
			int x, y;
			tpp M, R;
			scanf("%d%d", &x, &y);
			split(t, t, M, x - 2);
			split(M, M, R, y - x);
			trash(M);
			merge(t, t, R);
		} else if(T == 3) { //Reverse string from x to y (index start at 1)
			int x, y;
			tpp M, R;
			scanf("%d%d", &x, &y);
			split(t, t, M, x - 2);
			split(M, M, R, y - x);
			M->lz ^= true; //Lazy propagation
			merge(t, t, M);
			merge(t, t, R);
		} else if(T == 4) { //Check if string from x to y is palindrome
			int x, y;
			pii F, S; //Double hash for comparing string in O(1)
			tpp M, R;
			scanf("%d%d", &x, &y);
			split(t, t, M, x - 2);
			split(M, M, R, y - x);
			hsh(M, F);
			M->lz ^= true;
			hsh(M, S);
			M->lz ^= true;
			if(F == S) printf("PALINDROME\n"); //Reversed palindromic string always equals to itself
			else printf("NOT PALINDROME\n");
			merge(t, t, M);
			merge(t, t, R);
		}
	}

	print(t);

	return 0;
}