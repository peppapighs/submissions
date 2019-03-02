#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

int n;
int dsu[N], dist[N];
vector<pii> comp;

int find(int u) { return dsu[u] = u == dsu[u] ? u : find(dsu[u]); }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) dsu[i] = i;
	for(int i = 1; i <= n; i++) scanf("%d", &dist[i]);
	for(int i = 0, a, b; i < n - 2; i++) {
		scanf("%d%d", &a, &b);
		a = find(a), b = find(b);
		dsu[a] = b;
	}
	for(int i = 1; i <= n; i++) find(i), comp.emplace_back(dist[i], dsu[i]);
	sort(comp.begin(), comp.end());
	int ans = INT_MAX;
	for(int i = 1; i < n; i++) if(comp[i].y != comp[i - 1].y) ans = min(ans, comp[i].x - comp[i - 1].x);
	printf("%d", ans);

	return 0;
}