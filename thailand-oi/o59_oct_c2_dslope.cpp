#include <bits/stdc++.h>

using namespace std;

const int N = 8e4 + 5;
const int M = 1e9 - 1;

int n, k;
long long ans;
long long tree[45][N];

void update(int x, int pos, long long k) {
	for(int i = pos; i; i -= i & (-i)) tree[x][i] = (tree[x][i] + k) % M;
}

long long query(int x, int pos) {
	long long sum = 0;
	for(int i = pos; i <= n; i += i & (-i)) sum = (sum + tree[x][i]) % M;
	return sum % M;
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		update(1, x, 1LL);
		for(int j = 2; j <= k; j++) update(j, x, query(j - 1, x + 1));
		/*for(int j = 1; j <= k; j++) {
			for(int i = 1; i <= n; i++) printf("%d ", query(j, i));
			printf("\n");
		}
		printf("\n");*/
	}
	
	printf("%lld", query(k, 1));

	return 0;
}