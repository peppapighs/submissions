#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;

int n, q;
vector<pii> g(N);
int dep[N], chi[N][18];

int s, a, b;
int dir() {
	int res = ((s & 8) >> 3);
	s = (s * a + b) % 40507;
	return res;
}

void dfs(int u) {
	if(g[u].x == -1 && g[u].y == -1) {
		for(int i = 0; i <= 17; i++) chi[u][i] = u;
		return;
	}
	if(g[u].x != -1 && g[u].y != -1) {
		dep[g[u].x] = dep[g[u].y] = dep[u] + 1;
		for(int i = 0; i <= 17; i++) chi[u][i] = u;
		dfs(g[u].x), dfs(g[u].y);
		return;
	}
	int next;
	if(g[u].x != -1) next = g[u].x;
	else next = g[u].y;
	chi[u][0] = next;
	dep[next] = dep[u] + 1;
	dfs(next);
	for(int i = 1; i <= 17; i++) chi[u][i] = chi[chi[u][i - 1]][i - 1];
}

int solve(int v, int lvl) {
	if(dep[v] == lvl) return v;
	if(chi[v][0] == v) {
		if(g[v].x == -1 && g[v].y == -1) return v;
		else {
			bool st = dir();
			if(!st) return solve(g[v].x, lvl);
			else return solve(g[v].y, lvl);
		}
	} else {
		int nx = v;
		for(int i = 17; ~i; i--) if(dep[chi[nx][i]] <= lvl) nx = chi[nx][i];
		return solve(nx, lvl);
	}
}

int main() {
	scanf("%d%d", &n, &q);
	for(int i = 0, a, b; i < n; i++) {
		scanf("%d%d", &a, &b);
		g[i] = pii(a, b);
	}

	dfs(0);
	while(q--) {
		int l;
		scanf("%d%d%d%d", &l, &s, &a, &b);
		printf("%d\n", solve(0, l));
	}

	return 0;
}