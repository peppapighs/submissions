//#include <race.h>
#include <bits/stdc++.h>

#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int N = 2e5 + 5;
const int M = 1e6 + 5;

int n, k, ans = -1;
int sub[N], d[N], dep[N];
int dp[M], tim[M];
vector<pii> g[N];

int getsz(int u = 0, int p = 0, int w = 0, int l = 0) {
	sub[u] = 1;
	d[u] = d[p] + w;
	dep[u] = l;
	for(pii v : g[u]) if(v.x != p) sub[u] += getsz(v.x, u, v.y, l + 1);
	return sub[u];	
}

void add(int u, int p, int st, int gp) {
	if(d[u] - d[st] > k) return;
	if((tim[k - d[u] + 2*d[st]] == gp || tim[k - d[u] + 2*d[st]] == st) && (ans == -1 || dep[u] - dep[st] + dp[k - d[u] + 2*d[st]] < ans)) ans = dep[u] - dep[st] + dp[k - d[u] + 2*d[st]];
	if(d[u] - d[st] == k && (ans == -1 || dep[u] - dep[st] < ans)) ans = dep[u] - dep[st];
	for(pii v : g[u]) if(v.x != p) add(v.x, u, st, gp);
}

void prep(int u, int p, int st) {
	if(d[u] - d[st] > k) return;
	if(tim[d[u]] != st || dep[u] < dp[d[u]]) tim[d[u]] = st, dp[d[u]] = dep[u];
	for(pii v : g[u]) if(v.x != p) prep(v.x, u, st);
}

void dfs(int u, int p, bool keep) {
	int mx = 0, hv;
	for(pii v : g[u]) if(v.x != p && mx < sub[v.x]) mx = sub[v.x], hv = v.x;
	for(pii v : g[u]) if(v.x != p && v.x != hv) dfs(v.x, u, 0);
	if(mx) dfs(hv, u, 1);
	for(pii v : g[u]) if(v.x != p && v.x != hv) {
		add(v.x, u, u, mx ? hv : INT_MAX);
		prep(v.x, u, u);
	}
	if((tim[k + d[u]] == u || tim[k + d[u]] == hv) && (ans == -1 || dp[k + d[u]] - dep[u] < ans)) ans = dp[k + d[u]] - dep[u]; 
	printf("%d - %d: ", u, keep);
	for(int i = 1; i <= 20 ; i++) {if(tim[i] == u || tim[i] == hv) printf("%d(%d) ", dp[i], tim[i]); else printf("X(%d) ", tim[i]);}
	printf("\n");
	if(keep && (tim[d[u]] != u || dp[d[u]] > dep[u])) tim[d[u]] = u, dp[d[u]] = dep[u];
}

int best_path(int N, int K, int H[][2], int L[])
{
	n = N, k = K;
	for(int i = 0; i < N - 1; i++) {
		g[H[i][0]].emplace_back(H[i][1], L[i]);
		g[H[i][1]].emplace_back(H[i][0], L[i]);
	}
	fill(begin(tim), end(tim), -1);
	getsz();
	dfs(0, 0, 1);
 
	return ans;
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1, u, v, w; i <= n; i++) {
		scanf("%d%d%d", &u, &v, &w);
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	fill(begin(tim), end(tim), -1);
	getsz();
	dfs(0, 0, 1);	
	printf("%d", ans);

	return 0;
}