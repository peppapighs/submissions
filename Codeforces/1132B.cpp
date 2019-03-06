#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 3e5+5;

int n, m, dist[N];
long A[N], sum;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &A[i]);
		sum += A[i];
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d", &dist[i]);
	sort(A + 1, A + 1 + n, greater<int>());
	for(int i = 1; i <= m; i++) printf("%lld\n", sum - A[dist[i]]);

	return 0;
}
