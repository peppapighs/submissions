#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 1e5 + 5;

pii add(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
pii sub(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii mul(pii a, pii b) { return pii(a.x * b.x, a.y * b.y); }

int n, m;
long long ans;
vector<pii> edge;
pii hsh[N];
map<pii, int> cnt;

pii prm(69, 420);
pii pwr[N];

int main() {
	pwr[0] = pii(1, 1);
	for(int i = 1; i < N; i++) pwr[i] = mul(pwr[i - 1], prm);
	scanf("%d%d", &n, &m);
	for(int i = 0, u, v; i < m; i++) {
		scanf("%d%d", &u, &v);
		hsh[u] = add(hsh[u], pwr[v]);
		hsh[v] = add(hsh[v], pwr[u]);
		edge.emplace_back(u, v);
	}

	for(int i = 1; i <= n; i++) cnt[hsh[i]]++;
	for(pair<pii, int> p : cnt) ans += (1LL * p.y * (p.y - 1LL) / 2LL);
	for(pii p : edge) if(sub(hsh[p.x], pwr[p.y]) == sub(hsh[p.y], pwr[p.x])) ans++;

	printf("%lld", ans);

	return 0;
}