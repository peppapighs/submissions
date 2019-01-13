#include <bits/stdc++.h>

using namespace std;

struct node {
	int key;
	node *l, *r;
	node(int key) : key(key), l(NULL), r(NULL) {}
};

typedef node* nodep;

nodep lrot(nodep x) { nodep y = x->l; x->l = y->r; y->r = x; return y; }
nodep rrot(nodep x) { nodep y = x->r; x->r = y->l; y->l = x; return y; }

nodep splay(nodep t, int key) {
	if(!t || t->key == key) return t;
	else if(t->key > key) {
		if(!t->l) return t;
		else if(t->l->key > key) t->l->l = splay(t->l->l, key), t = rrot(t);
		else if(t->l->key < key) {
			t->l->r = splay(t->l->r, key); 
			if(t->l->r) t->l = lrot(t->l);
		}
		return t->l ? lrot(t) : t;
	} else {
		if(!t->r) return t;
		else if(t->r->key > key) {
			t->r->l = splay(t->r->l, key);
			if(t->r->l) t->r = rrot(t->r);
		} else if(t->r->key < key) t->r->r = splay(t->r->r, key), t = lrot(t);
		return t->r ? rrot(t) : t;
	}
}

nodep insert(nodep t, int key) {
	if(!t) return t;
	t = splay(t, key);
	if(t->key == key) return t;
	nodep ret = new node(key);
	if(t->key > key) ret->r = t, ret->l = t->l, t->l = NULL;
	else ret->l = t, ret->r = t->r, t->r = NULL;
	return ret;
}

nodep del(nodep t, int key) {
	nodep tmp;
	if(!t) return t;
	splay(t, key);
	if(t->key != key) return t;
	nodep l = t->l, r = t->r;
	if(!l) tmp = t, t = t->r;
	else tmp = t, t = splay(t->l, key), t->r = tmp->r;
	free(tmp);
	return t;
}

int main() {


	return 0;
}