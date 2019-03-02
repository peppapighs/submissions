#include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;

struct node {
	int key;
	node *l, *r;
	node(int key) : key(key), l(NULL), r(NULL) {}
};

typedef node* pnode;

int n;
int A[N], B[N];
map<int, int> M;

pnode solve(int a, int b, int sz) {
	if(A[a] != B[b]) return NULL;
	pnode root = new node(A[a]);
	if(sz == 1) return root;
	int idx = M[A[a+1]];
	int right = b-idx-1;
	root->l = solve(a+1, idx, sz-right-1);
	root->r = solve(a+sz-right, b-1, right);
	return root;
}

void print(pnode p) {
	if(!p) return;
	print(p->l);
	printf("%d\n", p->key);
	print(p->r);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", A+i);
	for(int i = 1; i <= n; i++) scanf("%d", B+i), M[B[i]] = i;
	pnode ans = solve(1, n, n);
	print(ans);

	return 0;
}
