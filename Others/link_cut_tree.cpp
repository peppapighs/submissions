#include <bits/stdc++.h>

using namespace std;

struct item {
	int d, sz;
	item *l, *r, *p, *pp;
	item(int d) : d(d), sz(1), l(NULL), r(NULL), p(NULL), pp(NULL) { }
};

typedef item* pitem;

int sz(pitem t) { return t ? t->sz : 0; }
void updt(pitem t) { if(t) t->sz = sz(t->l) + 1 + sz(t->r); }

void rrot(pitem x) {
	pitem y = x->p, z = y->p;
	if(y->l = x->r) y->l->p = y;
	x->r = y, y->p = x;
	if(x->p = z) {
		if(y == z->l) z->l = x;
		else z->r = x;
	}
	x->pp = y->pp, y->pp = NULL;
	updt(x);
}

void lrot(pitem x) {
	pitem y = x->p, z = y->p;
	if(y->r = x->l) y->r->p = x;
	x->r = y, y->p = x;
	if(x->p = z) {
		if(y == z->l) z->l = x;
		else z->r = x;
	}
	x->pp = y->pp, y->pp = NULL;
	updt(x);
}

void splay(pitem x) {
	pitem y, z;
	while(x->p) {
		y = x->p;
		if(!y->p) {
			if(y->l == x) rrot(x);
			else lrot(y);
		} else {
			z = y->p;
			if(z->l == y) {
				if(y->l == x) rrot(y), rrot(x);
				else lrot(x), rrot(x);
			} else {
				if(y->l == x) lrot(y), rrot(x);
				else rrot(x), lrot(x);
			}
		}
	}
	updt(x);
}

pitem access(pitem x) {
	splay(x);
	if(x->r) {
		x->r->pp = x;
		x->r->p = NULL;
		x->r = NULL;
		updt(x);
	}
	pitem prev = x;
	while(x->pp) {
		pitem y = x->pp;
		prev = y;
		splay(y);
		if(y->r) y->r->pp = y, y->r->p = NULL;
		y->r = x;
		x->p = y, x->pp = NULL;
		updt(y);
		splay(x);
	}
	return prev;
}

pitem find_root(pitem x) {
	access(x);
	while(x->l) x = x->l;
	splay(x);
	return x;
}

void link(pitem x, pitem y) {
	access(x), access(y);
	x->l = y;
	y->p = x;
	updt(x);
}

void cut(pitem x) {
	access(x);
	x->p->r = NULL;
	x->p = NULL;
	updt(x);
}

int main() {


	return 0;
}