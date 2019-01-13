#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

vector<vector<int> > tree(N);

int n,m;
int dep[N],anc[N][18];

void dfs(int u,int p) {
	anc[u][0] = p;
	dep[u] = dep[p]+1;
	for(int i=1;i<=17;i++) anc[u][i] = anc[anc[u][i-1]][i-1];
	for(int v : tree[u]) if(v!=p) dfs(v,u);
}

int lca(int a,int b) {
	if(dep[a]<dep[b]) swap(a,b);
	for(int i=17;i>=0;i--) if(dep[anc[a][i]]>=dep[b]) a=anc[a][i];
	if(a==b) return a;
	for(int i=17;i>=0;i--) if(anc[a][i]!=anc[b][i]) {
		a=anc[a][i];
		b=anc[b][i];
	}
	return anc[a][0];
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=0;i<n-1;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		tree[u].emplace_back(v);
		tree[v].emplace_back(u);
	}
	dfs(1,0);
	while(m--) {
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",dep[a]+dep[b]-2*dep[lca(a,b)]);
	}

	return 0;
}