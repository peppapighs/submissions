#include <bits/stdc++.h>

using namespace std;

const int N = 3e5+5;

struct ll {
	int val;
	int l, r;
	ll(int val) : val(val), l(-1), r(-1) {}
};

int n;
int tail[N];
vector<ll> L;
bool chk[N];

int main() {
	L.emplace_back(0);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) L.emplace_back(i), tail[i] = i;
	for(int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		int right = L[b].r;
		int t = tail[a];
		L[b].r = a;
		L[a].l = b;
		if(right == -1) tail[b] = t;
		else L[t].r = right, L[right].l = t;
		tail[a] = -1;
		chk[a] = true;
	}
	for(int i = 1; i <= n; i++) if(!chk[i]) 
		for(int j = i; j != -1; j = L[j].r) printf("%d ", j);
	printf("\n");

	return 0;
}
