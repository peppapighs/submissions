#include <bits/stdc++.h>

using namespace std;

const int N = 2e7+5;

int n, g;
int ans = INT_MAX;
int A[N];
bitset<N> chk;

int main() {
	scanf("%d", &n);
	for(int i = 1, a; i <= n; i++) {
		scanf("%d", &a);
		g = __gcd(g, a);
		A[a]++;
	}
	for(int i = g+1; i < N; i++) {
		int ret = 0;
		if(!chk[i]) for(int j = i; j < N; j += i) ret += A[j], chk[j] = 1;
		if(ret) ans = min(ans, n-ret);
	}
	if(ans == INT_MAX) printf("-1\n");
	else printf("%d\n", ans);
	
	return 0;
}