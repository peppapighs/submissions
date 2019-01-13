#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n,m;

int main() {
	scanf("%d%d", &n, &m);
	if(m < n - 1) return !printf("Impossible");
	vector<pii> g;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			if(__gcd(i,j) == 1) g.emplace_back(i, j);
			if(g.size() == m) {
				printf("Possible\n");
				for(pii k : g) printf("%d %d\n", k.x, k.y);
				return 0;
			}
		}
	}

	return !printf("Impossible");

	return 0;
}