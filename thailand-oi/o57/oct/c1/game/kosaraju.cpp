#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5;

int n, m;
int rnk[N], ans[N];
vector<int> g[N], tg[N];
bool vis[N];
deque<int> S, C;

void dfs(int u) {
	vis[u] = true;
	for(int v : g[u]) if(!vis[v]) dfs(v);
	S.emplace_front(u);
}

void scc(int u, int &lvl) {
	if(vis[u]) return void(lvl = max(lvl, rnk[u]));
	vis[u] = true;
	for(int v : tg[u]) scc(v, lvl);
	C.emplace_front(u);
}

int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].emplace_back(v);
		tg[v].emplace_back(u);
	}
	for(int i = 0; i < n; i++) if(!vis[i]) dfs(i);
	memset(vis, false, sizeof vis);
	while(!S.empty()) {
		int now = S.front();
		S.pop_front();
		if(vis[now]) continue;
		int lvl = 0;
		scc(now, lvl);
		lvl++;
		while(!C.empty()) {
			int cur = C.front();
			C.pop_front();
			rnk[cur] = lvl;
			ans[lvl]++;
		}
	}

	for(int i = 1; ans[i]; i++) printf("%d ", ans[i]);

	return 0;
}