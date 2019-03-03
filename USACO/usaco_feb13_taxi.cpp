#include <bits/stdc++.h>

#define long long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

int n, m, sum;
long ans;
vector<pii> V;

int main() {
	scanf("%d %d", &n, &m);
	V.emplace_back(0, -1), V.emplace_back(m, 1);
	for(int i = 1, a, b; i <= n; i++) {
		scanf("%d %d", &a, &b);
		V.emplace_back(a, 1), V.emplace_back(b, -1);
		ans += abs(a - b);
	}
	sort(V.begin(), V.end());
	sum = V[0].y;
	for(int i = 1; i < V.size(); i++) {
		ans += 1ll * (V[i].x - V[i-1].x) * abs(sum);
		sum += V[i].y;
	}
	printf("%lld\n", ans);

	return 0;
}