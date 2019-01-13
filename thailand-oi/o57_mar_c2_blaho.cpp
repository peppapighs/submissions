#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+5;

int n, m, cnt;
char A[N];
vector<int> g[N], C[N];
int comp[N];
int low[N], disc[N], st[N];
string str[N], dp[N];

void find_scc(int u) {
	static int idx = 0;
	static stack<int> S;
	low[u] = disc[u] = ++idx;
	S.emplace(u), st[u] = true;
	for(int v : g[u]) {
		if(!disc[v]) {
			find_scc(v);
			low[u] = min(low[u], low[v]);
		} else if(st[v]) low[u] = min(low[u], disc[v]);
	}
	if(low[u] == disc[u]) {
		int v;
		++cnt;
		do {
			v = S.top();
			S.pop();
			comp[v] = cnt;
			st[v] = false;
		} while(u != v);
	}
}

string dfs(int u) {
	if(u == comp[n]) {
		dp[u] = str[comp[n]];
		st[u] = true;
		return dp[u];
	}
	if(st[u]) return dp[u];
	string now = "";
	for(int v : C[u]) {
		string cat = dfs(v);
		if(!st[v]) continue;
		if(now.size() < cat.size()) now = cat;
		else if(now.size() == cat.size() && cat < now) now = cat;
		st[u] |= st[v];
	}
	return dp[u] = str[u] + now;
}

int main() {
	scanf("%d %d", &n, &m);
	scanf(" %s", A+1);
	while(m--) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].emplace_back(v);
	}
	for(int i = 1; i <= n; i++) if(!disc[i]) find_scc(i);
	for(int i = 1; i <= n; i++) {
		str[comp[i]].push_back(A[i]);
		for(int v : g[i]) if(comp[i] != comp[v]) C[comp[i]].emplace_back(comp[v]);
	}
	for(int i = 1; i <= cnt; i++) sort(str[i].begin(), str[i].end());

	cout << dfs(comp[1]) << endl;

	return 0;
}
