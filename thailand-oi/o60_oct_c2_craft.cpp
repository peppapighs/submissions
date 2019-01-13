#include <bits/stdc++.h>

using namespace std;

long long n, w;
long long A[25];

long long craft(long long lvl, long long k) {
	if(k <= 0) printf("-1"), exit(0);
	if(lvl == 1) return k;
	long long next = 2 * k - A[lvl - 1] + 1;
	return craft(lvl - 1, next / 2) + craft(lvl - 1, (next + 1) / 2); 
}

int main() {
	scanf("%lld%lld", &n, &w);
	for(int i = 1; i < n; i++) scanf("%lld", &A[i]);
	long long ans = craft(n, w);
	printf("%lld", ans);

	return 0;
}