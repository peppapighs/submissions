#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

int n;
int A[N];
bool chk[N], dp[N];
vector<int> g[N];

void dfs(int u) {
	chk[u] = true;
	for(int v : g[u]) {
		if(!chk[v]) dfs(v);
		dp[u] |= dp[v]^1;
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", A+i);
	for(int i = 1; i <= n; i++) {
		int c = A[i];
		for(int j = i+c; j <= n; j += c) if(A[j] > A[i]) 
			g[i].emplace_back(j);
		for(int j = i-c; j > 0; j -= c) if(A[j] > A[i])
			g[i].emplace_back(j);
	}
	for(int i = 1; i <= n; i++) if(!g[i].size()) chk[i] = true;
	for(int i = 1; i <= n; i++) if(!chk[i]) dfs(i);
	for(int i = 1; i <= n; i++) {
		if(dp[i]) printf("A");
		else printf("B");
	}
	printf("\n");

	return 0;
}
