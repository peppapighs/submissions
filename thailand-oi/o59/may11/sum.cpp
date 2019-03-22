#include <bits/stdc++.h>

using namespace std;

struct item {
	long long val, size;
	int prior;
	item *l, *r;
	item(long long val) : val(val), prior(rand()), size(1LL), l(NULL), r(NULL) {}
};

typedef item* pitem;

long long cnt(pitem t) { return t ? t->size : 0LL; }
void updt(pitem t) { if(t) t->size = cnt(t->l) + 1LL + cnt(t->r); }

void split(pitem t, pitem &l, pitem &r, long long key) {
	if(!t) return void(l = r = NULL);
	if(t->val <= key) split(t->r, t->r, r, key), l = t;
	else split(t->l, l, t->l, key), r = t;
	updt(t);
}

void merge(pitem &t, pitem l, pitem r) {
	if(!l || !r) t = l ? l : r;
	else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;
	updt(t);
}

const int N = 1e5 + 5;

int n;
long long k, pref[N];

long long f(long long m) {
	long long sum = 0LL;
	pitem t = new item(0LL);
	for(int i = 1; i <= n; i++) {
		pitem r;
		split(t, t, r, pref[i]-m);
		sum += cnt(t);
		merge(t, t, r);
		split(t, t, r, pref[i]);
		merge(t, t, new item(pref[i]));
		merge(t, t, r);
	}
	return sum;
}

int main() {
	scanf("%d%lld", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%lld", &pref[i]), pref[i] += pref[i-1];
	
	long long l = -1e11, r = 1e11;
	long long ret = -1LL;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(f(mid) >= k) l = mid+1, ret = mid;
		else r = mid-1;
	}
	
	printf("%lld", ret);
	
	return 0;
}
