#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int T;
int n, k;
int W[N], C[N];

int f(int m) {
	set<int> pwd;
	int ww = 0, cnt = 1;;
	for(int i = 1; i <= n; i++) {
		if(W[i] > m) return 1e9;
		if(pwd.find(C[i]) != pwd.end()) ww = 0, ++cnt, pwd.clear();
		if(ww + W[i] > m) ww = 0, ++cnt, pwd.clear();
		ww += W[i];
		pwd.emplace(C[i]);
	}
	return cnt;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &k);
		for(int i = 1; i <= n; i++) scanf("%d %d", W+i, C+i);
		int l = 0, r = 1e9;
		while(l < r) {
			int m = (l + r) >> 1;
			if(f(m) <= k) r = m;
			else l = m+1;
		}
		if(r != 1e9) printf("%d\n", r);
		else printf("-1\n");
	}

	return 0;
}
