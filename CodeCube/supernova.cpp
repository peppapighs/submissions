#include <bits/stdc++.h>

#define pii pair<int,int>

using namespace std;

const int N = 1e5+5;

int n,m;
vector<vector<int> > g(N);
vector<pii> edge;
vector<int> st,cyc;
long long color[N],dp[N];
bool vis[N],incyc[N];

void dfs1(int u,int p) {
	color[u]=1;
	st.push_back(u);
	for(int v : g[u]) if(v!=p) {
		if(!color[v]) {
			dfs1(v,u);
		} else if(color[v]==1) {
			incyc[v]=true;
			vis[v]=true;
			cyc.push_back(v);
			for(int i=st.size()-1;i>=0;i--) {
				if(st[i]==v) {
					break;
				}
				incyc[st[i]]=true;
				vis[st[i]]=true;
				cyc.push_back(st[i]);
			}
		}
	}
	color[u]=2;
	st.pop_back();
}

int dfs2(int u,int p) {
	vis[u]=true;
	for(int v : g[u]) if(!vis[v]&&v!=p) {
		dp[u]+=dfs2(v,u);
	}
	return ++dp[u];
}

int main() {
	scanf("%d%d",&n,&m);
	while(m--) {
		int u,v;
		scanf("%d%d",&u,&v);
		g[--u].emplace_back(--v);
		g[v].emplace_back(u);
		edge.emplace_back(u,v);
	}
	dfs1(0,-1);
	for(int a : cyc) {
		dfs2(a,-1);
	}
	for(pii e : edge) {
		if(incyc[e.first]&&incyc[e.second]) {
			printf("0 ");
		} else {
			printf("%lld ",min(dp[e.first],dp[e.second])*(n-min(dp[e.first],dp[e.second])));
		}
	}

	return 0;
}