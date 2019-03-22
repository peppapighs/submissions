#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 5e3 + 5;

int n, ans = INT_MAX;
vector<vector<int> > g(N);
int dep[N];

int bfs(int root) {
	int ret = 0;
	queue<int> Q;
	for(int i = 1; i <= n; i++) dep[i] = INT_MAX;

	Q.emplace(root);
	dep[root] = 1;

	while(!Q.empty()) {
		int now = Q.front();
		Q.pop();

		for(int v : g[now]) if(dep[now] + 1 < dep[v]) {
			dep[v] = dep[now] + 1;
			Q.emplace(v);
		} 
	}
	for(int i = 1; i <= n; i++) {
		if(dep[i] == INT_MAX) return INT_MAX;
		ret += dep[i];
	}
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 1, k; i <= n; i++) {
		scanf("%d", &k);
		while(k--) {
			int v;
			scanf("%d", &v);
			g[v].emplace_back(i);
		}
	} 

	for(int i = 1; i <= n; i++) ans = min(ans, bfs(i));
	printf("%d", ans);

	return 0;
}