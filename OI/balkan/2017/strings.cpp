#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5+5;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

pii hpow[N], iden(69, 1337);

struct item {
	char c;
	int prio, sz, lz;
	pii h, rh;
	item *l, *r;
	item(char c) : c(c), prio(rand()), sz(1), lz(0), h(c, c), rh(c, c), l(NULL), r(NULL) {}
};

typedef item* pitem;

int sz(pitem t) { return t ? t->sz : 0; }
void updt(pitem t) { 
	if(t) {
		t->sz = sz(t->l) + 1 + sz(t->r);
		t->h = t->rh = pii(t->c, t->c);
		if(t->r) t->h = add(mul(pii(t->c, t->c), hpow[sz(t->r)]), t->r->h);
		if(t->l) t->h = add(mul(t->l->h, hpow[sz(t->r)+1]), t->h);
		if(t->l) t->rh = add(mul(pii(t->c, t->c), hpow[sz(t->l)]), t->l->rh);
		if(t->r) t->rh = add(mul(t->r->rh, hpow[sz(t->l)+1]), t->rh);
	}
}

void push(pitem t) {
	if(!t || !t->lz) return;
	swap(t->l, t->r);
	if(t->l) t->l->lz ^= 1, swap(t->l->h, t->l->rh);
	if(t->r) t->r->lz ^= 1, swap(t->r->h, t->r->rh);
	t->lz = 0;
}

void split(pitem t, pitem &l, pitem &r, int pos, int add = 0) {
	if(!t) return void(l = r = NULL);
	push(t);
	int cur_pos = add+sz(t->l)+1;
	if(cur_pos <= pos) split(t->r, t->r, r, pos, cur_pos), l = t;
	else split(t->l, l, t->l, pos, add), r = t;
	updt(t);
}

void merge(pitem &t, pitem l, pitem r) {
	push(l), push(r);
	if(!l || !r) t = l ? l : r;
	else if(l->prio < r->prio) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;
	updt(t);
}

void print(pitem t) {
	push(t);
	if(!t) return;
	print(t->l);
	printf("%c", t->c);
	print(t->r);
}

int n, m;
char A[N];
pitem t;

int main() {
	hpow[0] = pii(1, 1);
	for(int i = 1; i < N; i++) hpow[i] = mul(hpow[i-1], iden);
	scanf("%d %d", &n, &m);
	scanf(" %s", A+1);
	for(int i = 1; A[i]; i++) merge(t, t, new item(A[i]));
	while(m--) {
		char K;
		scanf(" %c", &K);
		if(K == 'Q') {
			int a, b;
			scanf("%d %d", &a, &b);
			pitem l, r;
			split(t, l, t, a-1);
			split(t, t, r, b-a+1);
			if(t->h == t->rh) printf("YES\n");
			else printf("NO\n");
			merge(t, l, t);
			merge(t, t, r);
		} else {
			int T;
			scanf("%d", &T);
			if(T == 1) {
				int a, b, c;
				scanf("%d %d %d", &a, &b, &c);
				pitem l, r;
				split(t, l, t, a-1);
				split(t, t, r, b-a+1);
				merge(l, l, r);
				split(l, l, r, c);
				merge(t, l, t);
				merge(t, t, r);
			} else if(T == 2) {
				int a, b;
				scanf("%d %d", &a, &b);
				pitem l, r;
				split(t, l, t, a-1);
				split(t, t, r, b-a+1);
				t->lz ^= 1;
				merge(t, l, t);
				merge(t, t, r);
			} else {
				int a;
				char b;
				scanf("%d %c", &a, &b);
				pitem l;
				split(t, l, t, a-1);
				merge(l, l, new item(b));
				merge(t, l, t);
			}
		}
	}

	return 0;
}